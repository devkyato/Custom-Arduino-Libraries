"""Build a deterministic Arduino IDE library ZIP."""

from __future__ import annotations

import configparser
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DIST = ROOT / "dist"
INCLUDED = (
    "src",
    "examples",
    "docs",
    "README.md",
    "CHANGELOG.md",
    "RELEASE_NOTES.md",
    "CITATION.cff",
    "CONTRIBUTING.md",
    "CODE_OF_CONDUCT.md",
    "SECURITY.md",
    "LICENSE",
    "library.properties",
    "library.json",
    "keywords.txt",
)
FIXED_TIME = (2026, 1, 1, 0, 0, 0)


def library_version() -> str:
    parser = configparser.ConfigParser()
    text = "[library]\n" + (ROOT / "library.properties").read_text(encoding="utf-8")
    parser.read_string(text)
    return parser["library"]["version"]


def files_to_package() -> list[Path]:
    files: list[Path] = []
    for item in INCLUDED:
        path = ROOT / item
        if path.is_dir():
            files.extend(candidate for candidate in path.rglob("*") if candidate.is_file())
        else:
            files.append(path)
    return sorted(files, key=lambda path: path.as_posix())


def main() -> None:
    version = library_version()
    DIST.mkdir(exist_ok=True)
    output = DIST / f"ArduinoPatterns-{version}.zip"

    with zipfile.ZipFile(output, "w", compression=zipfile.ZIP_DEFLATED) as archive:
        for path in files_to_package():
            relative = path.relative_to(ROOT).as_posix()
            info = zipfile.ZipInfo(f"ArduinoPatterns/{relative}", FIXED_TIME)
            info.compress_type = zipfile.ZIP_DEFLATED
            info.external_attr = 0o100644 << 16
            archive.writestr(info, path.read_bytes())

    with zipfile.ZipFile(output) as archive:
        required = {
            "ArduinoPatterns/CITATION.cff",
            "ArduinoPatterns/docs/API.md",
            "ArduinoPatterns/library.properties",
            "ArduinoPatterns/src/ArduinoPatterns.h",
        }
        missing = required.difference(archive.namelist())
        if missing:
            raise RuntimeError(f"release archive is missing: {sorted(missing)}")

    print(output)


if __name__ == "__main__":
    main()
