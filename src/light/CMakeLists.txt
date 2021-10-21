cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${LIGHT_DIR}")

file(GLOB LIGHT_HEADER_LIST "*.h")
file(GLOB LIGHT_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${LIGHT_HEADER_LIST}
    ${LIGHT_SRC_LIST}
    PARENT_SCOPE
)
