cmake_minimum_required(VERSION 3.30)

set(PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}/toolchain")

set(PROJECT_NAME linux-ra02)
set(CMAKE_C_STANDARD 17)

include(${TOOLCHAIN_DIR}/project.cmake)
include(${TOOLCHAIN_DIR}/compiler.cmake)
include(${TOOLCHAIN_DIR}/util.cmake)

compiler_setup(GCC aarch64 linux-gnu)

project(${PROJECT_NAME} C)
project_init()

project_add_inc_dirs(${PROJECT_DIR}/include)
project_add_inc_recursive(${PROJECT_DIR}/include)
project_add_src_recursive(${PROJECT_DIR}/src)

project_add_define(
	"LOG_ENABLE_RA02=1"
	"LOG_ENABLE_MAIN=1"
)

project_add_link_options(ALL
	-Wl,--cref,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
	-Wl,--print-memory-usage

	-lm
)

function(__lib_target_setup)
	project_setup_shared_library(${PROJECT_NAME}-lib)
	target_link_options(${PROJECT_NAME}-lib PRIVATE -Wl,--dynamic-linker=/lib/ld-linux-aarch64.so.1)
endfunction()

project_add_finish_callback(__lib_target_setup)

project_finish()