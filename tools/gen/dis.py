"""usage: dis.py ADDR [ADDR...]  (hex, image offsets); sizes from functions.csv"""
import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import csv, sys
sys.path.insert(0, (ROOTDIR + r"\.tools\python"))
import capstone
root = ROOTDIR
d = open(root + r"\analysis\extracted\update\decompressed\main.memory.bin", "rb").read()
sz = {int(r[0], 16) - 0x7100000000: int(r[2]) for r in csv.reader(open(root + r"\matching\data\functions.csv")) if r[0].startswith("0x")}
md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
for x in sys.argv[1:]:
    a = int(x, 16)
    print(f"== {a:x} ({sz[a]} bytes)")
    for i in md.disasm(d[a:a + sz[a]], a):
        print(f"  {i.address:6x}  {i.mnemonic} {i.op_str}")
