"""Create matching/data/functions.csv from the baseline function inventory.

Every entry starts as U (undecompiled). Existing rows keep their quality and
name, so the script can be rerun safely. Size is the inventory's body byte
count.
"""
import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INVENTORY = ROOT / "analysis/source-map/update-main/functions.tsv"
OUTPUT = ROOT / "matching/data/functions.csv"


def main():
    existing = {}
    if OUTPUT.exists():
        with OUTPUT.open(newline="") as f:
            existing = {row["Address"]: row for row in csv.DictReader(f)}
    rows = []
    with INVENTORY.open(newline="") as f:
        for entry in csv.DictReader(f, delimiter="\t"):
            address = "0x" + entry["entry_address"].lower()
            old = existing.get(address)
            rows.append({
                "Address": address,
                "Quality": old["Quality"] if old else "U",
                "Size": entry["body_address_count"],
                "Name": old["Name"] if old else entry["qualified_name"],
            })
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    with OUTPUT.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["Address", "Quality", "Size", "Name"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    print(f"{len(rows)} functions written to {OUTPUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
