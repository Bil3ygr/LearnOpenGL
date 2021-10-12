cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Configure ${IMGUI_DIR}")

file(GLOB HEADER_LIST "*.h")
file(GLOB SRC_LIST "*.cpp")

if (WIN32)
set(BACKEND_HEADER_LIST
    "imgui/backends/imgui_impl_glfw.h"
    "imgui/backends/imgui_impl_opengl3.h"
    "imgui/backends/imgui_impl_opengl3_loader.h"
)
set(BACKEND_SRC_LIST
    "imgui/backends/imgui_impl_glfw.cpp"
    "imgui/backends/imgui_impl_opengl3.cpp"
)
set(ALL_FILES
    ${ALL_FILES}
    ${HEADER_LIST}
    ${SRC_LIST}
    ${BACKEND_HEADER_LIST}
    ${BACKEND_SRC_LIST}
    PARENT_SCOPE
)
else ()
set(ALL_FILES
    ${ALL_FILES}
    ${HEADER_LIST}
    ${SRC_LIST}
    PARENT_SCOPE
)
endif (WIN32)
