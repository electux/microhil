#!/usr/bin/env bash
#
# @brief   Run static analysis: build, cppcheck, clang-tidy.
# @version ver.1.0
# @date    Sat May 16 09:42:09 AM CEST 2026
# @company None, free software to use 2026
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

OUT_DIR="${ROOT_DIR}/build/static-analysis"
mkdir -p "$OUT_DIR"

PKGCFG="$(pkg-config --cflags-only-I gtkmm-4.0 libserial 2>/dev/null || true)"

echo "[1/3] Building project (make -C build)"
make --directory=build

echo "[2/3] Running cppcheck"
CPPOUT="$OUT_DIR/cppcheck.txt"
cppcheck --enable=all --inconclusive --std=c++23 --force --inline-suppr -I. $PKGCFG . 2> "$CPPOUT" || true
echo "cppcheck output -> $CPPOUT"

echo "[3/3] Running clang-tidy-18 (cppcoreguidelines checks)"
CLANGOUT="$OUT_DIR/clang-tidy.txt"
echo "clang-tidy run started at $(date)" > "$CLANGOUT"

# If bear is available, optionally generate compile_commands.json (uncomment if desired)
if command -v bear >/dev/null 2>&1; then
    echo "Generating compile_commands.json with bear..."
    bear -- make --directory=build || true
fi

for f in $(find . -name '*.cc'); do
    echo "=== $f ===" >> "$CLANGOUT"
    clang-tidy-18 "$f" -checks='-*,cppcoreguidelines-*' -- -std=gnu++23 -I. -I.. $PKGCFG >> "$CLANGOUT" 2>&1 || true
done

echo "clang-tidy output -> $CLANGOUT"
echo "Done. Reports saved under $OUT_DIR"

