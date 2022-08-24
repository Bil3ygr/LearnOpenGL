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
if (WIN32)
include_directories(${INCLUDE_DIR} ${SRC_DIR} ${SRC_DIR}/imgui ${SRC_DIR}/imgui/backends)
link_directories(${LIB_DIR})
elseif (APPLE)
set(CXX_LANGUAGE_STANDRARD "gnu++17")
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLFW_INCLUDE_DIR /opt/homebrew/Cellar/glfw/3.3.6/include)
set(BOOST_INCLUDE_DIR /opt/homebrew/Cellar/boost/1.79.0_1/include)
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR} ${PROJECT_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${BOOST_INCLUDE_DIR}")
set(GLFW_LIB_DIR /opt/homebrew/Cellar/glfw/3.3.6/lib)
set(BOOST_LIB_DIR /opt/homebrew/Cellar/boost/1.79.0_1/lib)
set(LIB_DIR "${GLFW_LIB_DIR} ${BOOST_LIB_DIR}")
set(GLFW_LINKER_FLAG -lglfw.3)
endif ()

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

if (WIN32)
set(LIB_FILES glfw3.lib)
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
elseif (APPLE)
# https://help.apple.com/xcode/mac/current/#/itcaec37c2a6
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD ${CXX_LANGUAGE_STANDRARD})
set(CMAKE_XCODE_ATTRIBUTE_HEADER_SEARCH_PATHS ${INCLUDE_DIR})
set(CMAKE_XCODE_ATTRIBUTE_LIBRARY_SEARCH_PATHS ${LIB_DIR})
set(CMAKE_XCODE_ATTRIBUTE_OTHER_LDFLAGS ${GLFW_LINKER_FLAG})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_SCHEME_EXECUTABLE ${PROJECT_NAME})
endif ()
