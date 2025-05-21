# =========================================================================
#
# @file compiler.cmake
# @date 20-05-2025
# @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
#
# @brief CMake toolchain compiler support
#
# =========================================================================


include_guard(GLOBAL)

#
# @brief Retrieves compiler folder from executable name
#
macro(compiler_get_folder bin folder)
  bin_which(${bin} bin_path)
  if ("${bin_path}" MATCHES "not found" OR "${bin_path}" STREQUAL "")
    message(FATAL_ERROR "Compiler executable not found (${bin})")
  endif ()

  if (IS_SYMLINK ${bin_path})
    file(REAL_PATH ${bin_path} bin_path)
  endif ()

  dir_name(${bin_path} compiler_path)
  set(${folder} ${compiler_path})
endmacro()

#
# @brief Sets up compiler, based on family, target abd ABI
#
macro(compiler_setup family target abi)
  if (NOT ${family} STREQUAL GCC)
    message(FATAL_ERROR "Unsupported compiler family ${family}")
  endif ()

  set(prefix ${target}-${abi})
  set(bin ${prefix}-gcc)

  compiler_get_folder(${bin} compiler_folder)

  message(STATUS "Setting up compiler (${family} at ${compiler_folder})")

  set(PROJECT_COMPILER_FOLDER "${compiler_folder}/../")

  set(CMAKE_C_COMPILER_ID ${CMAKE_COMPILER_ID} CACHE STRING "" FORCE)
  set(CMAKE_C_COMPILER_VERSION ${version} CACHE STRING "" FORCE)
  set(CMAKE_C_COMPILER "${compiler_folder}/${prefix}-gcc" CACHE STRING "" FORCE)

  set(CMAKE_C_STANDARD 17 CACHE STRING "" FORCE)
  set(CMAKE_C_STANDARD_COMPUTED_DEFAULT 17 CACHE STRING "" FORCE)
  set(CMAKE_C_STANDARD_REQUIRED ON CACHE STRING "" FORCE)
  set(CMAKE_C_EXTENSIONS ON CACHE STRING "" FORCE)
  set(CMAKE_C_FLAGS "" CACHE STRING "" FORCE)

  set(CMAKE_CXX_COMPILER_ID ${CMAKE_COMPILER_ID} CACHE STRING "" FORCE)
  set(CMAKE_CXX_COMPILER_VERSION ${version} CACHE STRING "" FORCE)
  set(CMAKE_CXX_COMPILER "${compiler_folder}/${prefix}-g++" CACHE STRING "" FORCE)

  set(CMAKE_CXX_STANDARD 17 CACHE STRING "" FORCE)
  set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT 17 CACHE STRING "" FORCE)
  set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE STRING "" FORCE)
  set(CMAKE_CXX_EXTENSIONS ON CACHE STRING "" FORCE)
  set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)

  set(CMAKE_ASM_COMPILER_ID ${CMAKE_COMPILER_ID} CACHE STRING "" FORCE)
  set(CMAKE_ASM_COMPILER_VERSION ${version} CACHE STRING "" FORCE)
  set(CMAKE_ASM_COMPILER "${compiler_folder}/${prefix}-gcc" CACHE STRING "" FORCE)

  set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "" FORCE)

  macro(__compiler_setup_executable name variable)
    set(bin "${compiler_folder}/${prefix}-${name}")
    if (NOT (bin MATCHES NOTFOUND) AND NOT (bin STREQUAL ""))
      set(${variable} "${bin}" CACHE STRING "" FORCE)
    else ()
      message(WARNING "${name} binary - not found")
    endif ()
  endmacro()

  __compiler_setup_executable(ld CMAKE_LD)
  __compiler_setup_executable(objcopy CMAKE_OBJCOPY)
  __compiler_setup_executable(size CMAKE_SIZE)
  __compiler_setup_executable(gdb CMAKE_GDB)
  __compiler_setup_executable(gcc-ar CMAKE_AR)
  __compiler_setup_executable(strip CMAKE_STRIP)
  __compiler_setup_executable(readelf CMAKE_READELF)
  __compiler_setup_executable(objdump CMAKE_OBJDUMP)
  __compiler_setup_executable(gcov CMAKE_GCOV)

  set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf CACHE STRING "" FORCE)
  set(CMAKE_EXECUTABLE_SUFFIX_C .elf CACHE STRING "" FORCE)
  set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf CACHE STRING "" FORCE)

  set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE STRING "" FORCE)
  set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" CACHE STRING "" FORCE)

  # TODO: Make generic (maybe receive from user, or infer from compiler)
  set(CMAKE_SYSTEM_NAME Linux CACHE STRING "" FORCE)
  set(CMAKE_SYSTEM_PROCESSOR aarch64 CACHE STRING "" FORCE)

  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endmacro()

#
# @brief Gets full path of file within compiler installation directory
#
macro(compiler_get_filepath path name)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=${name}
      OUTPUT_VARIABLE ${path}
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endmacro()
