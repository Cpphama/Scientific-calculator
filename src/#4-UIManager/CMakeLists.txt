
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
"${CMAKE_SOURCE_DIR}/src/#5-logic/*.cpp")

add_library(UImanager SHARED "${SOURCES}")
target_include_directories(UImanager PRIVATE "${CMAKE_SOURCE_DIR}/src/#5-logic")
target_link_libraries(UImanager PRIVATE common_pch raylib)

target_precompile_headers(UImanager REUSE_FROM common_pch)
target_precompile_headers(UImanager REUSE_FROM eval_pch)

