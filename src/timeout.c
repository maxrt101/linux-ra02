/** ========================================================================= *
*
 * @file timeout.c
 * @date 20-07-2024
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 *  ========================================================================= */

/* Includes ================================================================= */
#include <timeout.h>
#include <assertion.h>
#include <time.h>

/* Defines ================================================================== */
/* Macros =================================================================== */
/* Enums ==================================================================== */
/* Types ==================================================================== */
/* Variables ================================================================ */
/* Private functions ======================================================== */
static uint64_t get_system_time_ms(void) {
  struct timespec spec;

  clock_gettime(CLOCK_REALTIME, &spec);

  return spec.tv_sec * 1000 + (spec.tv_nsec / 1.0e6);
}

/* Shared functions ========================================================= */
void timeout_start(timeout_t * timeout, uint64_t ms) {
  ASSERT_RETURN(timeout);

  timeout->duration = ms;
  timeout->start = get_system_time_ms();
}

void timeout_restart(timeout_t * timeout) {
  ASSERT_RETURN(timeout);

  timeout->start = get_system_time_ms();
}

bool timeout_is_expired(const timeout_t * timeout) {
  ASSERT_RETURN(timeout, true);

  return get_system_time_ms() >= (timeout->start + timeout->duration);
}

void timeout_expire(timeout_t * timeout) {
  ASSERT_RETURN(timeout);

  timeout->duration = 0;
}