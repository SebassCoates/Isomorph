/*
 *
 *  COMP 15 Project 2 - ISOMORPH 
 *
 *  Decryption.h
 *  Complete Decryption Header and Declaration
 *  Modified By (UTLN):scoate02
 *           On       :May 16, 2017
 *  
 *
 *  This contains the interface of my decryption algorithm. It permutes
 *  a file stored in a graph to decrypt it, and outputs the new plaintext. 
 */

#ifndef DECRYPTION_H_
#define DECRYPTION_H_

#include "Graph.h"
#include "Compressor.h"
#include <fstream> 
#include <string>

using namespace std;

class Decryption
{
	public: 
		Decryption(string, string);
		~Decryption();
		
		/*run the decryption process*/
		void run();
   
	private:
		/*Store name of file with encrypted text*/
		string file_name;

		/*Store name of file with key information*/
		string key_name;

		/*Read key and decrypt graph*/
		void readKey(Graph *);

		/*Output decrypted ciphertext to file*/
		void outputPlaintext(Graph *);
};

#endif
