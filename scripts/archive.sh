#!/bin/sh

[ -e scripts ] || { echo 'Execute this script from root dir.'; exit 1; }

OUT_DIR=target/bin

[ -e $OUT_DIR ] || mkdir -p $OUT_DIR

TAR_FILE=$OUT_DIR/fde-linux-x64.tar.gz

[ ! -e target/run ] && cd target && ln -s ../gn-out/run && cd ..

tar --dereference -cvzf $TAR_FILE target/run lib/* app/build/flutter_assets/*
