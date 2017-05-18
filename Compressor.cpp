/*
 *
 *  COMP 15 Project 2 - ISOMORPH 
 *
 *  Compressor.cpp
 *  Complete Compresseion Scheme Implementation
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This is the implementation of the compression scheme used to 
 *  reduce the file size of the key. It compresses integers to strings 
 *  where the strings represent the original int in a greater base. 
 *  For the sake of Isomorph, it will convert base 2 and 10 to base 128.
 */

#include "Compressor.h"
#include <math.h>
#include <iostream>

using namespace std;

/*Constructor*/
Compressor::Compressor(){
	/*Nothing to do*/
}

/*Destructor*/
Compressor::~Compressor(){
	/*Nothing to do*/
}

/* Purpose: Compress binary number to base 128 string
 * Parameters: int - number to compress
 * Returns: string - compressed integer
 *
 */ 
string Compressor::compressBinary(string binary){

	string to_return = ""; 
	int bit_power = 0;
	char to_append = 0;

	for (int i = (int) binary.size() - 1; i >= 0; i--){
		if (binary.at(i) == ONE){
			to_append += pow(2, bit_power);
		}
		bit_power++;

		if (bit_power == 7){
			to_return = to_append + to_return; /*add to front*/
			bit_power = 0;
			to_append = 0;
		}
	}
	if (to_append != 0){
		to_return = to_append + to_return;
	}

	return to_return;
}

/* Purpose: Compress decimal number to base 128 string
 * Parameters: int - number to compress
 * Returns: string - compressed integer
 *
 */ 
string Compressor::compressDecimal(int decimal){
	(void) decimal;
	return "";
}

/* Purpose: Decmpress base 128 string to binary number
 * Parameters: string - compressed integer
 * Returns: int - decompressed integer
 *
 * ADDITIONAL INFORMATION:
 * 		-Extra zeroes likely exist at front of decompressed binary,
 * 		ensure it is same length as the original binary by erasing
 * 		the characters starting at 0 until length is same.
 */ 
string Compressor::decompressBinary(string charbase){
	string to_return;

	for (int i = 0; i < (int) charbase.size(); i++){
		to_return += charToBinary(charbase.at(i));
	}

	return to_return;	
}

/* Purpose: Decmpress base 128 string to decimal number
 * Parameters: string - compressed integer
 * Returns: int - decompressed integer
 *
 */ 
int Compressor::decompressDecimal(string charbase){
	(void) charbase;
	return 5;
}


/*********************PRIVATE FUNCTIONS*********************/
string Compressor::charToBinary(int to_convert){
	string binary = "";

	for (int i = 6; i >= 0; i--){
		if (to_convert / pow(2, i) >= 1){
			to_convert -= pow(2, i);
			binary += ONE;
		}
		else{
			binary += ZERO;
		}
		
	}

	return binary;
}





