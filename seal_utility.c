#include "seal_utility.h"

#include <sodium.h>
#include <time.h>

/*
	Generate 128 bits of uniformly distributed random data
*/
void generateRandomBits128(uint32_t blocks[4]){
	//For each block of the word
	int i;
	for(i = 0; i < 4; i++){
		blocks[i] = randombytes_random();	//Generate random bits
	}
}

/*
	Print the contents of a 128 bit word using a certain mode
*/
void printBytes(uint32_t blocks[4], int mode){
	//Check for valid mode
	if(mode != BIN && mode != DEC && mode != HEX)
		return;

	int i;
	for(i = 3; i >= 0; i--){
		uint32_t block = blocks[i];
		if(mode == BIN){
			int j;
			for(j = 31; j >= 0; j--){
				printf("%d", (block >> j)&1);
			}
		}
		else if(mode == DEC){
			printf("%09d", block);
		}
		else{
			printf("%08X", block);
		}
	}
}

/*
	Convert a 16 byte string into an array of four 32-bit chunks (i.e. block)

	No resource allocation is done inside this method.

	NOTE:
		Assumes the provided string is 16 bytes! If this is not the case, undefined behavior will occur.
		Assumes the provided block has 4 32-bit chunks and that each chunk is initialized to zero! If this is not the case,
		undefined behavior will occur.
*/
void stringToBlock(uint32_t *block, const char *str){
	int i;
	for(i = 0; i < 16; i++){
		block[i/4] |= (uint32_t)str[i] << 8*(i%4);
	}
}

/*
	Convert a 128 bit block into a 16 byte string

	No resource allocation is done inside this method.

	NOTE:
		Assumes the provided string is 16 bytes! If this is not the case, undefined behavior will occur.
		Assumes the provided block has 4 32-bit chunks and that each chunk is initialized to zero! If this is not the case,
		undefined behavior will occur.
*/
void blockToString(char *str, const uint32_t *block){
	int i;
	int j;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			str[4*i + j] = (char)(block[i] >> 8*j);
		}
	}
}

clock_t start_time;	//The timer for performance measurement

/*
	Start timer for performance measurement
*/
void startClock(){
	start_time = clock();
}

/*
	Stop timer and get time in milliseconds since last call to startClock
*/
float stopClock(){
	clock_t end_time = clock();

	return (1000.0*(end_time - start_time) )/ CLOCKS_PER_SEC;
}
