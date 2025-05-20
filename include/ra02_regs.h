
/** ========================================================================= *
 *
 * @file ra02_regs.h
 * @date 01-08-2024
 * @author Maksym Tkachuk <max.r.tkachuk@gmail.com>
 *
 * @brief LoRa RA-02 module registers
 *
 *  ========================================================================= */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================= */
/* Defines ================================================================== */

/* SX 1278 Registers */
#define RA02_REG_FIFO             0x00 // FIFO read/write access
#define RA02_REG_OP_MODE          0x01 // Operating mode & LoRaTM / FSK selection
#define RA02_REG_BITRATE_MSB      0x02 // Bit Rate setting, Most Significant Bits
#define RA02_REG_BITRATE_LSB      0x03 // Bit Rate setting, Least Significant Bits
#define RA02_REG_FDEV_MSB         0x04 // Frequency Deviation setting, Most Significant Bits
#define RA02_REG_FDEV_LSB         0x05 // Frequency Deviation setting, Least Significant Bits
#define RA02_REG_FRF_MSB          0x06 // RF Carrier Frequency, Most Significant Bits
#define RA02_REG_FRF_MID          0x07 // RF Carrier Frequency, Intermediate Bits
#define RA02_REG_FRF_LSB          0x08 // RF Carrier Frequency, Least Significant Bits
#define RA02_REG_PA_CFG           0x09 // PA selection and Output Power control
#define RA02_REG_PA_RAMP          0x0A // Control of PA ramp time, low phase noise PLL
#define RA02_REG_OCP              0x0B // OverCurrent Protection control
#define RA02_REG_LNA              0x0C // LNA settings
#define RA02_REG_RX_CFG           0x0D // FSK: AFC, AGC, ctrl; LORA: FIFO SPI pointer
#define RA02_REG_RSSI_CFG         0x0E // FSK: RSSI; LORA: Start Tx data
#define RA02_REG_RSSI_COL         0x0F // FSK: RSSI Collision detector; LORA: Start Rx data
#define RA02_REG_RSSI_THRESH      0x10 // FSK: RSSI Threshold control; LORA: Start address of last packet received
#define RA02_REG_RSSI_VALUE       0x11 // FSK: RSSI value in dBm; LORA: Optional IRQ flag mask
#define RA02_REG_RX_BW            0x12 // FSK: Channel Filter BW Control; LORA: IRQ flags
#define RA02_REG_AFC_BW           0x13 // FSK: AFC Channel Filter BW; LORA: Number of received bytes
#define RA02_REG_OOK_PEEK         0x14 // FSK: OOK demodulator; LORA: Number of valid headers received
#define RA02_REG_OOK_FIX          0x15 // FSK: Threshold of the OOK demod; LORA: LORA: Number of valid headers received
#define RA02_REG_OOK_AVG          0x16 // FSK: Average of the OOK demod; LORA: Number of valid packets received
#define RA02_REG_RES_17           0x17 // LORA: Number of valid packets received
#define RA02_REG_RES_18           0x18 // LORA: Live LoRa modem status
#define RA02_REG_RES_19           0x19 // LORA: Estimation of last packet SNR
#define RA02_REG_AFC_FEI          0x1A // FSK: AFC and FEI control; LORA: RSSI of last packet
#define RA02_REG_AFC_MSB          0x1B // FSK: Frequency correction value of the AFC; LORA: Current RSSI
#define RA02_REG_AFC_LSB          0x1C // FSK: Frequency correction value of the AFC; LORA: HSS start channel
#define RA02_REG_FEI_MSB          0x1E // FSK: Value of the calculated frequency error; LORA: Modem PHY config 1
#define RA02_REG_FEI_LSB          0x1D // FSK: Value of the calculated frequency error; LORA: Modem PHY config 2
#define RA02_REG_PREAMBLE_DETECT  0x1F // FSK: Settings of the Preamble Detector; LORA: Receiver timeout value
#define RA02_REG_RX_TIMEOUT_1     0x20 // FSK: Timeout Rx request and RSSI; LORA: Size of preamble
#define RA02_REG_RX_TIMEOUT_2     0x21 // FSK: Timeout RSSI and PayloadReady; LORA: Size of preamble
#define RA02_REG_RX_TIMEOUT_3     0x22 // FSK: Timeout RSSI and SyncAddress; LORA: LoRa payload length
#define RA02_REG_RX_DELAY         0x23 // FSK: Delay between Rx cycles; LORA: LoRa maximum payload length
#define RA02_REG_OSC              0x24 // FSK: RC Oscillators Settings, CLKOUT frequency; LORA: FHSS Hop period
#define RA02_REG_PREAMBLE_MSB     0x25 // FSK: Preamble length, MSB; LORA: Address of last byte written in FIFO
#define RA02_REG_PREAMBLE_LSB     0x26 // FSK: Preamble length, LSB; Modem PHY config 3
#define RA02_REG_SYNC_CFG         0x27 // FSK: Sync Word Recognition control
#define RA02_REG_SYNC_VALUE_1     0x28 // FSK: Sync Word bytes 1; LORA: Estimated frequency error
#define RA02_REG_SYNC_VALUE_2     0x29 // FSK: Sync Word bytes 2; LORA: Estimated frequency error
#define RA02_REG_SYNC_VALUE_3     0x2A // FSK: Sync Word bytes 3; LORA: Estimated frequency error
#define RA02_REG_SYNC_VALUE_4     0x2B // FSK: Sync Word bytes 4
#define RA02_REG_SYNC_VALUE_5     0x2C // FSK: Sync Word bytes 5; LORA: Wideband RSSI measurement
#define RA02_REG_SYNC_VALUE_6     0x2D // FSK: Sync Word bytes 6
#define RA02_REG_SYNC_VALUE_7     0x2E // FSK: Sync Word bytes 7
#define RA02_REG_SYNC_VALUE_8     0x2F // FSK: Sync Word bytes 8
#define RA02_REG_PACKET_CFG_1     0x30 // FSK: Packet mode settings
#define RA02_REG_PACKET_CFG_2     0x31 // FSK: Packet mode settings; LORA: LoRa detection Optimize for SF6
#define RA02_REG_PAYLOAD_LEN      0x32 // FSK: Payload length setting
#define RA02_REG_NODE_ADDR        0x33 // FSK: Node address; LORA: Invert LoRa I and Q signals
#define RA02_REG_BROADCAST_ADDR   0x34 // FSK: Broadcast address
#define RA02_REG_FIFO_THRESH      0x35 // FSK: Fifo threshold, Tx start condition
#define RA02_REG_SEQ_CFG_1        0x36 // FSK: Top level Sequencer settings
#define RA02_REG_SEQ_CFG_2        0x37 // FSK: Top level Sequencer settings; LORA: LoRa detection threshold for SF6
#define RA02_REG_TIMER_RES        0x38 // FSK: Timer 1 and 2 resolution control
#define RA02_REG_TIMER1_COEF      0x39 // FSK: Timer 1 setting; LORA: LoRa Sync Word
#define RA02_REG_TIMER2_COEF      0x3A // FSK: Timer 2 setting
#define RA02_REG_IMAGE_CAL        0x3B // FSK: Image calibration engine control
#define RA02_REG_TEMP             0x3C // FSK: Temperature Sensor value
#define RA02_REG_LOW_BAT          0x3D // FSK: Low Battery Indicator Settings
#define RA02_REG_IRQ_FLAGS_1      0x3E // FSK: Status register: PLL Lock state, Timeout, RSSI
#define RA02_REG_IRQ_FLAGS_2      0x3F // FSK: Status register: FIFO handling flags, Low Battery
#define RA02_REG_DIO_MAP_1        0x40 // Mapping of pins DIO0 to DIO3
#define RA02_REG_DIO_MAP_2        0x41 // Mapping of pins DIO4 and DIO5, ClkOut frequency
#define RA02_REG_VERSION          0x42 // Semtech ID relating the silicon revision
#define RA02_REG_PLL_HOP          0x43 // FSK: Control the fast frequency hopping mode
#define RA02_REG_TXCO             0x44 // TCXO or XTAL input setting
#define RA02_REG_PA_DAC           0x4B // Higher power settings of the PA
#define RA02_REG_FORMER_TEMP      0x5B // Stored temperature during the former IQ Calibration
#define RA02_REG_BIT_RATE_FRAC    0x5D // FSK: Fractional part in the Bit Rate division ratio
#define RA02_REG_AGC_REF          0x61 // Adjustment of the AGC thresholds
#define RA02_REG_THRESH_1         0x62 // Adjustment of the AGC thresholds
#define RA02_REG_THRESH_2         0x63 // Adjustment of the AGC thresholds
#define RA02_REG_THRESH_3         0x64 // Adjustment of the AGC thresholds
#define RA02_REG_PLL              0x70 // Control of the PLL bandwidth

