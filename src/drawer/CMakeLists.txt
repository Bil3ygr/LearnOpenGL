cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${DRAWER_DIR}")

file(GLOB DRAWER_HEADER_LIST "${PUBLIC}/*.h")
file(GLOB DRAWER_SRC_LIST "${PRIVATE}/*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${DRAWER_HEADER_LIST}
    ${DRAWER_SRC_LIST}
    PARENT_SCOPE
)
