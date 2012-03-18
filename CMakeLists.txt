cmake_minimum_required (VERSION 2.8)

project (valkyrie)

## boost
find_package(BOOST 1.48.0 COMPONENTS python REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories (${Boost_LIBRARY_DIRS})
endif (Boost_FOUND)

set (HEADERS
    ${CMAKE_SOURCE_DIR}/src/valkyrie.h
    ${CMAKE_SOURCE_DIR}/src/version.h)

set (SOURCES
    ${CMAKE_SOURCE_DIR}/src/version.cpp)

#library sources
add_subdirectory (src)

#python modules
add_subdirectory (python)


## tests
enable_testing()
find_package (GTEST)
if (GTEST_FOUND)
    include_directories (${GTEST_INCLUDE_DIRS})
    add_subdirectory (tests)
endif (GTEST_FOUND)
