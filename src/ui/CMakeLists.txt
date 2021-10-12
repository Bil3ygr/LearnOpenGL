cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${UI_DIR}")

file(GLOB UI_HEADER_LIST "${PUBLIC}/*.h")
file(GLOB UI_SRC_LIST "${PRIVATE}/*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${UI_HEADER_LIST}
    ${UI_SRC_LIST}
    PARENT_SCOPE
)