/* SX 1278 LoRa Registers */
#define RA02_LORA_REG_FIFO_ADDR_PTR         RA02_REG_RX_CFG
#define RA02_LORA_REG_FIFO_TX_BASE_ADDR     RA02_REG_RSSI_CFG
#define RA02_LORA_REG_FIFO_RX_BASE_ADDR     RA02_REG_RSSI_COL
#define RA02_LORA_REG_FIFO_RX_CURRENT_ADDR  RA02_REG_RSSI_THRESH
#define RA02_LORA_REG_IRQ_FLAGS_MASK        RA02_REG_RSSI_VALUE
#define RA02_LORA_REG_IRQ_FLAGS             RA02_REG_RX_BW
#define RA02_LORA_REG_RX_NB_BYTES           RA02_REG_AFC_BW
#define RA02_LORA_REG_RX_HDR_CNT_VAL_MSB    RA02_REG_OOK_PEEK
#define RA02_LORA_REG_RX_HDR_CNT_VAL_LSB    RA02_REG_OOK_FIX
#define RA02_LORA_REG_RX_PKT_CNT_VAL_MSB    RA02_REG_OOK_AVG
#define RA02_LORA_REG_RX_PKT_CNT_VAL_LSB    RA02_REG_RES_17
#define RA02_LORA_REG_MODEM_STAT            RA02_REG_RES_18
#define RA02_LORA_REG_LAST_PKT_SNR          RA02_REG_RES_19
#define RA02_LORA_REG_LAST_PKT_RSSI_VAL     RA02_REG_AFC_FEI
#define RA02_LORA_REG_RSSI_VAL              RA02_REG_AFC_MSB
#define RA02_LORA_REG_HOP_CHANNEL           RA02_REG_AFC_LSB
#define RA02_LORA_REG_MODEM_CFG_1           RA02_REG_FEI_LSB
#define RA02_LORA_REG_MODEM_CFG_2           RA02_REG_FEI_MSB
#define RA02_LORA_REG_MODEL_CFG_3           RA02_REG_PREAMBLE_LSB
#define RA02_LORA_REG_SYMB_TIMEOUT_LSB      RA02_REG_PREAMBLE_DETECT
#define RA02_LORA_REG_PREAMBLE_MSB          RA02_REG_RX_TIMEOUT_1
#define RA02_LORA_REG_PREAMBLE_LSB          RA02_REG_RX_TIMEOUT_2
#define RA02_LORA_REG_PAYLOAD_LEN           RA02_REG_RX_TIMEOUT_3
#define RA02_LORA_REG_MAX_PAYLOAD_LEN       RA02_REG_RX_DELAY
#define RA02_LORA_REG_HOP_PERIOD            RA02_REG_OSC
#define RA02_LORA_REG_FIFO_RX_BYTE_ADDR     RA02_REG_PREAMBLE_MSB
#define RA02_LORA_REG_FEI_MSB               RA02_REG_SYNC_VALUE_1
#define RA02_LORA_REG_FEI_MID               RA02_REG_SYNC_VALUE_2
#define RA02_LORA_REG_FEI_LSB               RA02_REG_SYNC_VALUE_3
#define RA02_LORA_REG_RSSI_WIDEBAND         RA02_REG_SYNC_VALUE_5
#define RA02_LORA_REG_DETECT_OPTIMIZE       RA02_REG_PACKET_CFG_2
#define RA02_LORA_REG_INVERT_IQ             RA02_REG_NODE_ADDR
#define RA02_LORA_REG_DETECTION_THRESH      RA02_REG_SEQ_CFG_2
#define RA02_LORA_REG_SYNC_WORD             RA02_REG_TIMER1_COEF

