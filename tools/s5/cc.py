"""cc.py CPP [FUNC_SUBSTRING...]: compile a scratch file with the project's compiler and flags and print the
disassembly of its functions (those whose symbol contains one of the substrings, or all). For quick experiments on
source forms; relocations are not applied (branch and adrp targets are section-relative)."""
import os, sys, json, subprocess
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
ROOT = os.path.dirname(M)
sys.path.insert(0, os.path.join(M, "tools"))
sys.path.insert(0, os.path.join(ROOT, ".tools", "python"))
import capstone  # noqa
import check_obj  # noqa
cpp = sys.argv[1]
want = sys.argv[2:]
man = json.load(open(os.path.join(M, "data", "units.json"), encoding="utf-8-sig"))
obj = os.path.splitext(cpp)[0] + ".o"
c = subprocess.run([os.path.join(ROOT, man["compiler"]), *man["flags"], "-I", os.path.join(M, "include"), "-c", cpp,
                    "-o", obj], capture_output=True, text=True)
if c.returncode:
    print(c.stderr[-3000:]); sys.exit(1)
data, sections, symbols, relocs = check_obj.read_elf(obj)
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
for s in symbols:
    if s.is_section or s.shndx == 0 or not s.size or (want and not any(w in s.name for w in want)):
        continue
    sec = sections[s.shndx]
    if not sec[2] & 4:  # SHF_EXECINSTR
        continue
    code = data[sec[4] + s.value: sec[4] + s.value + s.size]
    print("== %s (%d bytes)" % (s.name, s.size))
    for i in md.disasm(code, s.value):
        print("  %4x  %s %s" % (i.address, i.mnemonic, i.op_str))
