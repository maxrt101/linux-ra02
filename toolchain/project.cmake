# =========================================================================
#
# @file project.cmake
# @date 20-05-2025
# @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
#
# @brief CMake Project support
#
# =========================================================================

include_guard(GLOBAL)

#
# @brief Internal macro that setups project flags/options for a target
#
macro(__project_setup_target target)
  # Add include directories
  target_include_directories(${target} PRIVATE ${PROJECT_INCLUDE_DIRS})

  # Add defines
  add_compile_definitions(${PROJECT_DEFINES})

  # Add compile options
  target_compile_options(
      ${target} PRIVATE
      ${PROJECT_COMPILE_FLAGS}
  )

  # Add link options
  target_link_options(
      ${target} PRIVATE
      ${ld_script_options}
      ${PROJECT_LINK_FLAGS}
  )
endmacro()

#
# @brief Sets up named executable target
#
macro(project_setup_executable target)
  # Add executable with specified .c and .h files
  add_executable(${target}
      ${PROJECT_INCLUDES}
      ${PROJECT_SOURCES}
  )

  __project_setup_target(${target})
endmacro()

#
# @brief Sets up named static library target
#
macro(project_setup_static_library target)
  # Add static library with specified .c and .h files
  add_library(${target} STATIC
      ${PROJECT_INCLUDES}
      ${PROJECT_SOURCES}
  )

  __project_setup_target(${target})
endmacro()

#
# @brief Sets up named shared library target
#
macro(project_setup_shared_library target)
  # Add shared library with specified .c and .h files
  add_library(${target} SHARED
      ${PROJECT_INCLUDES}
      ${PROJECT_SOURCES}
  )

  __project_setup_target(${target})
endmacro()

#
# @brief Start of project configuration section
#
# You should place all your code between project_init/project_finish
# In-between you can setup build parameters, such as include directories,
# source files, compile options, etc., by calling functions like:
#   project_add_src_recursive
#   project_add_inc_dirs
#   etc.
#
# @param[in] project_type Type of project: EXECUTABLE, STATIC or SHARED
#
macro(project_init project_type)
  if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevent build in source directory")
  endif ()

  if (NOT DEFINED PROJECT_NAME)
    message(FATAL_ERROR "PROJECT_NAME not found, set it before calling project_init")
  endif ()

  if (PROJECT_VERBOSE STREQUAL 1)
    set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose makefile" FORCE)
  endif ()

  set(PROJECT_TYPE "${project_type}")

  set(PROJECT_INCLUDE_DIRS "")
  set(PROJECT_INCLUDES "")
  set(PROJECT_SOURCES "")
  set(PROJECT_LD_PATHS "")
  set(PROJECT_LD "")
  set(PROJECT_DEFINES "")
  set(PROJECT_COMPILE_FLAGS "")
  set(PROJECT_LINK_FLAGS "")
  set(PROJECT_FINISH_CALLBACKS "")

  if ("${CMAKE_BUILD_TYPE}" STREQUAL DEBUG)
    project_add_define("USE_DEBUG=1")
  endif ()
endmacro()

#
# @brief End of project configuration block.
# Setups all required parameters and build targets.
#
# See `project_init()` description for more details
#
macro(project_finish)
  # Set dependency for LD scripts to every file in the project
  if (NOT "${PROJECT_LD}" STREQUAL "")
    foreach (source ${PROJECT_SOURCES})
      set_source_files_properties(${source} PROPERTIES OBJECT_DEPENDS "${PROJECT_LD}")
    endforeach ()
  endif ()

  set(ld_script_options "")

  # Parse linker paths
  foreach (path ${PROJECT_LD_PATHS})
    list(APPEND ld_script_options "-Wl,-L${path}")
  endforeach ()

  # Parse linker scripts
  foreach (ld ${PROJECT_LD})
    list(APPEND ld_script_options "-T${ld}")
  endforeach ()

  if (${PROJECT_TYPE} STREQUAL EXECUTABLE)
    project_setup_executable(${PROJECT_NAME})
  elseif (${PROJECT_TYPE} STREQUAL STATIC)
    project_setup_static_library(${PROJECT_NAME})
  elseif (${PROJECT_TYPE} STREQUAL SHARED)
    project_setup_shared_library(${PROJECT_NAME})
  else ()
    message(FATAL_ERROR "Unknown PROJECT_TYPE '${PROJECT_TYPE}'")
  endif ()

  foreach (cb ${PROJECT_FINISH_CALLBACKS})
    message(STATUS "Calling finish callback ${cb}")
    cmake_language(CALL ${cb})
  endforeach ()
