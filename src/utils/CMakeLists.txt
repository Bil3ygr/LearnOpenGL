cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${UTILS_DIR}")

file(GLOB UTILS_HEADER_LIST "${PUBLIC}/*.h")
file(GLOB UTILS_SRC_LIST "${PRIVATE}/*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${UTILS_HEADER_LIST}
    ${UTILS_SRC_LIST}
    PARENT_SCOPE
)
