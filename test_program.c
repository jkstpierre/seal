/*
	SEAL Block Cipher Test Program
	Author: Joseph St. Pierre
	Year: 2017
*/

#include <sodium.h>
#include <stdio.h>
#include "seal.h"
#include "seal_utility.h"

int main(int argc, char** args){
	if(sodium_init() < 0)	//Initialize Sodium Library
		return -1;

	uint32_t key[4] = {0x00, 0x00, 0x01, 0x00};
	uint32_t block[4] = {0x00, 0x00, 0x00, 0x00};

	startClock();
	for(int i = 0; i < 1000; i++){
		uint32_t input[4] = {block[0], block[1], block[2], block[3]};
		uint32_t test_key[4] = {key[0], key[1], key[2], key[3]};

		//generateRandomBits128(key);

		seal_encrypt(input, test_key);

		printBytes(input, HEX);
		printf("\n");

		block[0]++;
	}
	printf("Took: %f\n", stopClock());

	return 0;
}
