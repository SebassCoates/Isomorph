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
	string to_return = "";
	
	int divisor = 128;

	while (decimal > 0){
		string add_front = "";
		add_front += (char) (decimal % divisor);

		to_return = add_front + to_return; 

		decimal /= divisor;
	}

	return to_return;
}

/* Purpose: Decmpress base 128 string to binary number
 * Parameters: string - compressed integer
 * Returns: int - decompressed integer
 *
 * ADDITIONAL INFORMATION:
 * 		-Extra zeroes often exist at front of decompressed binary,
 * 		ensure it is same length as the original binary by erasing
 * 		the characters starting at 0 until length is same.
 * 		(This occurs when compressing string of bits with a length
 		that is not a multiple of 8)
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
	int decimal = 0;

	for (int i = (int) charbase.size() - 1; i >= 0; i--){
		int integerAtIndex = charbase.at(i);
		decimal += integerAtIndex * pow(128, charbase.size() - 1 - i);
	}
	
	return decimal;
}


/*********************PRIVATE FUNCTIONS*********************/

/* Purpose: Convert character to string of bits
 * Parameters: int - ascii value of character
 * Returns: string - string of bits representing char
 *
 */ 
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





