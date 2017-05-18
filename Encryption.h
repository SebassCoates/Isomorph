/*
 *
 *  COMP 15 Project 2 - ISOMORPH 
 *
 *  Encryption.h
 *  Complete Encryption Header and Declaration
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This contains the interface of my encryption algorithm. It permutes
 *  a file stored in a graph and outputs the ciphertext. 
 */

#ifndef ENCRYPTION_H_
#define ENCRYPTION_H_

#include "Graph.h"
#include "Compressor.h"
#include <string>
#include <vector>

using namespace std;

class Encryption
{
	public: 
		Encryption(string);
		~Encryption();
		
		/*Run the encryption process*/
		void run();
		
	private:
		/*To store name of plaintext file*/
		string file_name;

		/*Used to efficiently, randomly permuate graph*/
		int *label_permutation;
		
		/*Randomly permute graph to encrypt*/
		void randomizeMap(int);

		/*Output permuted graph to file*/
		void outputCiphertext(Graph *);

		/*Output padding and label information to file*/
		void outputKey(Graph *);
};

#endif
