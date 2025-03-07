project( anti-debugging
         VERSION        1.0.0
         LANGUAGES      CXX ASM_NASM RC
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}         )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/Methods )
include_directories( ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} )

add_compile_definitions( WIN32_LEAN_AND_MEAN=1 )
add_compile_definitions( VC_EXTRALEAN=1 )

set( RC_SOURCE Resources/anti-debugging.rc )
set( RC_OBJECT "${CMAKE_CURRENT_BINARY_DIR}/anti-debugging.rc.o" )

add_custom_command(
    OUTPUT ${RC_OBJECT}
    COMMAND x86_64-w64-mingw32-windres -O coff
            -i ${CMAKE_CURRENT_SOURCE_DIR}/${RC_SOURCE}
            -o ${RC_OBJECT}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${RC_SOURCE}
    COMMENT "Compiling resource file ${RC_SOURCE} with windres"
    VERBATIM
)

add_library(
    ${PROJECT_NAME}_rc
    OBJECT
        ${RC_OBJECT}
)

add_executable(
    ${PROJECT_NAME}
         anti-debugging.cpp
         AntiDebugMethod.cpp
         heavens_gate.asm
         ${RC_OBJECT}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        PREFIX "vpr-"
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE 
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-masm=intel>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Ofast>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wall>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wextra>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Werror>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wshadow>
#       $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wconversion>
#       $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wno-unused-value>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wno-cast-function-type>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-Wno-missing-field-initializers>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-fPIE>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-fno-ident>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-ffast-math>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-funroll-loops>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>:-fvisibility=hidden>

        $<$<COMPILE_LANGUAGE:RC>:-Ocoff>
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-static>
        psapi
        ${PROJECT_NAME}_rc
)
