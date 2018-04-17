#! /bin/bash

set -e # fail fast

BUILD_DIR=_build
MAKE_CMD="ninja -C $BUILD_DIR"

which cmake || { echo Install CMake first. ; exit 1; }
which ninja || {
  MAKE_CMD="make -C $BUILD_DIR"
  which make || { echo Install either ninja or make. ; exit 1; }
}

if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi
