cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(SFML_INCLUDE_DIR /usr/incude CACHE PATH "path to SFML include dir")
set(SFML_LIB_DIR /usr/lib/x86_64-linux-gnu/ CACHE PATH "path to SFML lib dir")
set(SFML_LIB_SUFFIX ".so" CACHE STRING "suffix for SFML libs")

project(Shittle)

include_directories(${CMAKE_SOURCE_DIR}/common/include ${CMAKE_SOURCE_DIR}/editor/include /usr/include/)

add_executable(
    editor
    ${CMAKE_SOURCE_DIR}/common/src/Button.cpp
    ${CMAKE_SOURCE_DIR}/common/src/InputState.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/FontResource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/ImageResource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/Resource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/ResourceFactory.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/Peg.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/RunEditor.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/main.cpp
)

target_link_libraries(
    editor 
    ${SFML_LIB_DIR}/libsfml-graphics${SFML_LIB_SUFFIX}
    ${SFML_LIB_DIR}/libsfml-window${SFML_LIB_SUFFIX}
    ${SFML_LIB_DIR}/libsfml-system${SFML_LIB_SUFFIX}
)