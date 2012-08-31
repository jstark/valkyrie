add_library (valkyrie SHARED ${HEADERS} ${SOURCES})
set_target_properties (valkyrie PROPERTIES
    SOVERSION 1.1
    VERSION 1.1)
install (TARGETS valkyrie DESTINATION "${PROJECT_BINARY_DIR}/lib")
install (FILES valkyrie.h DESTINATION "${PROJECT_BINARY_DIR}/include")
