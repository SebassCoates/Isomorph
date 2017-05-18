/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  Decryption.cpp
 *  Complete Decryption Implementation
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This contains the implementation of my decryption algorithm. It permutes
 *  a file stored in a graph to decrypt it, and outputs the new plaintext. 
 */

#include "Decryption.h"
#include "Compressor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector> 

using namespace std;

/*Constructor*/
Decryption::Decryption(string ciphertext, string key)
{
	file_name = ciphertext;
	key_name = key;
}

/*Destructor*/
Decryption::~Decryption()
{
	/*Nothing to delete*/	
}

/* Purpose: Run the decryption process
 * Parameters: None
 * Returns: void
 *
 */ 
void Decryption::run()
{
	Graph filedata(file_name);
	readKey(&filedata);
	outputPlaintext(&filedata);
}


/******************PRIVATE FUNCTIONS******************/

/* Purpose: Read key information from file and decipher grapher
 * Parameters: Graph - graph to permute with key data
 * Returns: void
 *
 */ 
void Decryption::readKey(Graph *filedata)
{
	Compressor comp;

	ifstream infile;
	infile.open(key_name);
	if (!infile.is_open()){
		cerr << "Error: file could not be opened" << endl;
	}

	string keyfile_text = "";
	stringstream strStream;
	strStream << infile.rdbuf(); /*Read complete file to string stream*/
	keyfile_text = strStream.str(); /*Store complete file text*/
	infile.close();
	
	char flag = 128; /*Not created by comopression*/
	int end_of_key_index = keyfile_text.find(flag);

	string compressed_pad = keyfile_text.substr(0, end_of_key_index);

	string com_permutation = 
	keyfile_text.substr(end_of_key_index + 1, keyfile_text.length());

	string compressed_binary  = comp.decompressBinary(compressed_pad);
	while ((int)compressed_binary.size() > filedata->getPadLength()){
		compressed_binary.erase(0,1);
	}
	filedata->setPadText(compressed_binary);

	vector <int> permutation;
	while(com_permutation.size() > 0){
		end_of_key_index = com_permutation.find(flag);
		string value = com_permutation.substr(0, end_of_key_index);
		if (value.size() > 0){
			permutation.push_back(comp.decompressDecimal(value));
		}
		com_permutation.erase(0, end_of_key_index + 1);
	}
	
	for (int i = permutation.size() - 1; i > 0; i--){
		filedata->permute(permutation[i], permutation[i-1]);
	}
}

/* Purpose: Output decrypted graph to file called "decrypted.txt"
 * Parameters: None
 * Returns: void
 *
 */ 
void Decryption::outputPlaintext(Graph *filedata)
{
	ofstream outfile;
	outfile.open("decrypted.txt");
	outfile << filedata->getString();
	outfile.close();
}
