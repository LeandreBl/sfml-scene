cmake_minimum_required(VERSION 3.7)

project("SFML-scene" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

## Sets the library name
set(LIB_NAME "sfml-scene")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ggdb3 -Wall -Wextra -Weffc++ -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wlogical-op -Wuseless-cast")
set(CMAKE_CXX_FLAGS_DEBUG "-O3 -ggdb3 -Wall -Wextra -Wpedantic")

## Sources
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
file(GLOB_RECURSE LIB_HEADERS "include/*.hpp")

add_library(${LIB_NAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})
add_library(${LIB_NAME}-static STATIC ${LIB_SOURCES} ${LIB_HEADERS})
set_target_properties(${LIB_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIB_NAME}-static PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${LIB_NAME} PRIVATE "./include")
target_include_directories(${LIB_NAME}-static PRIVATE "./include")
