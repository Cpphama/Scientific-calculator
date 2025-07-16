
add_executable(Calculator "${CMAKE_CURRENT_SOURCE_DIR}/#1-entry/entry.cpp")
target_include_directories(Calculator PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/#2-application")




add_subdirectory("#2-application")
add_subdirectory("#3-windowMaker")
add_subdirectory("#4-UIManager")



target_link_libraries(Calculator common_pch -lraylib application windowMaker UImanager) 
target_precompile_headers(Calculator REUSE_FROM common_pch)

