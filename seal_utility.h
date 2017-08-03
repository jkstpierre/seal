#ifndef _SEAL_UTILITY_H_
#define _SEAL_UTILITY_H_

/*
	SEAL Utility
	Author: Joseph St. Pierre
	Year: 2017

	This optional file contains helper functions to complement the Simple Encryption ALgorithm's usage
*/

#include <inttypes.h>

/*
	Generate 128 bits of uniformly distributed random data.
	Good for creating cryptographically secure keys!

	NOTE: Assumes array has four elements! If this is not the case, undefined behavior will occur.
*/
void generateRandomWord128(uint32_t blocks[4]);

enum PRINT_MODE{
	BIN = 0,
	DEC = 1,
	HEX = 2
};

/*
	Print the contents of a 128 bit word using a certain mode

	NOTE: Assumes array has four elements! If this is not the case, undefined behavior will occur.
*/
void printBytes(uint32_t blocks[4], int mode);

/*
	Convert a 16 byte string into an array of four 32-bit chunks (i.e. block)

	NOTE: Assumes the provided string is 16 bytes! If this is not the case, undefined behavior will occur.
*/


/*
	Start timer for performance measurement
*/
void startClock();

/*
	Stop timer and get time in milliseconds since last call to startClock
*/
float stopClock();
#endif

