add_library(compiler_warnings INTERFACE)
add_library(ModernCircuits::CompilerWarnings ALIAS compiler_warnings)

if (MSVC)
    if (MODERN_CIRCUITS_BUILD_WERROR)
        target_compile_options(compiler_warnings INTERFACE /WX)
    endif (MODERN_CIRCUITS_BUILD_WERROR)
    target_compile_options(compiler_warnings INTERFACE /W3)
else ()
    if (MODERN_CIRCUITS_BUILD_WERROR)
        target_compile_options(compiler_warnings INTERFACE -Werror)
    endif (MODERN_CIRCUITS_BUILD_WERROR)
    target_compile_options(compiler_warnings
            INTERFACE
                    -Wall
                    -Wextra
                    -Wpedantic
                    -Wcast-align
                    -Wshadow
                    -Wunused-parameter
                    -Wnarrowing
                    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
                        #-Weverything
                    >
                    $<$<CXX_COMPILER_ID:AppleClang>:
                        -Wno-poison-system-directories

                    >
                    $<$<CXX_COMPILER_ID:GNU>:
                        #-Wlogical-op
                    >
            )

endif (MSVC)
