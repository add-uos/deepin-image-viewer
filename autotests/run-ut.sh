#!/bin/bash
# SPDX-FileCopyrightText: 2026 UnionTech Software Technology Co., Ltd.
# SPDX-License-Identifier: GPL-3.0-or-later
#
# run-ut.sh - Build, run and measure coverage for the deepin-image-viewer
# standalone Google Test suite (qt-autotest-generator skill).
#
# Usage:
#   ./run-ut.sh            # configure + build + run + coverage
#   ./run-ut.sh --no-cov   # skip coverage
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
APP="$(cd "$HERE/.." && pwd)"
BUILD="$HERE/build"

# ---- Environment ----------------------------------------------------------
# The host may not have the OCR/ncnn/opencv/Qt6Svg dev packages installed
# system-wide. If the locally extracted prefix exists, use it; otherwise rely
# on the system packages (the CMakeLists is portable).
PREFIX="$HOME/.local/prefix/usr"
if [ -d "$PREFIX" ]; then
  export PKG_CONFIG_PATH="$PREFIX/lib/x86_64-linux-gnu/pkgconfig:${PKG_CONFIG_PATH:-}"
  export CMAKE_PREFIX_PATH="$PREFIX${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"
  export LD_LIBRARY_PATH="$PREFIX/lib/x86_64-linux-gnu${LD_LIBRARY_PATH:-}"
  export QT_EXTRA_INCLUDE_DIR="$PREFIX/include/x86_64-linux-gnu/qt6"
  export PATH="$PREFIX/bin:$PATH"
fi
export QT_QPA_PLATFORM="${QT_QPA_PLATFORM:-offscreen}"

# ---- Configure & build ----------------------------------------------------
cmake -S "$HERE" -B "$BUILD" -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
cmake --build "$BUILD" -j"$(nproc)"

# ---- Run (under a private D-Bus session so DBus tests pass) ---------------
if command -v dbus-run-session >/dev/null 2>&1; then
  dbus-run-session -- "$BUILD/deepin-image-viewer-autotest" "$@"
else
  "$BUILD/deepin-image-viewer-autotest" "$@"
fi
RC=$?
echo "test exit code: $RC"

# ---- Coverage -------------------------------------------------------------
if [ "${1:-}" != "--no-cov" ]; then
  if command -v lcov >/dev/null 2>&1; then
    lcov --capture --directory "$BUILD" --output-file "$BUILD/coverage.info" \
         --rc lcov_branch_coverage=0 --quiet || true
    lcov --extract "$BUILD/coverage.info" "*/deepin-image-viewer/src/src/*" \
         --output-file "$BUILD/coverage_app.info" --quiet || true
    echo "---- function coverage (application sources) ----"
    lcov --list "$BUILD/coverage_app.info" || true
    if command -v genhtml >/dev/null 2>&1; then
      genhtml "$BUILD/coverage_app.info" -o "$HERE/report" --quiet || true
      echo "HTML report: $HERE/report/index.html"
    fi
  else
    echo "lcov not found; skipping coverage"
  fi
fi

exit $RC
