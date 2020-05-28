cmake_minimum_required(VERSION 3.15.0)
project(MinesweeperPlusPlus)

add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${SOURCE_DIR}")
file(GLOB SOURCE_FILES
    "${SOURCE_DIR}/*.hpp"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/GameLogic/*.hpp"
    "${SOURCE_DIR}/GameLogic/*.cpp"
    "${SOURCE_DIR}/GameStates/*.hpp"
    "${SOURCE_DIR}/GameStates/*.cpp"
    "${SOURCE_DIR}/Graphics/*.hpp"
    "${SOURCE_DIR}/Graphics/*.cpp"
    "${SOURCE_DIR}/HelperSrc/*.hpp"
    "${SOURCE_DIR}/HelperSrc/*.cpp"
)

add_executable(game "${SOURCE_FILES}")
target_link_libraries(game ${CONAN_LIBS})
