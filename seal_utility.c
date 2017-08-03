#include "seal_utility.h"

#include <sodium.h>
#include <time.h>

/*
	Generate 128 bits of uniformly distributed random data
*/
void generateRandomWord128(uint32_t blocks[4]){
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

clock_t start_time;

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

