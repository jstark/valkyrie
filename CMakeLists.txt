cmake_minimum_required (VERSION 2.6)

project (valkyrie)

## boost
find_package(BOOST 1.48.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

set (HEADERS
    ${CMAKE_SOURCE_DIR}/src/version.h)

set (SOURCES
    ${CMAKE_SOURCE_DIR}/src/version.cpp)

add_subdirectory (src)

## tests
enable_testing()
find_package (GTEST)
if (GTEST_FOUND)
    include_directories (${GTEST_INCLUDE_DIRS})
    add_subdirectory (tests)
endif (GTEST_FOUND)
