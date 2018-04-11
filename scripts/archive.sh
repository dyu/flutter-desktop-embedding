#!/bin/sh

[ -e scripts ] || { echo 'Execute this script from root dir.'; exit 1; }

OUT_DIR=target/bin

[ -e $OUT_DIR ] || mkdir -p $OUT_DIR

TAR_FILE=$OUT_DIR/fde-linux-x64.tar.gz

[ ! -e target/app ] && cd target && ln -s ../gn-out/flutter_embedder_example app && cd ..

tar --dereference -cvzf $TAR_FILE target/app lib/* app/build/flutter_assets/*
