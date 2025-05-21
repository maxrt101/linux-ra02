/** ========================================================================= *
 *
 * @file error.h
 * @date 20-07-2024
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 *  ========================================================================= */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================= */
/* Defines ================================================================== */
/* Macros =================================================================== */
/* Enums ==================================================================== */

/**
 * Generic errors
 */
typedef enum {
  E_OK          = 0,  /** Successful result */
  E_FAILED      = 1,  /** Operation failed (Generic error) */
  E_ASSERT      = 2,  /** Assertion failed */
  E_NULL        = 3,  /** Null pointer was detected */
  E_INVAL       = 4,  /** Invalid value */
  E_NOTIMPL     = 5,  /** Functionality not implemented */
  E_TIMEOUT     = 6,  /** Operation timed out */
  E_NORESP      = 7,  /** No response */
  E_OVERFLOW    = 8,  /** Overflow occurred */
  E_UNDERFLOW   = 9,  /** Underflow occurred */
  E_AGAIN       = 10, /** Repeat the request */
  E_DONE        = 11, /** Already done */
  E_CORRUPT     = 12, /** Data is corrupt */
  E_BUSY        = 13, /** Resource is busy */
  E_NOTFOUND    = 14, /** Requested resource can't be found */
  E_CANCELLED   = 15, /** Operation was cancelled */
  E_EMPTY       = 16, /** Buffer/Response is empty */
  E_NOMEM       = 17, /** No memory left */
  E_OUTOFBOUNDS = 18, /** Out Of Bounds Access */
} error_t;

/* Types ==================================================================== */
/* Variables ================================================================ */
/* Shared functions ========================================================= */
/**
 * Converts error code to string
 */
const char * error2str(error_t err);

/**
 * Assertion/Error check failure handler
 */
void error_handler(error_t error, int line, const char * file);


#ifdef __cplusplus
}
#endif
