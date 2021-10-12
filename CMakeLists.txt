cmake_minimum_required(VERSION 3.8.0)
project(LearningOpenGL VERSION 0.1.0)

message(STATUS "Start configure project")

set(INCLUDE_DIR include)
set(LIB_DIR lib)
set(SRC_DIR src)
set(RES_DIR res)
set(SHADER_DIR shader)

# include目录和lib目录
message(STATUS "Add include directories and lib directories")
include_directories(${INCLUDE_DIR} ${SRC_DIR} ${SRC_DIR}/imgui ${SRC_DIR}/imgui/backends)
link_directories(${LIB_DIR})

# 拷贝资源
message(STATUS "Copy shaders and resources")
file(COPY ${SHADER_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${SRC_DIR})
file(COPY ${RES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${SRC_DIR})

# 子目录
message(STATUS "Process source codes")
add_subdirectory(${SRC_DIR})

message(STATUS "Setup settings")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
include(CPack)
# 设置启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
