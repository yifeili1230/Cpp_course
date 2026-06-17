#!/usr/bin/env bash
set -euo pipefail

compiler="${CXX:-clang++}"
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
lecture_dir="$(cd "${script_dir}/.." && pwd)"
build_dir="${lecture_dir}/build/manual"

mkdir -p "${build_dir}"

echo "[1/5] Pre-processing: src/main.cpp -> ${build_dir}/main.i"
"${compiler}" -std=c++17 -I"${lecture_dir}/include" -E "${lecture_dir}/src/main.cpp" -o "${build_dir}/main.i"

echo "[2/5] Compilation: ${build_dir}/main.i -> ${build_dir}/main.s"
"${compiler}" -std=c++17 -x c++-cpp-output -S "${build_dir}/main.i" -o "${build_dir}/main.s"

echo "[3/5] Assembly: ${build_dir}/main.s -> ${build_dir}/main.o"
"${compiler}" -c "${build_dir}/main.s" -o "${build_dir}/main.o"

echo "[4/5] Static library: src/tools.cpp -> liblecture01_tools.a"
"${compiler}" -std=c++17 -I"${lecture_dir}/include" -c "${lecture_dir}/src/tools.cpp" -o "${build_dir}/tools.o"
ar rcs "${build_dir}/liblecture01_tools.a" "${build_dir}/tools.o"

echo "[5/5] Linking: main.o + liblecture01_tools.a -> lecture01_manual_app"
"${compiler}" -std=c++17 "${build_dir}/main.o" -L"${build_dir}" -llecture01_tools \
    -o "${build_dir}/lecture01_manual_app"

echo
echo "Run it with: ${build_dir}/lecture01_manual_app"
