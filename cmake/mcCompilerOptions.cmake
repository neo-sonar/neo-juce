add_library(compiler_options INTERFACE)
add_library(ModernCircuits::CompilerOptions ALIAS compiler_options)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(compiler_options INTERFACE "/permissive-")
endif()

if(MC_BUILD_ASAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(compiler_options INTERFACE -fsanitize=address -fsanitize-address-use-after-scope -O1 -g -fno-omit-frame-pointer)
    target_link_libraries(compiler_options INTERFACE -fsanitize=address -fsanitize-address-use-after-scope -O1 -g -fno-omit-frame-pointer)
endif()

if(MC_BUILD_UBSAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(compiler_options INTERFACE -fsanitize=undefined -O1 -g -fno-omit-frame-pointer)
    target_link_libraries(compiler_options INTERFACE -fsanitize=undefined -O1 -g -fno-omit-frame-pointer)
endif()

if(MC_BUILD_MSAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(compiler_options INTERFACE -fsanitize=memory -O1 -g -fno-omit-frame-pointer)
    target_link_libraries(compiler_options INTERFACE -fsanitize=memory -O1 -g -fno-omit-frame-pointer)
endif()

if(MC_BUILD_TSAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(compiler_options INTERFACE -fsanitize=thread -O1 -g -fno-omit-frame-pointer)
    target_link_libraries(compiler_options INTERFACE -fsanitize=thread -O1 -g -fno-omit-frame-pointer)
endif()


