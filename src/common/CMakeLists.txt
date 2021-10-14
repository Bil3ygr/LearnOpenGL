cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${COMMON_DIR}")

file(GLOB COMMON_HEADER_LIST "*.h")
file(GLOB COMMON_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${COMMON_HEADER_LIST}
    ${COMMON_SRC_LIST}
    PARENT_SCOPE
)
