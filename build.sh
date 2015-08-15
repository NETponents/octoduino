#!/bin/sh
echo "Octoduino automated builder."
echo "Copyright 2015 NETponents"
echo "Protected under the GPL v2.0"
echo "============================="
echo "Enter build args like this: -Dxxx_xxx_xxx"
echo "For example, -DCORE_STACK"
echo "For a full list of available options and their impact on performance, see https://github.com/NETponents/octoduino/wiki/Build-options"
read -e -p "BUILD_ARGS: " -i "-DBUILDPIPE_BNUM='Local'" BARGS
read -e -p "BUILD_TARGET: " -i "upload" BTARGET
read -e -p "BUILD_ENV: " -i "uno" BTARGET
echo "Starting build..."
platformio --SRC="/src" --BUILD_FLAGS=$BARGS --target=$BTARGET -- environment=$BENV -vvv
