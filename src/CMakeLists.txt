add_library (valkyrie SHARED ${HEADERS} ${SOURCES})
set_target_properties (valkyrie PROPERTIES
    SOVERSION 1.0
    VERSION 1.0)

