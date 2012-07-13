cmake_minimum_required (VERSION 2.8)

project (valkyrie)

set (HEADERS
    ${CMAKE_SOURCE_DIR}/src/valkyrie.h
    ${CMAKE_SOURCE_DIR}/src/version.h
    ${CMAKE_SOURCE_DIR}/src/node.h
    ${CMAKE_SOURCE_DIR}/src/model.h
    ${CMAKE_SOURCE_DIR}/src/material.h
    ${CMAKE_SOURCE_DIR}/src/property.h
    ${CMAKE_SOURCE_DIR}/src/entity.h
    ${CMAKE_SOURCE_DIR}/src/rod.h
    ${CMAKE_SOURCE_DIR}/src/spc.h
    ${CMAKE_SOURCE_DIR}/src/force.h
    ${CMAKE_SOURCE_DIR}/src/staticanalysis.h)

set (SOURCES
    ${CMAKE_SOURCE_DIR}/src/version.cpp
    ${CMAKE_SOURCE_DIR}/src/valkyrie.cpp
    ${CMAKE_SOURCE_DIR}/src/node.cpp
    ${CMAKE_SOURCE_DIR}/src/model.cpp
    ${CMAKE_SOURCE_DIR}/src/material.cpp
    ${CMAKE_SOURCE_DIR}/src/property.cpp
    ${CMAKE_SOURCE_DIR}/src/rod.cpp
    ${CMAKE_SOURCE_DIR}/src/spc.cpp
    ${CMAKE_SOURCE_DIR}/src/force.cpp
    ${CMAKE_SOURCE_DIR}/src/staticanalysis.cpp)

#Eigen
include_directories ("/Users/john/Develop/Local/include")

#library sources
add_subdirectory (src)

#lua modules
add_subdirectory (lua)

#doc
add_subdirectory (doxygen)

#examples
add_subdirectory (examples)

## tests
enable_testing()
find_package (GTEST)
if (GTEST_FOUND)
    include_directories (${GTEST_INCLUDE_DIRS})
    add_subdirectory (tests)
endif (GTEST_FOUND)
