#!/bin/sh

CURRENT_DIR=$PWD
# locate
if [ ! -n "$BASH_SOURCE" ]; then
    SCRIPT_DIR=`dirname "$(readlink -f "$0")"`
else
    F=$BASH_SOURCE
    while [ -h "$F" ]; do
        F="$(readlink "$F")"
    done
    SCRIPT_DIR=`dirname "$F"`
fi

cd $SCRIPT_DIR

GIT_CLONE='git clone --depth 1 --single-branch -b'

mkdir -p deps && cd deps

[ -e glfw ] || $GIT_CLONE gn https://github.com/dyu/glfw.git
[ -e jsoncpp ] || $GIT_CLONE gn https://github.com/dyu/jsoncpp.git

