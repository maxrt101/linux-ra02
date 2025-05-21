# =========================================================================
#
# @file CMakeLists.txt
# @date 20-05-2025
# @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
#
# @brief LinuxRA02 Project
#
# =========================================================================

cmake_minimum_required(VERSION 3.30)

set(PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}/toolchain")

set(PROJECT_NAME     linux-ra02)
set(CMAKE_C_STANDARD 17)
set(PROJECT_VERBOSE  0)

include(${TOOLCHAIN_DIR}/project.cmake)
include(${TOOLCHAIN_DIR}/compiler.cmake)
include(${TOOLCHAIN_DIR}/util.cmake)

compiler_setup(GCC aarch64 linux-gnu)

project(${PROJECT_NAME} C)
project_init(SHARED)

project_add_inc_dirs(${PROJECT_DIR}/include)
project_add_inc_recursive(${PROJECT_DIR}/include)
project_add_src_recursive(${PROJECT_DIR}/src)

if (NOT "$ENV{LINUX_RA02_LD_LOADER_PATH}" STREQUAL "")
  set(LD_LOADER_PATH "$ENV{LINUX_RA02_LD_LOADER_PATH}")
else ()
  set(LD_LOADER_PATH "/lib/ld-linux-aarch64.so.1")
endif ()

message(STATUS "LD_LOADER_PATH=${LD_LOADER_PATH}")

project_add_define(
    # Logs
    "LOG_ENABLE_RA02=1"
    "LOG_ENABLE_MAIN=1"

    # Path to program loader. Platform specific
    "LD_LOADER_PATH=\"${LD_LOADER_PATH}\""
)

project_add_compile_options(ALL
    -fpic	# Enable position independent code
    -pie	# Make elf a position independent executable
)

project_add_link_options(ALL
    -fpic			      # Enable position independent code
    -pie			      # Make elf a position independent executable
    -Wl,--cref,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,-e,__entry	# Set entry to custom __entry function (micro version on libc _start for executable ELFs)
    -Wl,-E			    # Export symbols
    -lc				      # Link libc
    -lm				      # Link libm
)

# Setup size reports
function(__size_report_setup)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>)
endfunction()

project_add_finish_callback(__size_report_setup)

project_finish()
