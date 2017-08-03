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
	if(sodium_init() < 0)
		return -1;

	uint32_t key[4] = {0x00, 0x00, 0x00, 0x00};
	uint32_t block[4] = {0x00, 0x00, 0x10, 0x00};



	return 0;
}

