/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  Encryption.cpp
 *  Complete Encryption Implementation
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This contains the implementation of my encryption algorithm. It permutes
 *  a file stored in a graph and outputs the ciphertext. 
 *
 */

#include "Encryption.h"
#include "Compressor.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

/*Constructor*/
Encryption::Encryption(string plaintext)
{
	srand(time(NULL)); /*Set seed randomly*/
	file_name = plaintext;
	label_permutation = NULL;
}

/*Destructor*/
Encryption::~Encryption()
{
	if (label_permutation != NULL){
		delete []label_permutation;
	}
}

/* Purpose: Run the encryption process
 * Parameters: None
 * Returns: void
 *
 */ 
void Encryption::run()
{
	Graph filedata(file_name);
	randomizeMap(filedata.size());

	/*Permute graph according to new permutation*/
	for (int i = 0; i < filedata.size() - 1; i++){
		filedata.permute(label_permutation[i], label_permutation[i+1]);
	}

	outputCiphertext(&filedata);
	outputKey(&filedata); 
}


/******************PRIVATE FUNCTIONS******************/

/* Purpose: Randomly pair labels to be permuted
 * Parameters: int - number of labels in graph
 * Returns: void
 *
 */ 
void Encryption::randomizeMap(int num_labels)
{
	if (num_labels > 0){ /*Perhaps unecessary check, but safe*/
		label_permutation = new int[num_labels];
	}

	for (int i = 0; i < num_labels; i++){
		label_permutation[i] = i;
	}

	/*Make n random swaps to create permutation*/
	for (int i = 0; i < num_labels; i++){
		int rand_index = (int) (rand() % num_labels);

		if (rand_index != i){ /*Only swap if meaningful*/
			int to_swap = label_permutation[rand_index];
			label_permutation[rand_index] = label_permutation[i];
			label_permutation[i] = to_swap;
		}
	}
}

/* Purpose: Save encrypted data to new filed called "encrypted.txt"
 * Parameters: Graph - permuted graph to print
 * Returns: void
 *
 */ 
void Encryption::outputCiphertext(Graph *filedata)
{
	ofstream outfile;
	outfile.open("encrypted.txt");

	string ciphertext = filedata->getString();
	outfile << ciphertext;

	outfile.close();
}

/* Purpose: Print the key information to "key.txt"
 * Parameters: Graph - permuted graph to get pad information
 * Returns: void
 *
 */ 
void Encryption::outputKey(Graph *filedata)
{
	string pad_text = filedata->getPadText();

	ofstream outfile;
	outfile.open("key.txt");

	Compressor comp;
	string compressed_pad = comp.compressBinary(pad_text);

	char flag = 128;  /*Not created by comopression*/
	if (pad_text != ""){
		outfile <<  compressed_pad << flag;

	}

	for (int i = 0; i < filedata->size(); i++){
		outfile << label_permutation[i];
		outfile << " ";
	}

	outfile.close();
}
