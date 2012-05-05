project (single_bar)

set (SOURCES three_bar.c)

include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable (three_bar ${SOURCES})
target_link_libraries (three_bar valkyrie)
