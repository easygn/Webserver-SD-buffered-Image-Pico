#pragma once

// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf


// LEDs
#define PIN_LED        (25u)

// Serial
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)
								// Default variant
#define PIN_SERIAL2_TX (4u)		// (8u)	
#define PIN_SERIAL2_RX (5u)		// (9u)

// SPI
#define PIN_SPI0_MISO  (16u)
#define PIN_SPI0_MOSI  (19u)
#define PIN_SPI0_SCK   (18u)
#define PIN_SPI0_SS    (17u)

#define PIN_SPI1_MISO  (12u)
#define PIN_SPI1_MOSI  (11u)		// (15u)
#define PIN_SPI1_SCK   (10u)		// (14u)
#define PIN_SPI1_SS    (9u)		// (13u)

// Wire
#define PIN_WIRE0_SDA  (20u) 		// (4u)
#define PIN_WIRE0_SCL   (21u)		// (5u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define SERIAL_HOWMANY (3u)
#define SPI_HOWMANY    (2u)
#define WIRE_HOWMANY   (2u)

#include "../generic/common.h"
