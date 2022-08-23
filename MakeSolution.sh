# !/bin/bash

BUILD_DIR="build"
RES_DIR="res"
GENERATOR="Xcode"
XCODEPROJ="LearningOpenGL.xcodeproj"

if [ ! -d "$BUILD_DIR" ]; then
	mkdir $BUILD_DIR
fi

if [ ! -d "$RES_DIR" ]; then
	mkdir $RES_DIR
fi

cd $BUILD_DIR

cmake -G $GENERATOR ..

# auto open project
if [ -e "$XCODEPROJ" ]; then
	open $XCODEPROJ
fi

exit
