cmake_minimum_required( VERSION 3.22.1 )

set( CMAKE_CXX_COMPILER          x86_64-w64-mingw32-g++-posix )
set( CMAKE_CXX_STANDARD_REQUIRED                           ON )
set( CMAKE_CXX_STANDARD                                    20 )

set( CMAKE_ASM_NASM_OBJECT_FORMAT win64 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )

project( anti-debugging )

## Main targets
add_subdirectory( anti-debugging )

## Test targets
#add_subdirectory( test )
