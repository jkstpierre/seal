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

	uint32_t key[4];	//The 128 bit key
	generateRandomBits128(key);	//Fill 128 bit key with cryptographically secure random bits

	uint32_t block[4] = {0x11, 0x10, 0x10, 0xA1};	//The block of plaintext

	printf("Before encryption: ");
	printBytes(block, HEX);		//Print the block in hexadecimal
	printf("\n");

	seal_encrypt(block, key);	//Permute the block against the key using SEAL

	printf("After encryption: ");
	printBytes(block, HEX);		//Print the block in hexadecimal
	printf("\n");

	seal_decrypt(block, key);	//Decrypt the block

	printf("After decryption: ");
	printBytes(block, HEX);		//Print the plaintext in hexadecimal
	printf("\n");

	return 0;
}
