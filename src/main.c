/** ========================================================================= *
 *
 * @file spi.c
 * @date 20-05-2025
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 *  ========================================================================= */

/* Includes ================================================================= */
#include <ra02.h>
#include <spi.h>
#include <log.h>
#include <stdlib.h>
#include <string.h>

/* Defines ================================================================== */
#define LOG_TAG MAIN

/* Macros =================================================================== */
#define WITH_RA02(__handle, __spidev) \
    for (ra02_t * __handle = __ra02_init_static(__spidev); __handle; __ra02_deinit_static(&__handle))

/* Exposed macros =========================================================== */
/* Enums ==================================================================== */
enum __ra02_action {
  RA02_INIT,
  RA02_DEINIT,
};

/* Types ==================================================================== */
/* Variables ================================================================ */
const char ld_interp[] __attribute__((section(".interp"))) = LD_LOADER_PATH;

/* Private functions ======================================================== */
static void __ra02_static_action(int action, ...) {
  static ra02_t ra02;
  static spi_t spi;

  va_list args;
  va_start(args, action);

  switch (action) {
    case RA02_INIT: {
      ra02_t ** ra02_out = va_arg(args, ra02_t **);

      spi_cfg_t spi_cfg;

      spi_cfg_default(&spi_cfg);
      spi_init(&spi, &spi_cfg, va_arg(args, const char *));

      ra02_cfg_t ra02_cfg = {.spi = &spi};

      ra02_init(&ra02, &ra02_cfg);

      *ra02_out = &ra02;
      break;
    }

    case RA02_DEINIT: {
      ra02_deinit(&ra02);
      spi_deinit(&spi);
      break;
    }

    default:
      break;
  }

  va_end(args);
}

static ra02_t * __ra02_init_static(const char * spidev) {
  ra02_t * ra02;

  __ra02_static_action(RA02_INIT, &ra02, spidev);

  return ra02;
}

static void __ra02_deinit_static(ra02_t ** ra02) {
  __ra02_static_action(RA02_DEINIT);
  *ra02 = NULL;
}

static void usage(const char * argv0) {
  log_printf(
    "Usage: %s SPIDEV help|spitest|init|send|recv [TIMEOUT|BYTES]\n"
    "  help    - Shows this message\n"
    "  spitest - Tests SPI connection to ra02 module\n"
    "  init    - Initializes ra02 module\n"
    "  send    - Sends bytes via ra02 module\n"
    "  recv    - Received a packet via a ra02 module\n",
    argv0
  );
}

/* Shared functions ========================================================= */
int main(int argc, char ** argv) {
  if (argc < 3) {
    log_error("Insufficient arguments");
    usage(argv[0]);
    return 1;
  }

  const char * spidev = argv[1];

  if (!strcmp(argv[2], "spitest")) {
    spi_t spi;
    spi_cfg_t spi_cfg;

    spi_cfg_default(&spi_cfg);
    spi_init(&spi, &spi_cfg, spidev);

    // Version register
    uint8_t tx[2] = {0x42 & 0x7F, 0};
    uint8_t rx[2] = {0, 0};

    spi_transcieve(&spi, tx, rx, 2);

    log_info("Result: 0x%x 0x%x", rx[0], rx[1]);

    spi_deinit(&spi);
  } else if (!strcmp(argv[2], "init")) {
    WITH_RA02(ra02, spidev) {
      log_info("RA-02 Initialized");
    }
  } else if (!strcmp(argv[2], "send")) {
    uint8_t packet[RA02_MAX_PACKET_SIZE] = {0};
    size_t size = 0;

    for (int i = 3; i < argc; ++i) {
      packet[size++] = atoi(argv[i]);
    }

    error_t err = E_OK;

    WITH_RA02(ra02, spidev) {
      err = ra02_send(ra02, packet, size);
    }

    if (err == E_OK) {
      log_info("Packet sent");
    } else {
      log_error("Failed to send packet: %s", error2str(err));
    }
  } else if (!strcmp(argv[2], "recv")) {
    if (argc != 4) {
      log_error("Expected TIMEOUT", argv[2]);
      usage(argv[0]);
      return 1;
    }

    TIMEOUT_CREATE(t, atoi(argv[3]));

    uint8_t packet[RA02_MAX_PACKET_SIZE] = {0};
    size_t size = sizeof(packet);
    error_t err = E_OK;

    WITH_RA02(ra02, spidev) {
      err = ra02_recv(ra02, packet, &size, &t);
    }

    if (err == E_OK) {
      log_printf("[%d]: ", size);
      for (size_t i = 0; i < size; ++i) {
        log_printf("%02x ", packet[i]);
      }
      log_printf("\n");
    } else {
      log_error("ra02_recv: %s", error2str(err));
      return 1;
    }
  } else {
    log_error("Unknown argument '%s'", argv[2]);
    usage(argv[0]);
    return 1;
  }

  return 0;
}

void __entry() {
#if __aarch64__
  asm volatile (
    "ldr x0, [sp]   \n" // Load argc
    "add x1, sp, #8 \n" // Load argv
    "bl main        \n" // Call main
    "mov x8, #93    \n" // exit() syscall number
    "svc #0         \n" // Execute syscall
  );
#else
  #error "Unsupported architecture"
#endif
}
