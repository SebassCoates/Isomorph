/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  Isomorph.cpp
 *  Complete Isomorph Main 
 *  Modified By (UTLN):scoate02
 *           On       :April 13, 2017
 *  
 *
 *  This is the main implmementation for my Isomorph program. It handles user
 *  input and determiens whether to encrypt or decrypt. 
 *
 */

#include "Encryption.h"
#include "Decryption.h"
#include <iostream>
#include <string>

using namespace std;

void validateInput(int, char**);
void displayError();
void encrypt(char *);
void decrypt(char *, char *);


int main(int argc, char* argv[])
{
	validateInput(argc,argv);
	if (argc == 3){
		encrypt(argv[2]);
	}
	else {
		decrypt(argv[2], argv[3]);
	}
	return 0;
}

/* Purpose: Verify command line input is valid. If not, display error & quit
 * Parameters: int, char** - command line arguments
 * Returns: void
 *
 */ 
void validateInput(int argc, char* argv[])
{
	if (argc != 3 && argc != 4){
		displayError();
	}

	if (argc == 3){
		if ((string) argv[1] != "-encrypt"){
			displayError();		
		}
	}	

	if (argc == 4){
		if ((string) argv[1] != "-decrypt"){
			displayError();
		}
	}
}

/* Purpose: Display error and exit program
 * Parameters: None
 * Returns: void
 *
 */ 
void displayError()
{
	cerr << "Usage: mode textfile [key]" << endl;
	cerr << "\t \t where: mode is -encrypt or -decrypt" << endl;
	cerr << "\t \t and:   key is used with -decrypt" << endl;
	exit(1);
}

/* Purpose: Encrypt file passed through command line
 * Parameters: char * - name of file to encrypt
 * Returns: void
 *
 */ 
void encrypt(char *file_name)
{
	Encryption encipher((string) file_name);
	encipher.run();
}

/* Purpose: Decrypt file passed through command line
 * Parameters: char * - name of file to encrypt, char * - name of key file
 * Returns: void
 *
 */ 
void decrypt(char *text_name, char *key_name)
{
	Decryption decipher((string) text_name, (string) key_name);
	decipher.run();
}
