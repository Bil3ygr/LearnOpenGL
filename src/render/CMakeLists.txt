cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${RENDER_DIR}")

file(GLOB RENDER_HEADER_LIST "*.h")
file(GLOB RENDER_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${RENDER_HEADER_LIST}
    ${RENDER_SRC_LIST}
    PARENT_SCOPE
)
