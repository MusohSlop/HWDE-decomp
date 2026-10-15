"""Live-range lengths of one function's virtual registers, as the greedy allocator sees them.

usage: ranges.py CPP|LL FUNC [--top N] [--block K]

Compiles with -print-machineinstrs, takes the function as it enters the greedy register allocator (after the
pre-RA machine scheduler) and prints, for each virtual register, its first definition and last use (slot index /
16, i.e. instruction distance), the length, whether it spans blocks (allocated first, longest first, as are ranges
longer than twice the class size: 64 instructions for FPR128 and GPR64), and the register it was given (from the
Virtual Register Rewriter's output, matched by instruction position). Lists the global ranges in allocation order.
"""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))
import os, sys, re, json, subprocess, argparse
ROOT = os.path.dirname(M)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src"); ap.add_argument("func"); ap.add_argument("--top", type=int, default=40)
    a = ap.parse_args()
    man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
    cc = os.path.join(ROOT, man["compiler"])
    flags = list(man["flags"])
    if a.src.endswith(".ll"):
        flags = [f for f in flags if not f.startswith(("-std=", "-stdlib", "-fno-exceptions", "-fstandalone", "-g"))]
        flags += ["-Xclang", "-disable-llvm-optzns"]
    out = os.path.join(M, "build", "s5", "ranges.o")
    r = subprocess.run([cc, *flags, "-I", os.path.join(M, "include"), "-c", a.src, "-o", out, "-mllvm",
                        "-print-machineinstrs"], capture_output=True, text=True)
    text = r.stderr
    def section(title):
        k = text.find("# After " + title)
        while k >= 0:
            e = text.find("\n# After ", k + 1)
            body = text[k: e if e > 0 else len(text)]
            if ("Machine code for function " + a.func + ":") in body:
                return body
            k = text.find("# After " + title, k + 1)
        return None
    pre = section("Machine Instruction Scheduler")
    post = section("Virtual Register Rewriter")
    if pre is None:
        sys.exit("no scheduler output for " + a.func)
    blocks = {}
    cur = None
    defs, uses = {}, {}
    slot_line = {}
    for line in pre.split("\n"):
        m = re.match(r"^(\d+)B\s+(BB#\d+):", line)
        if m:
            cur = m.group(2)
            continue
        m = re.match(r"^(\d+)B\t(.*)$", line)
        if not m:
            continue
        s = int(m.group(1)) // 16
        ins = m.group(2).split(";")[0]
        slot_line[s] = ins
        lhs, _, rhs = ins.partition(" = ")
        if not rhs:
            lhs, rhs = "", ins
        for v in re.findall(r"%vreg(\d+)", lhs):
            v = int(v)
            defs.setdefault(v, (s, cur))
            blocks.setdefault(v, set()).add(cur)
        for v in re.findall(r"%vreg(\d+)", rhs):
            v = int(v)
            uses[v] = max(uses.get(v, (s, cur)), (s, cur))
            blocks.setdefault(v, set()).add(cur)
        for v in re.findall(r"%vreg(\d+)<def,tied", lhs):
            pass
    # registers from the rewriter, by slot
    phys = {}
    if post:
        for line in post.split("\n"):
            m = re.match(r"^(\d+)B\t(.*)$", line)
            if m:
                phys[int(m.group(1)) // 16] = m.group(2).split(";")[0]
    rows = []
    for v, (ds, db) in defs.items():
        us, ub = uses.get(v, (ds, db))
        glob = len(blocks[v]) > 1
        reg = ""
        p = phys.get(ds)
        if p:
            reg = p.split(" = ")[0].strip().split(":")[0].split("<")[0]
        rows.append((v, ds, us, us - ds, glob, reg, slot_line.get(ds, "")[:60]))
    rows.sort(key=lambda r: r[1])
    big = [r for r in rows if r[4] or r[3] > 64]
    print("global or long (> 64), allocation order (longest first, then lower vreg):")
    for r in sorted(big, key=lambda r: (-r[3], r[0]))[:a.top]:
        print("  vreg%-4d %5d-%-5d len %3d %-6s %s %s" % (r[0], r[1], r[2], r[3], r[5], "multi-block" if r[4] else "", r[6]))
    print("local, by start:")
    for r in rows:
        if r not in big:
            print("  vreg%-4d %5d-%-5d len %3d %-6s %s" % (r[0], r[1], r[2], r[3], r[5], r[6]))


if __name__ == "__main__":
    main()
