
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(application SHARED "${SOURCES}")
target_link_libraries(application PRIVATE common_pch raylib windowMaker UImanager)
target_precompile_headers(application REUSE_FROM common_pch)