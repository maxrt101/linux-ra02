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
  E_OK = 0,       /** Successful result */
  E_FAILED,       /** Operation failed (Generic error) */
  E_ASSERT,       /** Assertion failed */
  E_NULL,         /** Null pointer was detected */
  E_INVAL,        /** Invalid value */
  E_NOTIMPL,      /** Functionality not implemented */
  E_TIMEOUT,      /** Operation timed out */
  E_NORESP,       /** No response */
  E_OVERFLOW,     /** Overflow occurred */
  E_UNDERFLOW,    /** Underflow occurred */
  E_AGAIN,        /** Repeat the request */
  E_DONE,         /** Already done */
  E_CORRUPT,      /** Data is corrupt */
  E_BUSY,         /** Resource is busy */
  E_NOTFOUND,     /** Requested resource can't be found */
  E_CANCELLED,    /** Operation was cancelled */
  E_EMPTY,        /** Buffer/Response is empty */
  E_NOMEM,        /** No memory left */
  E_OUTOFBOUNDS,  /** Out Of Bounds Access */
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
