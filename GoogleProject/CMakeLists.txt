cmake_minimum_required (VERSION 2.6)
 
project (textSearch)
 
 
#the version number
 
#set (composer_VERSION_MAJOR 1) 
#set (composer_VERSION_MINOR 0)
#set (database_VERSION_MAJOR 1) 
#set (database_VERSION_MINOR 0)
 
#set the compiler
#set (CMAKE_C_COMPILER_INIT CXX=g++-4.9)
 
#set the language library
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
 
#configure a header file to pass some of the CMake settings
#to the source code
 
#configure_file(
#        "${PROJECT_SOURCE_DIR}/composer.h.in"
#        "${PROJECT_SOURCE_DIR}/composer.h"     
#        )
 
#add the binary tree to the search path for include files
#so that we will find main.h
 
#include_directories("${PROJECT_BINARY_DIR}")
 
#add_library(composer_c STATIC composer.cpp)
#add_library(composer_h STATIC composer.h)
#add_library(database_c STATIC database.cpp)
#add_library(database_h STATIC database.h)
 
#add the executable
 
add_executable(textSearch textSearch.cpp)
 
 
#need to link the libraries that will be used to each other and to the "main" file
#target_link_libraries(composer_c composer_h)
#target_link_libraries(composer_h composer_c)
#target_link_libraries(database_c database_h)
#target_link_libraries(database_h database_c)

#target_link_libraries(database_h composer_c)
#target_link_libraries(database_c composer_h)
#target_link_libraries(composer_h database_c)
#target_link_libraries(composer_c database_h)

#target_link_libraries(main ${EXTRA_LIBS})
#target_link_libraries(main composer_c)
#target_link_libraries(main database_c)
 
 
#add the install targets
 
#install (TARGETS main DESTINATION bin)
 
#install (FILES "${PROJECT_BINARY_DIR}/composer.h"
 
#               DESTINATION include)

#install (FILES "${PROJECT_BINARY_DIR}/database.h"
 
#                DESTINATION include)                
 
#copy the books subdirectory files and put them into the directory #"books" inside the build folder "books"
file(COPY books/ DESTINATION books)