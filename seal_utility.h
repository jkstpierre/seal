#ifndef _SEAL_UTILITY_H_
#define _SEAL_UTILITY_H_

/*
	SEAL Utility
	Author: Joseph St. Pierre
	Year: 2017

	This optional file contains helper functions to complement the Simple Encryption ALgorithm's usage
*/

#include <inttypes.h>
#include <stddef.h>

/*
	Generate 128 bits of uniformly distributed random data.
	Good for creating cryptographically secure keys!

	NOTE: Assumes array has four elements! If this is not the case, undefined behavior will occur.
*/
void generateRandomBits128(uint32_t blocks[4]);

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

	No resource allocation is done inside this method.

	NOTE:
		Assumes the provided string is 16 bytes! If this is not the case, undefined behavior will occur.
		Assumes the provided block has 4 32-bit chunks and that each chunk is initialized to zero! If this is not the case,
		undefined behavior will occur.
*/
void stringToBlock(uint32_t *block, const char *str);

/*
	Convert a 128 bit block into a 16 byte string

	No resource allocation is done inside this method.

	NOTE:
		Assumes the provided string is 16 bytes! If this is not the case, undefined behavior will occur.
		Assumes the provided block has 4 32-bit chunks and that each chunk is initialized to zero! If this is not the case,
		undefined behavior will occur.
*/
void blockToString(char *str, const uint32_t *block);

/*
	Start timer for performance measurement
*/
void startClock();

/*
	Stop timer and get time in milliseconds since last call to startClock
*/
float stopClock();

/*
	Test bit distribution for a particular key
*/
void test_distribution(size_t N, const uint32_t *key);

/*
	Test bit divergence for a particular key
*/
void test_block_divergence(size_t N, const uint32_t *key);

/*
	Test bit divergence for a particular block
*/
void test_key_divergence(size_t N, const uint32_t *block);
#endif
