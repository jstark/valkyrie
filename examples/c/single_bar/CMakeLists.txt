project (single_bar)

set (SOURCES single_bar.c)

include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable (single_bar ${SOURCES})
target_link_libraries (single_bar valkyrie)
