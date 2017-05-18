/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  testCompressor.cpp
 *  Complete Compression Scheme Testing Main
 *  Modified By (UTLN):scoate02
 *           On       :May 17, 2017
 *  
 *
 *  This tests all the functionality of the compression class, compressing 
 *  and decompressing binary and decimal numbers
 *
 */

#include "Compressor.h"
#include <string>
#include <iostream>

using namespace std;

void testBinary();
void testDecimal();

int main()
{
	//testBinary();
	testDecimal();
	return 0;
}

void testBinary()
{	
	Compressor compress;
	string compressed = compress.compressBinary("01111001");
	cout << "01111001 in charbase is: " << compressed << endl;
	cout << "Expected: 'y' " << endl;

	compressed = compress.compressBinary("0111100101111001");
	cout << "0111100101111001 in charbase is: " << compressed << endl;
	cout << "Expected: 'yy' " << endl;

	string decompressed = compress.decompressBinary("y");
	cout << "y in binary is: " << decompressed << endl;
	cout << "Expected: '01111001' " << endl;

	decompressed = compress.decompressBinary("yy");
	cout << "yy in binary is: " << decompressed << endl;
	cout << "Expected: '0111100101111001' " << endl;
	
	string binary = "101010101";
	compressed = compress.compressBinary(binary);
	cout << "Original binary = " << binary << endl;
	cout << "Compressed = " << compressed << endl;
	decompressed = compress.decompressBinary(compressed);
	while (decompressed.size() > binary.length()){
			decompressed.erase(0,1);
		}
	cout << "Decompressed " << decompressed << endl;
}

void testDecimal()
{
	Compressor compress;
	
}