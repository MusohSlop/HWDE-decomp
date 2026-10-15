"""Write a ByteMatch history file: one entry per published commit, with objdiff-style measures from functions.csv.

Usage: bytematch_history.py REPO HEAD [MERGED] [--out FILE] [--first-parent]

REPO is the published repository (the matching/-only copy), HEAD its branch as published and MERGED, optionally, a
commit that will be merged into it next (the new subtree split). The commits are HEAD's mainline: its first-parent
chain, oldest first, where each merge is preceded by the first-parent chain of what it merged that the first parent
does not already contain (one level deep); MERGED's first-parent chain follows. With --first-parent only HEAD's first-parent chain
is used. Each commit's own data/functions.csv gives its measures; commits without one in the byte-matching format
(Address,Quality,Size,Name) are skipped.

The format is ByteMatch's history upload (docs/api.md): a JSON array, oldest first, of
{"timestamp", "commit_sha", "commit_message", "measures"} with the 16 objdiff measures. total_code and
total_functions count every inventory function, matched_* the exact matches (quality O); fuzzy_match_percent is
the matched code percent, a lower bound (no per-function fuzzy scores are kept); data, complete and unit measures
are 0 (not tracked).
"""
import csv
import io
import json
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

GIT = r"C:/Users/grays/.cache/codex-runtimes/codex-primary-runtime/dependencies/native/git/cmd/git.exe"
CSV_PATH = "data/functions.csv"
HEADER = ["Address", "Quality", "Size", "Name"]


def git(repo, *args):
    r = subprocess.run([GIT, *args], cwd=repo, capture_output=True, text=True, encoding="utf-8", errors="replace")
    if r.returncode:
        raise SystemExit(f"git {' '.join(args)}: {r.stderr.strip()}")
    return r.stdout


def chain(repo, tip, exclude=None):
    args = ["rev-list", "--first-parent", "--reverse", tip] + ([f"^{exclude}"] if exclude else [])
    return git(repo, *args).split()


def mainline(repo, tip, exclude=None, first_parent=False):
    out = []
    for c in chain(repo, tip, exclude):
        parents = git(repo, "rev-list", "--parents", "-n", "1", c).split()[1:]
        if len(parents) > 1 and not first_parent:
            out += chain(repo, parents[1], parents[0])   # one level: the merged branch's own merges stay whole
        out.append(c)
    return out


def measures(repo, sha):
    r = subprocess.run([GIT, "show", f"{sha}:{CSV_PATH}"], cwd=repo, capture_output=True, text=True, encoding="utf-8")
    if r.returncode:
        return None
    rows = list(csv.reader(io.StringIO(r.stdout)))
    if not rows or rows[0] != HEADER:
        return None
    tf = mf = tb = mb = 0
    for row in rows[1:]:
        if len(row) < 3 or not row[2].isdigit():
            continue
        tf += 1; tb += int(row[2])
        if row[1] == "O":
            mf += 1; mb += int(row[2])
    if not tf:
        return None
    pct = lambda a, b: round(100.0 * a / b, 2) if b else 0
    return {
        "fuzzy_match_percent": pct(mb, tb),
        "total_code": tb, "matched_code": mb, "matched_code_percent": pct(mb, tb),
        "total_data": 0, "matched_data": 0, "matched_data_percent": 0,
        "total_functions": tf, "matched_functions": mf, "matched_functions_percent": pct(mf, tf),
        "complete_code": 0, "complete_code_percent": 0, "complete_data": 0, "complete_data_percent": 0,
        "total_units": 0, "complete_units": 0,
    }


def main():
    args = sys.argv[1:]
    out = Path(args[args.index("--out") + 1]) if "--out" in args else None
    if out:
        i = args.index("--out"); del args[i:i + 2]
    first_parent = "--first-parent" in args
    args = [a for a in args if not a.startswith("--")]
    repo, head = args[0], args[1]
    commits = mainline(repo, head, first_parent=first_parent)
    if len(args) > 2:
        commits += chain(repo, args[2], head)
    seen, entries = set(), []
    for c in commits:
        if c in seen:
            continue
        seen.add(c)
        m = measures(repo, c)
        if m is None:
            continue
        ts, subject = git(repo, "show", "-s", "--format=%ct%x00%s", c).rstrip("\n").split("\0", 1)
        stamp = datetime.fromtimestamp(int(ts), timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
        entries.append({"timestamp": stamp, "commit_sha": c, "commit_message": subject, "measures": m})
    text = json.dumps(entries, indent=1) + "\n"
    if out:
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text, encoding="utf-8", newline="\n")
    print(f"{len(entries)} entries of {len(commits)} commits")
    for e in (entries[:1] + entries[-1:]):
        print(e["timestamp"], e["commit_sha"][:10], e["commit_message"][:60], json.dumps(e["measures"]))


if __name__ == "__main__":
    main()
