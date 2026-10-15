"""dropunit.py UNIT: remove a unit's entry from units.json (its symbols in the symbols table stay)."""
import os as _os
M = _os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))  # the matching/ folder
WORK = _os.path.join(M, "build", "s3")  # scratch files
_os.makedirs(WORK, exist_ok=True)
import json, sys
p = _os.path.join(M, "data", "units.json")
u = json.load(open(p, encoding="utf-8-sig"))
print("dropped" if u["units"].pop(sys.argv[1], None) is not None else "not present")
open(p, "w", encoding="utf-8", newline="\n").write(json.dumps(u, indent=2) + "\n")