/* SX 1278 Flags */
#define RA02_IRQ_FLAGS_1_MODE_READY         (1 << 7)
#define RA02_IRQ_FLAGS_1_RX_READY           (1 << 6)
#define RA02_IRQ_FLAGS_1_TX_READY           (1 << 5)
#define RA02_IRQ_FLAGS_1_PLL_LOCK           (1 << 4)
#define RA02_IRQ_FLAGS_1_RSSI               (1 << 3)
#define RA02_IRQ_FLAGS_1_TIMEOUT            (1 << 2)
#define RA02_IRQ_FLAGS_1_PREAMBLE_DETECT    (1 << 1)
#define RA02_IRQ_FLAGS_1_SYNC_ADDR_MATCH    (1 << 0)
#define RA02_IRQ_FLAGS_2_FIFO_FULL          (1 << 7)
#define RA02_IRQ_FLAGS_2_FIFO_EMPTY         (1 << 6)
#define RA02_IRQ_FLAGS_2_LEVEL              (1 << 5)
#define RA02_IRQ_FLAGS_2_OVERRUN            (1 << 4)
#define RA02_IRQ_FLAGS_2_PACKET_SENT        (1 << 3)
#define RA02_IRQ_FLAGS_2_PAYLOAD_READY      (1 << 2)
#define RA02_IRQ_FLAGS_2_CRC_OK             (1 << 1)
#define RA02_IRQ_FLAGS_2_LOW_BAT            (1 << 0)

