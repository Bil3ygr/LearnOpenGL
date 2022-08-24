cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

set(CAMERA_DIR camera)
set(COMMON_DIR common)
set(CONTROL_DIR control)
set(DRAWER_DIR drawer)
set(GAME_DIR game)
set(IMGUI_DIR imgui)
set(LIGHT_DIR light)
set(NODE_DIR node)
set(RENDER_DIR render)
set(SCENE_DIR scene)
set(UI_DIR ui)
set(UTILS_DIR utils)

message(STATUS "Configure ${SRC_DIR}")
aux_source_directory(. ALL_FILES)

message(STATUS "Add subdirectories")
add_subdirectory(${CAMERA_DIR})
add_subdirectory(${COMMON_DIR})
add_subdirectory(${CONTROL_DIR})
add_subdirectory(${DRAWER_DIR})
add_subdirectory(${GAME_DIR})
add_subdirectory(${LIGHT_DIR})
add_subdirectory(${NODE_DIR})
add_subdirectory(${RENDER_DIR})
add_subdirectory(${SCENE_DIR})
add_subdirectory(${UI_DIR})
add_subdirectory(${UTILS_DIR})

message(STATUS "Process ${IMGUI_DIR}")

file(GLOB HEADER_LIST "${IMGUI_DIR}/*.h")
file(GLOB SRC_LIST "${IMGUI_DIR}/*.cpp")
set(ALL_FILES ${ALL_FILES} ${HEADER_LIST} ${SRC_LIST})

set(BACKEND_HEADER_LIST
    "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h"
)
set(BACKEND_SRC_LIST
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
set(ALL_FILES ${ALL_FILES} ${BACKEND_HEADER_LIST} ${BACKEND_SRC_LIST})

if (APPLE)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(IMGUI_BACKENDS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
set(INCLUDE_DIR "${INCLUDE_DIR} ${IMGUI_INCLUDE_DIR} ${IMGUI_BACKENDS_INCLUDE_DIR}" PARENT_SCOPE)
endif ()

message(STATUS "Configure source files")
add_executable(${PROJECT_NAME} ${ALL_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

message(STATUS "Link static libraries")
# 链接lib
if (WIN32)
# set(LIB_FILES glfw3.lib)
# target_link_libraries(${PROJECT_NAME} ${LIB_FILES})
endif (WIN32)
if (APPLE)
endif (APPLE)
