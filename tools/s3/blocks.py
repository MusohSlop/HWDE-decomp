"""blocks.py CPP ADDR [SYMJSON] [--name SYM] [--map ...]: coarse diff of a long function: compiles like try.py and
prints the difflib opcodes as instruction-index ranges with their lengths (equal runs summarised), so the parts
that differ in size stand out."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
import sys, subprocess, re, difflib
r = subprocess.run([sys.executable, "-B", "-I", _os.path.join(_os.path.dirname(_os.path.abspath(__file__)), "try.py"),
                    *sys.argv[1:], "--all", "--ctx", "0"], capture_output=True, text=True)
lines = r.stdout.split("\n")
print("\n".join(lines[:3]))
# rebuild the two instruction lists from try.py --all output: "  off   ins" (equal), "  off - ins" (ours), "  off + ins" (orig)
ours, orig = [], []
for l in lines[3:]:
    m = re.match(r"\s+([0-9a-f]+) ([-+ ]) (.*)$", l)
    if not m:
        continue
    k, s, ins = m.groups()
    if s == " ":
        ours.append(ins); orig.append(ins)
    elif s == "-":
        ours.append(ins)
    else:
        orig.append(ins)
sm = difflib.SequenceMatcher(None, ours, orig, autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        print(f"  equal   {i2 - i1:5d}   ours {i1 * 4:#06x}  orig {j1 * 4:#06x}")
    else:
        print(f"  {tag:7s} ours[{i1 * 4:#06x}:{i2 * 4:#06x}] ({i2 - i1})  orig[{j1 * 4:#06x}:{j2 * 4:#06x}] ({j2 - j1})"
              f"   first: {ours[i1] if i1 < i2 else '-'} | {orig[j1] if j1 < j2 else '-'}")
