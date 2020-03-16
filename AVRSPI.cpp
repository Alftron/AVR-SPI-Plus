/*
A simple SPI library written in C++ for personal use
This was written with ATMega328P in mind but SPI is pretty portable across the range
We're going to assume that the user is handling the chip/slave selects.

Author: Martin Haycock 2020
*/

#include "AVRSPI.h"

#include <avr/io.h>

// Have an instance already setup to use
AVRSPI SPI;

void AVRSPI::masterInit() {
	// Set SCK, MOSI and SS as outputs (DDR_SPI might be faster but not as readable)
	DDRB |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);
	// MISO as input
	DDRB &= ~(1 << SPI_MISO);
	// Set chip as master
	SPCR |= (1 << MSTR);
	// Enable SPI
	SPCR |= (1 << SPE);
	// Set the bit order
	setBitOrder(MSBFIRST);
	// Set the clock divider
	setClockDivider(SPI_CLOCK_DIV4);
	// Set the data mode
	setDataMode(SPI_MODE0);
}

void AVRSPI::slaveInit() {
	// Set SCK, MOSI and SS as inputs (DDR_SPI might be faster but not as readable)
	DDRB &= ~(1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);
	// MISO as output
	DDRB |= (1 << SPI_MISO);
	// Set the bit order
	setBitOrder(MSBFIRST);
	// Set the clock divider
	setClockDivider(SPI_CLOCK_DIV4);
	// Set the data mode
	setDataMode(SPI_MODE0);
}

void AVRSPI::transmit(char data) {
	// Start transmission by loading data into SPI data register
	SPDR = data;
	/* Wait for transmission to complete by reading interrupt flag
		which is set by the hardware when an SPI transfer is complete
	*/
	while (!(SPSR & (1 << SPIF)));
}

char AVRSPI::receive() {
	// Wait for receive to finish
	while (!(SPSR & (1 << SPIF)));
	// Return the data
	return SPDR;
}

void AVRSPI::setBitOrder(BitOrder order) {
	_bitorder = order;
	if (order == LSBFIRST) {
		// DORD bit set to 1 if LSB
		SPCR |= (1 << DORD);
	} else {
		// DORD bit set to 0 if MSB
		SPCR &= ~(1 << DORD);
	}
}

void AVRSPI::setClockDivider(ClockDivider divider) {
	_clockdivider = divider;
}

void AVRSPI::setDataMode(DataMode mode) {
	_datamode = mode;
	SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

extern AVRSPI SPI;
