cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${NODE_DIR}")

file(GLOB NODE_HEADER_LIST "*.h")
file(GLOB NODE_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${NODE_HEADER_LIST}
    ${NODE_SRC_LIST}
    PARENT_SCOPE
)
