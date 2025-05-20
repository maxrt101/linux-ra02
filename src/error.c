/** ========================================================================= *
 *
 * @file error.c
 * @date 23-07-2024
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 *  ========================================================================= */

/* Includes ================================================================= */
#include <error.h>
#include <log.h>
#include <stdlib.h>

/* Defines ================================================================== */
/* Macros =================================================================== */
/* Exposed macros =========================================================== */
/* Enums ==================================================================== */
/* Types ==================================================================== */
/* Variables ================================================================ */
/* Private functions ======================================================== */
/* Shared functions ========================================================= */
const char * error2str(error_t err) {
  switch (err) {
    case E_OK:          return "E_OK";
    case E_FAILED:      return "E_FAILED";
    case E_ASSERT:      return "E_ASSERT";
    case E_NULL:        return "E_NULL";
    case E_INVAL:       return "E_INVAL";
    case E_NOTIMPL:     return "E_NOTIMPL";
    case E_TIMEOUT:     return "E_TIMEOUT";
    case E_NORESP:      return "E_NORESP";
    case E_OVERFLOW:    return "E_OVERFLOW";
    case E_UNDERFLOW:   return "E_UNDERFLOW";
    case E_AGAIN:       return "E_AGAIN";
    case E_DONE:        return "E_DONE";
    case E_CORRUPT:     return "E_CORRUPT";
    case E_BUSY:        return "E_BUSY";
    case E_NOTFOUND:    return "E_NOTFOUND";
    case E_CANCELLED:   return "E_CANCELLED";
    case E_EMPTY:       return "E_EMPTY";
    case E_NOMEM:       return "E_NOMEM";
    case E_OUTOFBOUNDS: return "E_OUTOFBOUNDS";
    default:
      return "E_?";
  }
}

void error_handler(error_t error, int line, const char * file) {
  log_fatal("%s at %s:%d", error2str(error), file, line);
  exit(1);
}