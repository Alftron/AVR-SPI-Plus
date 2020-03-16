/*
A simple SPI library written in C++ for personal use
This was written with ATMega328P in mind but SPI is pretty portable across the range
We're going to assume that the user is handling the chip/slave selects.

Author: Martin Haycock 2020
*/

#ifndef AVRSPI_H
#define AVRSPI_H

#define SPI_SS		PB2
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5

public class AVRSPI {

	enum BitOrder {
		LSBFIRST = 0,
		MSBFIRST;
	}

	enum ClockDivider {
		SPI_CLOCK_DIV2 = 0,
		SPI_CLOCK_DIV4,
		SPI_CLOCK_DIV8,
		SPI_CLOCK_DIV16,
		SPI_CLOCK_DIV32,
		SPI_CLOCK_DIV64,
		SPI_CLOCK_DIV128
	}

	enum DataMode {
		SPI_MODE0 = 0,
		SPI_MODE1,
		SPI_MODE2,
		SPI_MODE3
	}

	public:
		// Variables

	public:
		// Functions
		AVRSPI();
		void masterInit();
		void slaveInit();
		void transmit(char data);
		char receive();
		void setBitOrder(BitOrder order);
		void setClockDivider(ClockDivider divider);
		void setDataMode(DataMode mode);

	private:
		// Variables
		BitOrder _bitorder;
		ClockDivider _clockdivider;
		DataMode _datamode;

	private:
		// Functions
		BitOrder getBitOrder();
		ClockDivider getClockDivider();
		DataMode getDataMode();
}

#endif
