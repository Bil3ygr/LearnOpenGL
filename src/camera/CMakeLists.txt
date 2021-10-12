cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${CAMERA_DIR}")

file(GLOB CAMERA_HEADER_LIST "${PUBLIC}/*.h")
file(GLOB CAMERA_SRC_LIST "${PRIVATE}/*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${CAMERA_HEADER_LIST}
    ${CAMERA_SRC_LIST}
    PARENT_SCOPE
)
