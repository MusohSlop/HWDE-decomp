"""flt.py ADDR... : print the 4-byte words at image offsets as float and hex (literal pool lookups)."""
import os, struct, sys
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
IMG = os.path.join(os.path.dirname(M), "analysis", "extracted", "update", "decompressed", "main.memory.bin")
img = open(IMG, "rb").read()
for x in sys.argv[1:]:
    a = int(x, 16) & 0xffffffff
    w = img[a:a + 4]
    print("%x  %08x  %r" % (a, struct.unpack("<I", w)[0], struct.unpack("<f", w)[0]))
