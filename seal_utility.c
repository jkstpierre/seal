#include "seal_utility.h"
#include "seal.h"

#include <sodium.h>
#include <time.h>
#include <stdlib.h>

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
			printf("%08x", block);
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

/*
	Test bit distribution for a particular key
*/
void test_distribution(size_t N, const uint32_t *key){
	double bits[128] = {0.0};	//Initialize bits to 0

	for(size_t i = 0; i < N; i++){
		uint32_t block[4];
		generateRandomBits128(block);	//Fill block with random bits

		seal_encrypt(block, key);	//Encrypt the block

		for(int j = 0; j < 128; j++){
			bits[j] += (double)((block[j/32] >> (j%32)) & 1);
		}
	}

	for(int i = 0; i < 128; i++){
		bits[i] /= (double)N;
		printf("Bit %d: %lf\n", i, bits[i]);
	}
}

/*
	Test bit divergence for a particular key
*/
void test_block_divergence(size_t N, const uint32_t *key){
	double average_divergence = 0.0;

	for(size_t i = 0; i < N; i++){
		uint32_t block[4];
		generateRandomBits128(block);	//Generate random block

		uint32_t test_block[4] = {block[0], block[1], block[2], block[3]};	//Copy the block to a test_block
		uint32_t comp_block[4] = {block[0], block[1], block[2], block[3]};	//Comparator block
		seal_encrypt(block, key);	//Encrypt the original block

		double count = 0.0;
		for(int j = 0; j < 128; j++){
			test_block[j/32] ^= (1 << (j%32));	//Toggle the bit

			seal_encrypt(test_block, key);	//Encrypt the test block

			//Compute the divergence
			for(int k = 0; k < 128; k++){
				count += (double)(((test_block[j/32] >> (j%32))&1) != ((block[j/32] >> (j%32))&1));
			}

			//Reset the test block
			test_block[0] = comp_block[0];
			test_block[1] = comp_block[1];
			test_block[2] = comp_block[2];
			test_block[3] = comp_block[3];
		}

		count /= 16384.0;	//Compute average divergence for single block

		average_divergence += count;
	}

	average_divergence /= (double)N;	//Find total average divergence
	printf("Average Divergence across %lu samples: %lf%%\n", N, average_divergence*100.0);
}

/*
	Test S-box differential characteristic.

	NOTE:
		Assumes box has 256 elements. If this is not the case, undefined behavior will ensue.
*/
void find_sbox_differential_characteristic(const uint8_t *box){
	uint8_t table[256][256] = {{0}};	//The differential table

	//Produce table of differential values
	for(int i = 0; i < 256; i++){
		for(int j = i+1; j < 256; j++){
			int row = i ^ j;	//Compute the row
			int col = box[i] ^ box[j];	//Compute the column

			table[row][col]++;	//Increment cell
		}
	}

	uint8_t input_differential;
	uint8_t output_differential;
	uint8_t count = 0;

	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 256; j++){
			if(table[i][j] > count){
				count = table[i][j];
				input_differential = (uint8_t)i;
				output_differential = (uint8_t)j;
			}
		}
	}

	float probability = (float)count / 256.0;

	printf("Across given S-box, the best differential characteristic %u-->%u holds true with a probability of %u/256 = %f.\n",
			input_differential, output_differential, count, probability);
}
