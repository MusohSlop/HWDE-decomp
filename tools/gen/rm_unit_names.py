import os as _os
GENDIR = _os.path.dirname(_os.path.abspath(__file__))
MATCHDIR = _os.path.dirname(_os.path.dirname(GENDIR))
ROOTDIR = _os.path.dirname(MATCHDIR)
import re, sys
p = (MATCHDIR + r"\data\units.json")
t = open(p, encoding="utf-8").read()
i = t.index('"units"')
head, tail = t[:i], t[i:]
for name in sys.argv[1:]:
    tail = re.sub(r'\n\s*"' + re.escape(name) + r'": "0x[0-9a-f]+",?', "", tail)
tail = re.sub(r",(\s*\n\s*\})", r"\1", tail)
open(p, "w", encoding="utf-8", newline="\n").write(head + tail)
