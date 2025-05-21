/** ========================================================================= *
 *
 * @file ra02.h
 * @date 01-08-2024
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 * @brief Driver for LoRa RA-02 module based on sx1278
 *
 *  ========================================================================= */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================= */
#include <stdint.h>
#include <stddef.h>
#include <timeout.h>
#include <spi.h>

/* Defines ================================================================== */
/**
 * Timeout in ms for TX_DONE flag to get up after TX was initiated
 */
#ifndef RA02_SEND_IRQ_TIMEOUT
#define RA02_SEND_IRQ_TIMEOUT 500
#endif

/**
 * Max packet payload in bytes
 */
#define RA02_MAX_PACKET_SIZE 64

/* Macros =================================================================== */
/* Enums ==================================================================== */
/* Types ==================================================================== */
/**
 * RA-02 driver config
 */
typedef struct {
  spi_t * spi;
} ra02_cfg_t;

/**
 * RA-02 driver context
 */
typedef struct {
  spi_t * spi;
  uint8_t irq_flags;
} ra02_t;

/* Variables ================================================================ */
/* Shared functions ========================================================= */
error_t ra02_init(ra02_t * ra02, ra02_cfg_t * cfg);
error_t ra02_deinit(ra02_t * ra02);
error_t ra02_reset(ra02_t * ra02);
error_t ra02_sleep(ra02_t * ra02);
error_t ra02_set_freq(ra02_t * ra02, uint32_t khz);
error_t ra02_get_power(ra02_t * ra02, int8_t * db);
error_t ra02_set_power(ra02_t * ra02, int8_t db);
error_t ra02_set_sync_word(ra02_t * ra02, uint32_t sync_word);
error_t ra02_set_baudrate(ra02_t * ra02, uint32_t baudrate);
error_t ra02_set_bandwidth(ra02_t * ra02, uint32_t bandwidth);
error_t ra02_set_preamble(ra02_t * ra02, uint32_t preamble);
error_t ra02_get_rssi(ra02_t * ra02, int8_t * rssi);
error_t ra02_poll_irq_flags(ra02_t * ra02);
error_t ra02_send(ra02_t * ra02, uint8_t * buf, size_t size);
error_t ra02_recv(ra02_t * ra02, uint8_t * buf, size_t * size, timeout_t * timeout);

#ifdef __cplusplus
}
#endif