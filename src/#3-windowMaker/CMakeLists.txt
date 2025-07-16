
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(windowMaker SHARED "${SOURCES}")

target_link_libraries(windowMaker PRIVATE common_pch raylib)

target_precompile_headers(windowMaker REUSE_FROM common_pch)
