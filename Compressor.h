/*
 *
 *  COMP 15 Project 2 - ISOMORPH 
 *
 *  Compressor.h
 *  Complete Compresseion Scheme Header
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This is the interface of the compression scheme used to reduce the file 
 *  size of the key
 */

#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <string>

using namespace std;

class Compressor{

	public:
		Compressor();
		~Compressor();

		/*Compress to base 128*/
		string compressBinary(string);
		string compressDecimal(int);

		/*Decompress string to original base*/
		string decompressBinary(string);
		int decompressDecimal(string);

	private:
		static const char ZERO = '0';
		static const char ONE = '1'; 

		string charToBinary(int);
};
 
#endif