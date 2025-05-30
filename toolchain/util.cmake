# =========================================================================
#
# @file utils.cmake
# @date 20-05-2025
# @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
#
# @brief CMake utilities
#
# =========================================================================


include_guard(GLOBAL)

#
# @brief Wrapper for unix `which` command
#
macro(bin_which bin_name out_path)
  execute_process(COMMAND which ${bin_name}
      OUTPUT_VARIABLE ${out_path}
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endmacro()

#
# @brief Wrapper for unix `dirname` command
#
macro(dir_name file_path out_path)
  execute_process(COMMAND dirname ${file_path}
      OUTPUT_VARIABLE ${out_path}
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endmacro()

#
# @brief Checks for command-line dependencies
#
# Checks if command (cmd) return 0 when ran
# If not - can either notify, warn or fail, depending on mode
#
macro(check_cmd_dep cmd mode error_msg)
  execute_process(COMMAND sh -c ${cmd}
      RESULT_VARIABLE ret
      OUTPUT_QUIET
      ERROR_QUIET
  )

  if (NOT ${ret} EQUAL 0)
    string(REPLACE " " ";" cmd_split ${cmd})
    list(GET cmd_split 0 program)

    if (${mode} STREQUAL "FAIL")
      message(FATAL_ERROR "Dependency '${program}' missing: ${error_msg}")
    elseif (${mode} STREQUAL "WARN")
      message(WARNING "Dependency '${program}' missing: ${error_msg}")
    else ()
      message(STATUS "Dependency '${program}' missing: ${error_msg}")
    endif ()
  endif ()
endmacro()
