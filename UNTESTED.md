# Untested changes

## 1.7.7-a1: new UI languages, Windows installer in all languages, menu comment (2026-10-11, a128)

Committed without a package build or any run of the program, on the owner's instruction. The Czech translation was
reviewed and approved by the owner.

- **New translations** `src/i18n/q4os-imager_{cs,es,hu,pl,pt,he,id,uk}.ts` (135/135 each), registered in
  `src/CMakeLists.txt` (`TRANSLATIONS`) and `src/i18n/translations.qrc`. `pt` carries Brazilian Portuguese: the
  language list matches only the first part of the system locale (`pt_BR` -> `pt`), so a `pt_BR` file would load but
  never be preselected.
  Verified without a build: every placeholder (`%1`, `%2`, `%1%`) and `<br>`/`<b>` tag matches the English source;
  Qt5 `lrelease` compiles all eight with 0 unfinished.
- **Windows installer** (`src/windows/q4os-imager.nsi.in`): `Unicode true` added (it was an ANSI build), and
  21 `MUI_LANGUAGE`s with `termMsg`/`stopMsg`/`win7Msg` in each (was English, Dutch, Italian).
  Verified without a build: a stub installer with exactly this language block compiles with makensis 3.11, no warnings.
- **Linux menu entry** (`src/linux/q4os-imager.desktop`): `Comment` "Write Q4OS images to a USB drive or SD card"
  (was just "Q4OS Imager") plus 20 translations. `desktop-file-validate` passes.
- Version 1.7.7-a1 (`debian/changelog`, `IMAGER_VERSION_STR`/`CSV` in `src/CMakeLists.txt`).

**To test before publishing** (then delete this item):
1. Build (deb12 amd64 + deb14 per `q4pkg.conf`); the build must embed all 21 `.qm` files.
2. Linux: start with `LANG=cs_CZ.UTF-8` (and one RTL language, `he_IL.UTF-8`) - UI in that language, language menu
   shows the new entries with their native names and preselects the system language; check the longest strings
   (buttons, the no-browser popup, the "written to" message) fit; menu entry shows the translated comment.
3. Windows (offline VM, Czech): the NSIS installer pages and the imager UI are in Czech; the Italian and Dutch
   installer texts still display correctly after the Unicode switch; the Windows CI build passes.
4. Then the usual publish (P2-P7), the GitHub release and the Imager list `latest_version` 1.7.7.
