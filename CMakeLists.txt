cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)

set(SFML_INCLUDE_DIR /usr/incude CACHE PATH "path to SFML include dir")
set(SFML_LIB_DIR /usr/lib/x86_64-linux-gnu/ CACHE PATH "path to SFML lib dir")
set(SFML_LIB_SUFFIX ".so" CACHE STRING "suffix for SFML libs")

project(Shittle)


find_package(PkgConfig REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GRAPHENE REQUIRED graphene-1.0)
pkg_check_modules(X11 REQUIRED x11)

include_directories(
        ${CMAKE_SOURCE_DIR}/common/include
        ${CMAKE_SOURCE_DIR}/editor/include
        /usr/include
        /usr/include/x86_64-linux-gnu/qt6
        /usr/lib/x86_64-linux-gnu/glib-2.0/include
        /usr/include/cairo
        /usr/include/pango-1.0
        /usr/include/harfbuzz
        /usr/include/gdk-pixbuf-2.0
        ${GLIB_INCLUDE_DIRS}
        ${GRAPHENE_INCLUDE_DIRS}
        ${GTK3_INCLUDE_DIRS}
        ${X11_INCLUDE_DIRS}
    )

add_executable(
    editor
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
    ${CMAKE_SOURCE_DIR}/common/src/FilePrompt.cpp
    ${CMAKE_SOURCE_DIR}/common/src/LevelSaver.cpp
    ${CMAKE_SOURCE_DIR}/common/src/TextFeild.cpp
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
    Qt6::Widgets
    ${GTK3_LIBRARIES}
    ${GRAPHENE_LIBRARIES}
    ${X11_LIBRARIES}
)

target_compile_options(editor PUBLIC -Wall -DUSE_GTK)
