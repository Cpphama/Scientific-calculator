cmake_minimum_required(VERSION 4.0.2)

project(myproj VERSION  1.0 LANGUAGES CXX C)


#setting binrary out put
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)




add_library(common_pch STATIC "${CMAKE_SOURCE_DIR}/src/#0-commonpch/pch.cpp")
target_precompile_headers(common_pch 
PRIVATE
"${CMAKE_SOURCE_DIR}/#0-commonpch/pch.h"
"${CMAKE_SOURCE_DIR}/my_headers/applicationsConsts.h"
)


add_library(eval_pch STATIC "${CMAKE_SOURCE_DIR}/src/#0-commonpch/stackVectorPch.cpp")
target_precompile_headers(eval_pch PRIVATE 
"${CMAKE_SOURCE_DIR}/#0-commonpch/stackVectorPch.h"
"<cstdint>"
"<vector>"
"<cctype>"
"<stack>"
)






add_compile_options(

-Wall -Wextra -pedantic -Wshadow -Wconversion

-Wsign-conversion -Wnull-dereference

-Wold-style-cast -Wnon-virtual-dtor

-Wunused

)






#set(CMAKE_WIN32_EXECUTABLE True)




# Output directories for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")










set(ALL_HEADERS 

"${CMAKE_SOURCE_DIR}/src/#1-entry"
"${CMAKE_SOURCE_DIR}/src/#2-application"
"${CMAKE_SOURCE_DIR}/src/#3-windowMaker"
"${CMAKE_SOURCE_DIR}/src/#4-UImanager"

)



link_directories("${CMAKE_SOURCE_DIR}/lib")
include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/my_headers" "${ALL_HEADERS}")





add_subdirectory("src")