endmacro()

#
# @brief Register callback that will be called after executable is added
#
# @param[in] ... Callbacks
#
macro(project_add_finish_callback)
  foreach (cb ${ARGV})
    list(APPEND PROJECT_FINISH_CALLBACKS ${cb})
  endforeach ()
endmacro()

#
# @brief Add header files recursively
#
# @param[in] ... List of directories, from which the include will be extracted
#
macro(project_add_inc_recursive)
  foreach (path ${ARGV})
    unset(found_inc)
    file(GLOB_RECURSE found_inc ${path}/*.h)
    list(APPEND PROJECT_INCLUDES ${found_inc})
  endforeach ()
endmacro()

#
# @brief Add source files recursively
#
# @param[in] ... List of directories, from which the sources will be extracted
#
macro(project_add_src_recursive)
  foreach (path ${ARGV})
    unset(found_src)
    file(GLOB_RECURSE found_src ${path}/*.c)
    list(APPEND PROJECT_SOURCES ${found_src})
  endforeach ()
endmacro()

#
# @brief Add source files
#
# @param[in] ... List of source files
#
macro(project_add_src_files)
  list(APPEND PROJECT_SOURCES ${ARGV})
endmacro()

#
# @brief Add include directories
#
# @param[in] ... List of include directories
#
macro(project_add_inc_dirs)
  list(APPEND PROJECT_INCLUDE_DIRS ${ARGV})
endmacro()

#
# @brief Add LD paths
#
# @param[in] ... List of linker paths
#
macro(project_add_ld_paths)
  list(APPEND PROJECT_LD_PATHS ${ARGV})
endmacro()

#
# @brief Add LD script
#
# @param[in] ... List of linker scripts
#
macro(project_add_ld_scripts)
  list(APPEND PROJECT_LD ${ARGV})
endmacro()

#
# @brief Add command line defines
#
# @param[in] ... List of defines (e.g. "DEBUG" of "DEBUG=1")
#
macro(project_add_define)
  list(APPEND PROJECT_DEFINES ${ARGV})
endmacro()

#
# Sets ${result} to TRUE if exact define ${define} was added to PROJECT_DEFINES
#
# @param[in]  define Exact define passed to project_add_define (e.g. "USE_LED=1")
# @param[out] result Variable to put result in. TRUE if found, FALSE otherwise
#
macro(project_has_define define result)
  set(${result} FALSE)
  foreach (def ${PROJECT_DEFINES})
    if(${def} STREQUAL ${define})
      set(${result} TRUE)
    endif()
  endforeach ()
endmacro()

#
# @brief Adds compile options
#
# @param[in] target ALL, DEBUG or RELEASE
# @param[in] ... List of compile options
#
macro(project_add_compile_options target)
  macro(__add_compile_options)
    foreach (flag ${ARGN})
      list(APPEND PROJECT_COMPILE_FLAGS ${flag})
    endforeach ()
  endmacro()

  if (${target} STREQUAL ALL OR ${target} STREQUAL "${CMAKE_BUILD_TYPE}")
    __add_compile_options(${ARGV})
  endif ()
endmacro()

#
# @brief Adds link options
#
# @param[in] target ALL, DEBUG or RELEASE
# @param[in] ... List of link options
#
macro(project_add_link_options target)
  macro(__add_link_options)
    foreach (flag ${ARGN})
      list(APPEND PROJECT_LINK_FLAGS ${flag})
    endforeach ()
  endmacro()

  if (${target} STREQUAL ALL OR ${target} STREQUAL "${CMAKE_BUILD_TYPE}")
    __add_link_options(${ARGV})
  endif ()
endmacro()