"""Compile the probe samples with several compiler variants and score them.

The samples are functions in the existing units, one per suspected compiler-difference
pattern, plus exact matches as controls. Objects go to matching/scratch/compiler_probe/build.
Usage: python -B probe.py
"""
import json
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
MATCHING = HERE.parents[1]
ROOT = MATCHING.parent
sys.path.insert(0, str(ROOT / ".tools/python"))
sys.path.insert(0, str(MATCHING / "tools"))
import check  # noqa: E402
import check_obj  # noqa: E402

SAMPLES = [
    ("control", "event/adv_effects.cpp", 0x269544),   # stop_banner, exact match
    ("control", "event/adv_board.cpp", 0x269cfc),     # unit_kind, exact match
    ("control", "event/adv_board.cpp", 0x269c40),     # unit_alive, exact match
    ("null check", "event/adv_effects.cpp", 0x269188),  # play_banner
    ("null check", "event/adv_effects.cpp", 0x2696a8),  # play_clock
    ("switch", "event/adv_board.cpp", 0x269fa0),      # is_officer_kind
    ("switch", "event/adv_board.cpp", 0x26c610),      # is_plain_cell
    ("bitfield", "event/adv_board.cpp", 0x26c884),    # unit_override_frame
]

GREEDY = ["-mllvm", "-regalloc=greedy"]


def variants(base_flags):
    plain = [f for f in base_flags if f not in GREEDY]
    return [
        ("3.9.1 (project flags)", ".tools/clang-3.9.1/bin/clang++.exe", base_flags),
        ("3.9.1 without -regalloc=greedy", ".tools/clang-3.9.1/bin/clang++.exe", plain),
        ("3.9.1 -regalloc=basic", ".tools/clang-3.9.1/bin/clang++.exe", plain + ["-mllvm", "-regalloc=basic"]),
        ("3.9.1 -regalloc=pbqp", ".tools/clang-3.9.1/bin/clang++.exe", plain + ["-mllvm", "-regalloc=pbqp"]),
        ("3.9.1 -O2", ".tools/clang-3.9.1/bin/clang++.exe", ["-O2" if f == "-O3" else f for f in base_flags]),
        ("3.8.1", ".tools/clang-3.8.1/bin/clang++.exe", base_flags),
        ("4.0.1", ".tools/clang-4.0.1/bin/clang++.exe", base_flags),
    ]


def main():
    manifest = json.loads((MATCHING / "data/units.json").read_text(encoding="utf-8-sig"))
    externals = check.collect_externals(manifest)
    build = HERE / "build"
    build.mkdir(exist_ok=True)
    units = sorted({u for _, u, _ in SAMPLES})
    for label, compiler, flags in variants(manifest["flags"]):
        print(f"== {label}")
        for i, unit in enumerate(units):
            spec = manifest["units"][unit]
            obj = build / f"{label.split()[0]}_{abs(hash(label)) % 10000}_{i}.o"
            cmd = [str(ROOT / compiler), *flags, "-I", str(MATCHING / "include"), "-c",
                   str(MATCHING / "src" / unit), "-o", str(obj)]
            proc = subprocess.run(cmd, capture_output=True, text=True)
            if proc.returncode != 0:
                print(f"  {unit}: COMPILE FAILED: {proc.stderr.strip().splitlines()[-1]}")
                continue
            mapping = dict(externals)
            mapping.update({n: check.address(a) for n, a in spec.get("map", {}).items()})
            wanted = {a for _, u, a in SAMPLES if u == unit}
            pairs = [(n, check.address(a)) for n, a in spec["functions"].items()
                     if check.address(a) & 0xffffffff in wanted]
            results, _ = check_obj.compare(obj, pairs, mapping)
            kinds = {a: k for k, u, a in SAMPLES if u == unit}
            for name, addr, size, diffs, _ in results:
                state = "MATCH" if diffs == [] else ("missing" if diffs is None else f"{len(diffs)} words differ")
                print(f"  {kinds[addr & 0xffffffff]:10} {addr & 0xffffffff:x} {name}: {state}")


if __name__ == "__main__":
    main()
