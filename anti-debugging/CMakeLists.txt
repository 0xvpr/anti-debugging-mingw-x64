project( anti-debugging
         VERSION        1.0.0
         LANGUAGES      CXX ASM_NASM
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}         )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/Methods )
include_directories( ${CMAKE_SOURCE_DIR}/${PROJECT_NAME} )

add_executable(
    ${PROJECT_NAME}
         anti-debugging.cpp
         AntiDebugMethod.cpp
         heavens_gate.asm
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
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-static>
        psapi
)
