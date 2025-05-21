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
/**
 * Initializes RA02
 *
 * @param ra02 RA02 Context
 * @param cfg Valid RA02 Config
 */
error_t ra02_init(ra02_t * ra02, ra02_cfg_t * cfg);

/**
 * Deinitializes RA02
 *
 * @param ra02 RA02 Context
 */
error_t ra02_deinit(ra02_t * ra02);

/**
 * Resets RA02
 *
 * @param ra02 RA02 Context
 */
error_t ra02_reset(ra02_t * ra02);

/**
 * Transitions RA02 to sleep mode
 *
 * @param ra02 RA02 Context
 */
error_t ra02_sleep(ra02_t * ra02);

/**
 * Sets frequency
 *
 * @param ra02 RA02 Context
 * @param khz Operating frequency in kHz
 */
error_t ra02_set_freq(ra02_t * ra02, uint32_t khz);

/**
 * Gets output power
 *
 * @param ra02 RA02 Context
 * @param db Output
 */
error_t ra02_get_power(ra02_t * ra02, uint8_t * db);

/**
 * Sets output power
 *
 * @param ra02 RA02 Context
 * @param db Power
 */
error_t ra02_set_power(ra02_t * ra02, uint8_t db);

/**
 * Set sync word
 *
 * @param ra02 RA02 Context
 * @param sync_word Sync word
 */
error_t ra02_set_sync_word(ra02_t * ra02, uint32_t sync_word);

/**
 * Set baudrate
 *
 * @param ra02 RA02 Context
 * @param baudrate Baudrate
 */
error_t ra02_set_baudrate(ra02_t * ra02, uint32_t baudrate);

/**
 * Set bandwidth
 *
 * @param ra02 RA02 Context
 * @param bandwidth Bandwidth
 */
error_t ra02_set_bandwidth(ra02_t * ra02, uint32_t bandwidth);

/**
 * Set preamble length
 *
 * @param ra02 RA02 Context
 * @param preamble Preamble length in bytes
 */
error_t ra02_set_preamble(ra02_t * ra02, uint32_t preamble);

/**
 * Retrieves current RSSI
 *
 * @param ra02 RA02 Context
 * @param rssi Output
 */
error_t ra02_get_rssi(ra02_t * ra02, int8_t * rssi);

/**
 * Poll IRQ flags
 *
 * @param ra02 RA02 Context
 */
error_t ra02_poll_irq_flags(ra02_t * ra02);

/**
 * Send data over radio
 *
 * @param ra02 RA02 Context
 * @param buf Buffer to send
 * @param size Buffer size
 */
error_t ra02_send(ra02_t * ra02, uint8_t * buf, size_t size);

/**
 * Receive data over radio
 *
 * @param ra02 RA02 Context
 * @param buf Buffer to receive into
 * @param size On input - pointer to variable with buffer size. On output - size of received data
 * @param timeout Timeout to wait for
 */
error_t ra02_recv(ra02_t * ra02, uint8_t * buf, size_t * size, timeout_t * timeout);

#ifdef __cplusplus
}
#endif