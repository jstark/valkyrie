include_directories (../src)

set (LUA_VALKYRIE_HEADERS )
set (LUA_VALKYRIE_SOURCES lua.cpp)

find_package (Lua51)
if (LUA51_FOUND)
    include_directories (${LUA_INCLUDE_DIR})
    add_library (lvalkyrie SHARED ${LUA_VALKYRIE_HEADERS} ${LUA_VALKYRIE_SOURCES})
    target_link_libraries (lvalkyrie ${LUA_LIBRARIES} valkyrie)
    install (TARGETS lvalkyrie DESTINATION "${PROJECT_BINARY_DIR}/lib")
    install (FILES solve.lua DESTINATION "${PROJECT_BINARY_DIR}/include")
endif (LUA51_FOUND)
