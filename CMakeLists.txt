cmake_minimum_required (VERSION 2.8)

project (valkyrie)

## boost
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.49.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories (${Boost_LIBRARY_DIRS})
endif (Boost_FOUND)

set (HEADERS
    ${CMAKE_SOURCE_DIR}/src/valkyrie.h
    ${CMAKE_SOURCE_DIR}/src/version.h
    ${CMAKE_SOURCE_DIR}/src/node.h
    ${CMAKE_SOURCE_DIR}/src/model.h
    ${CMAKE_SOURCE_DIR}/src/material.h
    ${CMAKE_SOURCE_DIR}/src/property.h
    ${CMAKE_SOURCE_DIR}/src/entity.h
    ${CMAKE_SOURCE_DIR}/src/rod.h
    ${CMAKE_SOURCE_DIR}/src/spc.h)

set (SOURCES
    ${CMAKE_SOURCE_DIR}/src/version.cpp
    ${CMAKE_SOURCE_DIR}/src/valkyrie.cpp
    ${CMAKE_SOURCE_DIR}/src/node.cpp
    ${CMAKE_SOURCE_DIR}/src/model.cpp
    ${CMAKE_SOURCE_DIR}/src/material.cpp
    ${CMAKE_SOURCE_DIR}/src/property.cpp
    ${CMAKE_SOURCE_DIR}/src/rod.cpp
    ${CMAKE_SOURCE_DIR}/src/spc.cpp)

#library sources
add_subdirectory (src)

#lua modules
add_subdirectory (lua)

## tests
enable_testing()
find_package (GTEST)
if (GTEST_FOUND)
    include_directories (${GTEST_INCLUDE_DIRS})
    add_subdirectory (tests)
endif (GTEST_FOUND)
