cmake_minimum_required(VERSION 2.8.12)
project(Untitled)

add_definitions("-std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

#include(${PARENT_DIR}/conan/conanbuildinfo.cmake)
#conan_basic_setup()

file(GLOB Game_SOURCES ${PARENT_DIR}/src/*.cpp)
file(GLOB Game_HEADERS ${PARENT_DIR}/inc/*.hpp)

set (Game_INCLUDE_DIRS "")
foreach (_headerFile ${Game_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Game_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Game_INCLUDE_DIRS)

set(EXECUTABLE_OUTPUT_PATH ${PARENT_DIR}/bin/debug)

add_executable (GameExe ${Game_SOURCES})
target_include_directories(GameExe PRIVATE ${Game_INCLUDE_DIRS})
