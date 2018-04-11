#!/bin/sh

BASE_DIR=`dirname $PWD/..`

ENGINE_TARGET=host_release
ENGINE_SRC=$BASE_DIR/engine/src

FLUTTER_BIN=$BASE_DIR/flutter/bin/flutter

cd app && $FLUTTER_BIN build flx \
  --local-engine-src-path=$ENGINE_SRC \
  --local-engine=$ENGINE_TARGET
