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
	test_distribution(100000, key);
	test_divergence(10000, key);

	return 0;
}
