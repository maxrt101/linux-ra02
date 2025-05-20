/** ========================================================================= *
 *
 * @file spi.h
 * @date 20-05-2025
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 *  ========================================================================= */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================= */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <error.h>

/* Defines ================================================================== */
/* Macros =================================================================== */
/* Enums ==================================================================== */
/* Types ==================================================================== */
/**
 * SPI Config
 */
typedef struct {
  uint32_t speed;
  uint16_t delay_us;
  uint8_t  bits_per_word;
} spi_cfg_t;

/**
 * SPI Context
 */
typedef struct {
  spi_cfg_t cfg;
  int fd;
} spi_t;

/* Variables ================================================================ */
/* Shared functions ========================================================= */
/**
 * Set default values in SPI config
 *
 * @param cfg SPI Config
 */
error_t spi_cfg_default(spi_cfg_t * cfg);

/**
 * Initialize SPI driver handle
 *
 * @param spi SPI Handle
 * @param cfg SPI Config
 * @param dev Name of SPI device (/dev/spidevX.Y)
 */
error_t spi_init(spi_t * spi, spi_cfg_t * cfg, const char * dev);

/**
 * Deinitialize SPI driver handle
 *
 * @param spi SPI Handle
 */
error_t spi_deinit(spi_t * spi);

/**
 * Send/Receive data over SPI
 *
 * @param spi SPI Handle
 * @param tx_buf Buffer to send
 * @param rx_buf Buffer to receive (can be NULL)
 * @param size Size of tx_buf & rx_buf
 */
error_t spi_transcieve(
  spi_t * spi,
  uint8_t * tx_buf,
  uint8_t * rx_buf,
  size_t size
);

#ifdef __cplusplus
}
#endif
