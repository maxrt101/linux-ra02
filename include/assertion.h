#pragma once

#include <error.h>

/**
 * Calls error_handler with source file and line, where the error occurred
 */
#define ERROR_HANDLER_CALL(err) error_handler(err, __LINE__, __FILE__)

/**
 * Asserts expression, if failed calls error_handler
 */
#define ASSERT(expr)                                                            \
    do {                                                                        \
      if (!(expr)) {                                                            \
        ERROR_HANDLER_CALL(E_ASSERT);                                           \
      }                                                                         \
    } while (0)

/**
 * Asserts expression, if failed executes user code
 */
#define ASSERT_OR_ELSE(expr, ...)                                               \
    do {                                                                        \
      if (!(expr)) {                                                            \
        __VA_ARGS__;                                                            \
      }                                                                         \
    } while (0)

/**
 * Asserts expression, if failed returns
 */
#define ASSERT_RETURN(expr, ...)                                                \
    do {                                                                        \
      if (!(expr)) {                                                            \
        return __VA_ARGS__;                                                     \
      }                                                                         \
    } while (0)

/**
 * Implementation of ERROR_CHECK/ERROR_CHECK_RETURN
 */
#define __ERROR_CHECK_IMPL_CHECK(error_var, ...)                                \
    do {                                                                        \
      if (error_var != E_OK) {                                                  \
        __VA_ARGS__;                                                            \
      }                                                                         \
    } while (0)


/**
 * Default behaviour if ERROR_CHECK expr fails
 */
#define __ERROR_CHECK_DEFAULT(error_var)                                        \
  ERROR_HANDLER_CALL(error_var)

/**
 * Custom behaviour if ERROR_CHECK_RETURN expr fails
 */
#define __ERROR_CHECK_CUSTOM(error_var, ...)                                    \
  __VA_ARGS__; ERROR_HANDLER_CALL(error_var)


/**
 * Implementation of ERROR_CHECK
 */
#define __ERROR_CHECK_IMPL(error_var, expr, ...)                                \
    do {                                                                        \
       error_t error_var = expr;                                                \
       __ERROR_CHECK_IMPL_CHECK(error_var,                                      \
          UTIL_IF_EMPTY(__VA_ARGS__,                                            \
                        __ERROR_CHECK_DEFAULT(error_var),                       \
                        __ERROR_CHECK_CUSTOM(error_var, __VA_ARGS__)));         \
    } while (0)

/**
 * Checks expression for errors, if not E_OK, calls error_handler
 *
 * @param expr Expression to check
 * @param ... Code to execute if check failed
 */
#define ERROR_CHECK(expr, ...)                                                  \
    __ERROR_CHECK_IMPL(UTIL_CAT(__err, __LINE__), expr, __VA_ARGS__)

/**
 * Default behaviour if ERROR_CHECK_RETURN expr fails
 */
#define __ERROR_CHECK_RETURN_DEFAULT(error_var)                                 \
    return error_var

/**
 * Custom behaviour if ERROR_CHECK_RETURN expr fails
 */
#define __ERROR_CHECK_RETURN_CUSTOM(error_var, ...)                             \
    __VA_ARGS__; return error_var

/**
 * Implementation of ERROR_CHECK_RETURN
 */
#define __ERROR_CHECK_RETURN_IMPL(error_var, expr, ...)                         \
    do {                                                                        \
       error_t error_var = expr;                                                \
       __ERROR_CHECK_IMPL_CHECK(error_var,                                      \
          UTIL_IF_EMPTY(__VA_ARGS__,                                            \
                        __ERROR_CHECK_RETURN_DEFAULT(error_var),                \
                        __ERROR_CHECK_RETURN_CUSTOM(error_var, __VA_ARGS__)));  \
    } while (0)


/**
 * Checks expression for errors, if not E_OK, returns error
 *
 * @param expr Expression to check
 * @param ... Code to execute if check failed
 */
#define ERROR_CHECK_RETURN(expr, ...)                                           \
  __ERROR_CHECK_RETURN_IMPL(UTIL_CAT(__err, __LINE__), expr, __VA_ARGS__)
