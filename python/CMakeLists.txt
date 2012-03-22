include_directories (../src)

set (PY_VALKYRIE_HEADERS ${HEADERS})
set (PY_VALKYRIE_SOURCES python.cpp)

#find_package (PythonLibs REQUIRED)
set (PYTHON_INCLUDE_DIRS "/opt/local//Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/")
set (PYTHON_LIBRARIES "/opt/local//Library/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib")
include_directories (${PYTHON_INCLUDE_DIRS})
add_library (pyvalkyrie SHARED ${PY_VALKYRIE_HEADERS} ${PY_VALKYRIE_SOURCES})
target_link_libraries (pyvalkyrie
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    valkyrie
)

