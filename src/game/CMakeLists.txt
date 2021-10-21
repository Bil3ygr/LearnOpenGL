cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${GAME_DIR}")

file(GLOB GAME_HEADER_LIST "*.h")
file(GLOB GAME_SRC_LIST "*.cpp")

set(ALL_FILES
    ${ALL_FILES}
    ${GAME_HEADER_LIST}
    ${GAME_SRC_LIST}
    PARENT_SCOPE
)
