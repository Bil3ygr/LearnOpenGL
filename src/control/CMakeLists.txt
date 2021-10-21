cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${CONTROL_DIR}")

file(GLOB CONTROL_HEADER_LIST "*.h")
file(GLOB CONTROL_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${CONTROL_HEADER_LIST}
    ${CONTROL_SRC_LIST}
    PARENT_SCOPE
)
