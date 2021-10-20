cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

set(CAMERA_DIR camera)
set(DRAWER_DIR drawer)
set(SCENE_DIR scene)
set(UTILS_DIR utils)
set(IMGUI_DIR imgui)
set(UI_DIR ui)
set(COMMON_DIR common)
set(RENDEROBJECT_DIR renderobject)

message(STATUS "Configure ${SRC_DIR}")
aux_source_directory(. ALL_FILES)

message(STATUS "Add subdirectories")
add_subdirectory(${CAMERA_DIR})
add_subdirectory(${DRAWER_DIR})
add_subdirectory(${SCENE_DIR})
add_subdirectory(${UTILS_DIR})
add_subdirectory(${UI_DIR})
add_subdirectory(${COMMON_DIR})
add_subdirectory(${RENDEROBJECT_DIR})

message(STATUS "Process Imgui")

file(GLOB HEADER_LIST "${IMGUI_DIR}/*.h")
file(GLOB SRC_LIST "${IMGUI_DIR}/*.cpp")
set(ALL_FILES
    ${ALL_FILES}
    ${HEADER_LIST}
    ${SRC_LIST}
)

if (WIN32)
set(BACKEND_HEADER_LIST
    "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h"
)
set(BACKEND_SRC_LIST
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
set(ALL_FILES
    ${ALL_FILES}
    ${BACKEND_HEADER_LIST}
    ${BACKEND_SRC_LIST}
)
endif (WIN32)

message(STATUS "Configure source files")
add_executable(${PROJECT_NAME} ${ALL_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

message(STATUS "Link static libraries")
# 链接lib
if (WIN32)
set(LIB_FILES
    glfw3.lib
)
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})
endif (WIN32)
if (APPLE)
endif (APPLE)
