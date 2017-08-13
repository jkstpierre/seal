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

	uint32_t key[4];
	generateRandomBits128(key);
	test_distribution(10000, key);
	test_block_divergence(1000, key);

	uint32_t block[4];
	generateRandomBits128(block);

	startClock();
	for(int i = 0; i < 10000000; i++){
		seal_encrypt(block, key);
	}
	printf("Took %lf milleseconds to encrypt 160 million bytes...\n",stopClock());

	return 0;
}
