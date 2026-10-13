"""Compile probe.cpp with the project flags and compare each variant's code with the original."""
import json, re, struct, subprocess, sys
from pathlib import Path
sys.path.insert(0, r"F:\Claude Decomps\project1\.tools\python")
import capstone

here = Path(__file__).resolve().parent
matching = here.parents[1]
root = matching.parent
man = json.loads((matching / "data/units.json").read_text(encoding="utf-8-sig"))
asm = here / "probe.s"
subprocess.run([str(root / man["compiler"]), *man["flags"], "-S", str(here / "probe.cpp"), "-o", str(asm)], check=True)
data = (root / "analysis/extracted/update/decompressed/main.memory.bin").read_bytes()
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)

def norm(text):
    text = re.sub(r"\s+", " ", text.strip().replace("\t", " "))
    text = re.sub(r"#(-?)0x([0-9a-f]+)", lambda m: "#" + m.group(1) + str(int(m.group(2), 16)), text)
    text = re.sub(r"\bbl \S+", "bl CALL", text)
    text = re.sub(r"\bb \S+", "b CALL", text)
    return text

def original(addr, size):
    return [norm(f"{i.mnemonic} {i.op_str}") for i in md.disasm(data[addr:addr + size], addr)]

lines = asm.read_text().splitlines()
funcs, cur = {}, None
for line in lines:
    m = re.match(r"^(_ZN\w+5resetEv):", line)
    if m:
        cur = m.group(1); funcs[cur] = []; continue
    if cur and line.startswith("\t") and not line.startswith("\t."):
        ins = line.split("//")[0].strip()
        if ins:
            funcs[cur].append(norm(ins))
    if cur and line.startswith(".Lfunc_end"):
        cur = None

targets = {"Control": (0x5fad40, 48)}
for name, body in funcs.items():
    cls = re.match(r"_ZN\d+(\w+?)5resetEv", name).group(1)
    addr, size = targets.get(cls, (0x4c054, 48))
    orig = original(addr, size)
    same = body == orig
    print(f"{cls:18s} {'MATCH' if same else 'differs'} ({len(body)} vs {len(orig)} instructions)")
    if not same and "-v" in sys.argv:
        for a, b in zip(body, orig):
            print(f"   {'  ' if a == b else '* '}{a:40s} | {b}")
