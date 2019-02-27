#! /bin/bash

set -e

which xcodebuild || { echo Install Xcode via AppStore. ; exit 1; }
which cmake || { echo Install CMake via Homebrew. ; exit 1; }
which lua || { echo Install Lua via Homebrew ; exit 1; }

IRRLICHT_DIR_NAME=irrlicht-1.8.1
IRRLICHT_PACKAGE_NAME="$IRRLICHT_DIR_NAME".zip
IRRLICHT_DOWNLOAD=http://downloads.sourceforge.net/irrlicht/$IRRLICHT_PACKAGE_NAME
IRRKLANG_DIR_NAME=irrKlang-1.5.0
IRRKLANG_PACKAGE_NAME=irrKlang-32bit-1.5.0.zip
IRRKLANG_DOWNLOAD=http://www.ambiera.at/downloads/$IRRKLANG_PACKAGE_NAME

pushd Debug

  # Download and build dependencies:
  mkdir -p dependencies
  pushd dependencies

    test -f "$IRRLICHT_PACKAGE_NAME" || curl -LO "$IRRLICHT_DOWNLOAD"
    test -f "$IRRKLANG_PACKAGE_NAME" || curl -LO "$IRRKLANG_DOWNLOAD"

    test -d "$IRRLICHT_DIR_NAME" || unzip "$IRRLICHT_PACKAGE_NAME"
    test -d "$IRRKLANG_DIR_NAME" || unzip "$IRRKLANG_PACKAGE_NAME"

    pushd $IRRLICHT_DIR_NAME/source/Irrlicht/MacOSX

      IRRLICHT_BUILD_DIR=$PWD/BD
      mkdir -p "$IRRLICHT_BUILD_DIR"
      xcodebuild -configuration Release \
      	         CONFIGURATION_BUILD_DIR="$IRRLICHT_BUILD_DIR"

    popd

    IRRKLANG_PATH=$PWD/$IRRKLANG_DIR_NAME

  popd

  # Prepaire to build:

  mkdir -p BD
  pushd BD

  cmake ../..

  ln -fs "$PWD/../CONFIG.CFG" .
  ln -fs "$PWD/../GFX" .
  ln -fs "$PWD/../SAVEGAMES" .
  ln -fs "$PWD/../SCRIPTS" .
  ln -fs "$PWD/../SFX" .

  popd
popd


cat << EOF
================================================================================

Whats next?

go to build directory:
  $ cd Debug/BD
build with:
  $ make
run game with:
  $ DYLD_LIBRARY_PATH=$IRRLICHT_BUILD_DIR:$IRRKLANG_PATH/bin/macosx-gcc/ \
open Spiel.app"
EOF
