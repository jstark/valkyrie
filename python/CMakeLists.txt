include_directories (../src)

set (PY_VALKYRIE_HEADERS )
set (PY_VALKYRIE_SOURCES python.cpp)

find_package (PythonLibs REQUIRED)
include_directories (${PYTHON_INCLUDE_DIRS})
add_library (pyvalkyrie SHARED ${PY_VALKYRIE_HEADERS} ${PY_VALKYRIE_SOURCES})
target_link_libraries (pyvalkyrie
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)

