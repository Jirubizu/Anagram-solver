cmake_minimum_required(VERSION 2.8)

project(Anagram-Solver)
file (GLOB_RECURSE HEADERS src/*.h)
file (GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Anagram-Solver ${HEADERS} ${SOURCES})
set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)

set_target_properties (
    Anagram-Solver PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_FLAGS "-std=c++17 -Wall"
)
