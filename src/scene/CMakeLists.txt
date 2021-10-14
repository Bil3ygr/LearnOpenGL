cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${SCENE_DIR}")

file(GLOB SCENE_HEADER_LIST "*.h")
file(GLOB SCENE_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${SCENE_HEADER_LIST}
    ${SCENE_SRC_LIST}
    PARENT_SCOPE
)
