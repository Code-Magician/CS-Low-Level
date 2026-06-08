cmake_minimum_required(VERSION 3.20)

project(MemoryVisualizer C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/Src/*.c"
    "${CMAKE_SOURCE_DIR}/Src/main.c"
)

add_executable(
    MemoryVisualizer
    ${SOURCES}
 "Include/UI/panel.h" "Src/UI/panel.c")

target_include_directories(
    MemoryVisualizer
    PRIVATE
        Include/Core
        Include/Memory
        Include/UI
)

find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

target_link_libraries(
    MemoryVisualizer
    PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)