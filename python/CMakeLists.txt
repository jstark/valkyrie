include_directories(../src)
include_directories("/Library/Frameworks/Python.framework/Versions/3.2/include/python3.2m")

set (PYVALKYRIE_SOURCES python.cpp)

add_library (pyvalkyrie SHARED ${PYVALKYRIE_SOURCES})

set (PYTHON_LIB "/Library/Frameworks/Python.framework/Versions/3.2/lib/libpython3.2.dylib")
target_link_libraries (pyvalkyrie ${PYTHON_LIB} valkyrie)
install (TARGETS pyvalkyrie DESTINATION "${PROJECT_BINARY_DIR}/lib")


