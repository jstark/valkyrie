include_directories (../src)

set (LUA_VALKYRIE_HEADERS )
set (LUA_VALKYRIE_SOURCES lua.cpp)

find_package (Lua51)
if (LUA51_FOUND)
    include_directories (${LUA_INCLUDE_DIR})
    add_library (luavalkyrie SHARED ${LUA_VALKYRIE_HEADERS} ${LUA_VALKYRIE_SOURCES})
    target_link_libraries (luavalkyrie ${LUA_LIBRARIES} valkyrie)
endif (LUA51_FOUND)
