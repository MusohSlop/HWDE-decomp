"""Draw the matching progress as a treemap.

Reads data/functions.csv and writes docs/progress.png: every inventory function of main is a
rectangle sized by its byte size, grouped into 64 KB address blocks. Green is an exact match (O),
blue a near miss (m or M), dark grey not done. The image holds only addresses, sizes and status.
Also prints the summary line and, with --readme, refreshes it in README.md.

    python -B tools/progress_map.py [--readme]
"""
import argparse
import csv
import re
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

MATCHING = Path(__file__).resolve().parents[1]
BASE = 0x7100000000
BLOCK = 0x10000
WIDTH, HEIGHT, HEADER = 1600, 900, 44
BACKGROUND = (22, 24, 28)
COLOURS = {"match": (24, 200, 24), "near": (30, 120, 190), "open": (52, 52, 54)}
BORDER = (22, 24, 28)


def squarify(sizes, x, y, w, h):
    """Squarified treemap: returns one (x, y, w, h) per size, sizes sorted descending."""
    rects = []
    total = float(sum(sizes))
    if total <= 0 or w <= 0 or h <= 0:
        return [(x, y, 0, 0)] * len(sizes)
    scaled = [s * w * h / total for s in sizes]
    i = 0
    while i < len(scaled):
        short = min(w, h)
        row = [scaled[i]]
        j = i + 1

        def worst(r):
            s = sum(r)
            return max(max(s * s / (short * short * v), short * short * v / (s * s)) for v in r)

        while j < len(scaled) and worst(row + [scaled[j]]) <= worst(row):
            row.append(scaled[j])
            j += 1
        s = sum(row)
        if w >= h:
            col = s / h
            cy = y
            for v in row:
                rh = v / col
                rects.append((x, cy, col, rh))
                cy += rh
            x += col
            w -= col
        else:
            rw = s / w
            cx = x
            for v in row:
                cw = v / rw
                rects.append((cx, y, cw, rw))
                cx += cw
            y += rw
            h -= rw
        i = j
    return rects


def load():
    blocks = {}
    totals = {"match": [0, 0], "near": [0, 0], "open": [0, 0]}
    with (MATCHING / "data/functions.csv").open(newline="") as f:
        for row in csv.DictReader(f):
            addr = int(row["Address"], 16) - BASE
            size = int(row["Size"])
            quality = row["Quality"]
            status = "match" if quality == "O" else "near" if quality in ("m", "M") else "open"
            totals[status][0] += 1
            totals[status][1] += size
            if size > 0:
                blocks.setdefault(addr // BLOCK, []).append((size, status))
    return blocks, totals


def summary(totals):
    funcs = sum(v[0] for v in totals.values())
    size = sum(v[1] for v in totals.values())
    m_funcs, m_bytes = totals["match"]
    n_funcs, n_bytes = totals["near"]
    return (f"{m_bytes / size * 100:.2f}% of bytes ({m_bytes:,} of {size:,}) and "
            f"{m_funcs / funcs * 100:.2f}% of functions ({m_funcs:,} of {funcs:,}) match exactly; "
            f"{n_funcs:,} more are near misses")


def draw(blocks, totals, path):
    image = Image.new("RGB", (WIDTH, HEIGHT), BACKGROUND)
    pen = ImageDraw.Draw(image)
    try:
        font = ImageFont.truetype("arial.ttf", 18)
    except OSError:
        font = ImageFont.load_default()
    pen.text((12, 12), "HWDE main: " + summary(totals), fill=(230, 230, 230), font=font)
    keys = sorted(blocks, key=lambda k: -sum(s for s, _ in blocks[k]))
    outer = squarify([sum(s for s, _ in blocks[k]) for k in keys], 0, HEADER, WIDTH, HEIGHT - HEADER)
    for key, (bx, by, bw, bh) in zip(keys, outer):
        funcs = sorted(blocks[key], key=lambda f: -f[0])
        inner = squarify([s for s, _ in funcs], bx + 1, by + 1, bw - 2, bh - 2)
        for (size, status), (fx, fy, fw, fh) in zip(funcs, inner):
            x0, y0 = int(round(fx)), int(round(fy))
            x1, y1 = int(round(fx + fw)) - 1, int(round(fy + fh)) - 1
            if x1 < x0 or y1 < y0:
                continue
            if x1 - x0 >= 2 and y1 - y0 >= 2:
                pen.rectangle([x0, y0, x1, y1], fill=COLOURS[status], outline=(30, 30, 32))
            else:
                pen.rectangle([x0, y0, x1, y1], fill=COLOURS[status])
        if bw >= 2 and bh >= 2:
            pen.rectangle([int(bx), int(by), int(bx + bw) - 1, int(by + bh) - 1], outline=BORDER, width=2)
    image = image.convert("P", palette=Image.ADAPTIVE, colors=16)
    path.parent.mkdir(parents=True, exist_ok=True)
    image.save(path, optimize=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--readme", action="store_true")
    args = parser.parse_args()
    blocks, totals = load()
    out = MATCHING / "docs/progress.png"
    draw(blocks, totals, out)
    line = summary(totals)
    print(line)
    print(f"{out.relative_to(MATCHING)}: {out.stat().st_size:,} bytes")
    if args.readme:
        readme = MATCHING / "README.md"
        text = readme.read_text(encoding="utf-8")
        text = re.sub(r"<!-- progress -->.*?<!-- /progress -->",
                      f"<!-- progress -->\n![Progress map](docs/progress.png)\n\n{line}. Green: exact match, "
                      f"blue: near miss, grey: not done; one rectangle per function, sized by bytes, "
                      f"grouped into 64 KB address blocks.\n<!-- /progress -->", text, flags=re.S)
        readme.write_text(text, encoding="utf-8", newline="\n")


if __name__ == "__main__":
    main()
