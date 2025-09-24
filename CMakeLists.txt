cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)

set(USE_GTK ON CACHE BOOL "use GTK file prompt or custom one")

find_package(PkgConfig)

if(${USE_GTK})
    set(myOrGtksCompilationUnits ${CMAKE_SOURCE_DIR}/common/src/GtkFilePrompt.cpp ${CMAKE_SOURCE_DIR}/common/src/GTKNotification.cpp)
    pkg_check_modules(gtk3 REQUIRED gtk+-3.0)
else()
    set(myOrGtksCompilationUnits FilePrompt.cpp)
endif()

pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)

project(Shittle)

include_directories(
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/editor/include
    ${SFML_INCLUDE_DIRS}
    ${gtk3_INCLUDE_DIRS}
)

message(STATUS "using ${fpCompUnit} as file prompt")

add_executable(
    editor
    ${myOrGtksCompilationUnits}
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
    ${CMAKE_SOURCE_DIR}/common/src/TextField.cpp
    ${CMAKE_SOURCE_DIR}/common/src/MulColor.cpp
    ${CMAKE_SOURCE_DIR}/common/src/Scaler.cpp
    ${CMAKE_SOURCE_DIR}/common/src/ScreenRatioScaler.cpp
	${CMAKE_SOURCE_DIR}/common/src/LevelSaveLoad.cpp
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
    ${SFML_LIBRARIES}
    ${gtk3_LIBRARIES}
)

target_compile_options(editor PUBLIC -Wall)
