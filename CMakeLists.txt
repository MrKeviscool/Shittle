cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)

set(SFML_INCLUDE_DIR /usr/incude CACHE PATH "path to SFML include dir")
set(SFML_LIB_DIR /usr/lib/x86_64-linux-gnu/ CACHE PATH "path to SFML lib dir")
set(SFML_LIB_SUFFIX ".so" CACHE STRING "suffix for SFML libs")
set(USE_GTK ON CACHE BOOL "use GTK file prompt or custom one")

if(${USE_GTK})
    set(fpCompUnit "GtkFilePrompt.cpp")
    find_package(PkgConfig)
    pkg_check_modules(gtk3 REQUIRED gtk+-3.0)
else()
    set(fpCompUnit "FilePrompt.cpp")
endif()

project(Shittle)

include_directories(
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/editor/include
    /usr/include
    ${gtk3_INCLUDE_DIRS}
)

message(STATUS "using ${fpCompUnit} as file prompt")

add_executable(
    editor
    ${CMAKE_SOURCE_DIR}/common/src/${fpCompUnit}
    ${CMAKE_SOURCE_DIR}/common/src/Button.cpp
    ${CMAKE_SOURCE_DIR}/common/src/InputState.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager.cpp
    ${CMAKE_SOURCE_DIR}/common/src/Algorithms.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/FontResource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/ImageResource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/Resource.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ResourceManager/ResourceFactory.cpp
    ${CMAKE_SOURCE_DIR}/common/src/FileStreamCommon.cpp
    ${CMAKE_SOURCE_DIR}/common/src/FilesystemCommon.cpp
    ${CMAKE_SOURCE_DIR}/common/src/LevelSaver.cpp
    ${CMAKE_SOURCE_DIR}/common/src/TextField.cpp
    ${CMAKE_SOURCE_DIR}/common/src/MulColor.cpp
    ${CMAKE_SOURCE_DIR}/common/src/Scaler.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/Peg.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/RunEditor.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/CursorType.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/PegCommon.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/SelectCommon.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/DrawCommon.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/SelectedPeg.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/CursorType.cpp
    ${CMAKE_SOURCE_DIR}/editor/src/main.cpp
)

target_link_libraries(
    editor 
    ${SFML_LIB_DIR}/libsfml-graphics${SFML_LIB_SUFFIX}
    ${SFML_LIB_DIR}/libsfml-window${SFML_LIB_SUFFIX}
    ${SFML_LIB_DIR}/libsfml-system${SFML_LIB_SUFFIX}
    ${gtk3_LIBRARIES}
)

target_compile_options(editor PUBLIC -Wall)