/* SX 1278 LoRa Flags */
#define RA02_LORA_IRQ_FLAGS_RX_TIMEOUT      (1 << 7)
#define RA02_LORA_IRQ_FLAGS_RX_DONE         (1 << 6)
#define RA02_LORA_IRQ_FLAGS_PAYLOAD_CRC_ERR (1 << 5)
#define RA02_LORA_IRQ_FLAGS_VALID_HDR       (1 << 4)
#define RA02_LORA_IRQ_FLAGS_TX_DONE         (1 << 3)
#define RA02_LORA_IRQ_FLAGS_CAD_DONE        (1 << 2)
#define RA02_LORA_IRQ_FLAGS_FHSS_CHANGE_CH  (1 << 1)
#define RA02_LORA_IRQ_FLAGS_CAD_DETECTED    (1 << 0)

/* SX 1278 LoRa DIO Position */
#define RA02_LORA_MAP_DIO_0(mapping)        ((mapping) << 6)
#define RA02_LORA_MAP_DIO_1(mapping)        ((mapping) << 4)
#define RA02_LORA_MAP_DIO_2(mapping)        ((mapping) << 2)
#define RA02_LORA_MAP_DIO_3(mapping)        (mapping)
#define RA02_LORA_MAP_DIO_4(mapping)        ((mapping) << 6)
#define RA02_LORA_MAP_DIO_5(mapping)        ((mapping) << 4)

/* SX 1278 LoRa DIO Mapping */
#define RA02_LORA_DIO_0_RX_DONE             0b00
#define RA02_LORA_DIO_0_TX_DONE             0b01
#define RA02_LORA_DIO_0_CAD_DONE            0b10
#define RA02_LORA_DIO_1_RX_TIMEOUT          0b00
#define RA02_LORA_DIO_1_FHSS_CHANGE_CH      0b01
#define RA02_LORA_DIO_1_CAD_DETECTED        0b10
#define RA02_LORA_DIO_2_FHSS_CHANGE_CH_1    0b00
#define RA02_LORA_DIO_2_FHSS_CHANGE_CH_2    0b01
#define RA02_LORA_DIO_2_FHSS_CHANGE_CH_3    0b10
#define RA02_LORA_DIO_3_CAD_DONE            0b00
#define RA02_LORA_DIO_3_VALID_HDR           0b01
#define RA02_LORA_DIO_3_PAYLOAD_CRC_ERR     0b10
#define RA02_LORA_DIO_4_CAD_DETECTED        0b00
#define RA02_LORA_DIO_4_PLL_LOCK_1          0b01
#define RA02_LORA_DIO_4_PLL_LOCK_2          0b10
#define RA02_LORA_DIO_5_MODE_READY          0b00
#define RA02_LORA_DIO_5_CLK_OUT_1           0b01
#define RA02_LORA_DIO_5_CLK_OUT_2           0b10

/* SX 1278 Other values */
#define RA02_HW_VERSION           0x12
#define RA02_OP_MODE_LORA_PREFIX  0x80


/* Macros =================================================================== */
/* Enums ==================================================================== */
/* Types ==================================================================== */
/* Variables ================================================================ */
/* Shared functions ========================================================= */

#ifdef __cplusplus
}
#endif
