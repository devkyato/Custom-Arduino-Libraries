"""Validate release versions and Zenodo's restricted HTML description."""

from __future__ import annotations

import json
import re
from html.parser import HTMLParser
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ALLOWED_TAGS = {"p", "h2", "ul", "li", "pre", "code", "a", "strong"}
REQUIRED_SECTIONS = {
    "Overview",
    "Capabilities",
    "Installation",
    "Quick start",
    "Applications",
    "Compatibility, safety, and limitations",
    "Documentation",
    "Related software",
    "Citation",
}


class DescriptionValidator(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.errors: list[str] = []
        self.headings: list[str] = []
        self._in_h2 = False

    def handle_starttag(
        self, tag: str, attrs: list[tuple[str, str | None]]
    ) -> None:
        if tag not in ALLOWED_TAGS:
            self.errors.append(f"disallowed HTML tag: {tag}")
        if tag == "a":
            if {name for name, _ in attrs} - {"href"}:
                self.errors.append("links may only use the href attribute")
        elif attrs:
            self.errors.append(f"attributes are not allowed on {tag}")
        self._in_h2 = tag == "h2"

    def handle_endtag(self, tag: str) -> None:
        if tag not in ALLOWED_TAGS:
            self.errors.append(f"disallowed closing tag: {tag}")
        if tag == "h2":
            self._in_h2 = False

    def handle_data(self, data: str) -> None:
        if self._in_h2:
            self.headings.append(data.strip())


def property_version() -> str:
    text = (ROOT / "library.properties").read_text(encoding="utf-8")
    match = re.search(r"^version=(.+)$", text, re.MULTILINE)
    if not match:
        raise ValueError("library.properties has no version")
    return match.group(1)


def main() -> None:
    version = property_version()
    zenodo = json.loads((ROOT / ".zenodo.json").read_text(encoding="utf-8"))
    library_json = json.loads((ROOT / "library.json").read_text(encoding="utf-8"))
    cff = (ROOT / "CITATION.cff").read_text(encoding="utf-8")
    readme = (ROOT / "README.md").read_text(encoding="utf-8")

    assert version == "1.0.2"
    assert zenodo["version"] == version
    assert library_json["version"] == version
    assert re.search(rf"^version: {re.escape(version)}$", cff, re.MULTILINE)
    assert f"ArduinoPatterns {version}" in readme
    assert zenodo["creators"] == [
        {"name": "@dev.mako (devkyato)", "affiliation": "MATA Company"}
    ]
    assert {"name": "Cursor Agent", "type": "Other"} in zenodo["contributors"]

    parser = DescriptionValidator()
    parser.feed(zenodo["description"])
    parser.close()
    missing = REQUIRED_SECTIONS.difference(parser.headings)
    if parser.errors or missing:
        raise ValueError(
            f"invalid Zenodo description: errors={parser.errors}, "
            f"missing sections={sorted(missing)}"
        )

    print(f"metadata valid for ArduinoPatterns {version}")


if __name__ == "__main__":
    main()
