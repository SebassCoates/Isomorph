/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  Bruteforce.cpp
 *  Complete Bruteforce Main 
 *  Modified By (UTLN):scoate02
 *           On       :May 18, 2017
 *  
 *
 *  This is the main implmementation for my bruteforce decrypted process. This
 *  aims to show the time complexity of brute force decrypted a file encrypted
 *  using my graph isomorphic encryption scheme. 
 *
 */

#include "Graph.h"
#include "termfuncs.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <unistd.h>

using namespace std;

bool checkPermutations(string, string);
string nextLex(string);
bool permuteGraph(Graph *, Graph *, string);
int nextGraphPermutation(int, int, vector <int> *, vector <int> *);
void printVector(vector <int> *);
void swapLabels(Graph *, vector <int> *);
void reswapLabels(Graph *, vector <int> *);

int main(int argc, char* argv[])
{
	if (argc != 3){
		cerr << "Usage: ciphertext plaintext" << endl;
		exit(1);
	}

	hide_cursor();
	screen_clear();
	cerr << "Beginning bruteforce decryption process" << endl;
	usleep(2000000);
	cerr << "Starting in..." << endl;
	usleep(1000000);
	cerr << "3" << endl;
	usleep(1000000);
	cerr << "2" << endl;
	usleep(1000000);
	cerr << "1" << endl;
	usleep(100000);

	if (checkPermutations((string) argv[1], (string) argv[2])){
		cerr << "Successfully decrypted" << endl;
	}
	else{
		cerr << "Not same file - Decryption Failed!" << endl;
	}
	
	return 0;
}

/* Purpose: Check all possibile permutations of graph
 * Parameters: string - name of ciphertext file, string - name of plaintext 
 									file
 * Returns: bool - true if graph decrypted, false if not same file
 *
 */ 
bool checkPermutations(string cipherfile, string plainfile)
{
	Graph plain(plainfile), cipher(cipherfile);
	if (plain == cipher){
		return true;
	}

	string pad = cipher.getPadText(), pad_permutation = "", flag = "";
	for (size_t i = 0; i < pad.size(); i++){
		pad_permutation.push_back('0');
		flag.push_back('1');
	}

	bool done_decrypting = permuteGraph(&plain, &cipher, pad_permutation);
	if (done_decrypting){
		return true;
	}

	while (pad_permutation != flag){
		pad_permutation = nextLex(pad_permutation);
		bool done_decrypting = 
			permuteGraph(&plain, &cipher, pad_permutation);

		if (done_decrypting){
			return true;
		}	
	}
	return false;
}

/* Purpose: Return next lexographic string of binary numbers
 * Parameters: string - pad of 0s and 1s
 * Returns: string - next greater string lexographically
 *
 */ 
string nextLex(string pad)
{
	int size = (int) pad.size();
	for (int i = size - 1; i >= 0; i--){
		if (pad[i] == '0'){
			pad[i] = '1';
			for (int j = i + 1; j < size; j++){
				pad[j] = '0';
			}
			break;
		}
	}
	return pad;
}

/* Purpose: Check permutations of graph with given pad
 * Parameters: Graph * - plaintext, Graph *- ciphertext, guessed pad
 * Returns: bool - true if decrypted successfully, else false
 *
 */ 
bool permuteGraph(Graph *plain, Graph *cipher, string pad)
{
	cipher->setPadText(pad);
	vector <int> label_scheme, label_flag;

	for (int i = 0; i < (int) cipher->size(); i++){
		label_scheme.push_back(i);
		label_flag.push_back(cipher->size() - 1 - i);
	}
	
	swapLabels(cipher, &label_scheme);

	if (*plain == *cipher){
		return true;
	}
	else{
		reswapLabels(cipher, &label_scheme); /*fix graph*/
	}

	int index = 0;
	int flag = 0; 
	vector <int> c;
	while (label_scheme != label_flag){
		flag = nextGraphPermutation(index, flag, &label_scheme, &c);
		if (flag == 2){
			index++;
		}
		if (flag == 3){
			index = 0;
		}
		if (flag == 4){
			break;
		}
		
		screen_clear();
		cerr << "Pad: " << pad << endl;
		cerr << "Permutation: "; printVector(&label_scheme);
		cerr << endl;
	
		swapLabels(cipher, &label_scheme);

		if (*plain == *cipher){
			return true;
		}
		else{
			reswapLabels(cipher, &label_scheme); /*fix graph*/
		}
	}	
	return false;
}

/* Purpose: Use Heap's algorithm to generate next permutation
 * Parameters: vector <int> * - representation of label pairings
 * Returns: void
 *
 * 
 * Additional Info: 
 * 		HEAP'S ALGORITHM (Decomposed for repeated function calls)
 * 		Return Flag Meanings:
 *		0 - first call
 *		1 - neutral 
 * 		2 - increment index
 * 		3 - reset index
 * 		4 - stop
 */ 
int nextGraphPermutation(int index, int flag, 
	vector <int> *label_scheme, vector <int> *c)
{
	


	if (flag == 0){
		for (int i = 0; i < (int) label_scheme->size(); i += 1){
	       		c->push_back(0);
		}
		return 1;
	}
	    
	while (index < (int) label_scheme->size()){
	        if  ((*c)[index] < index){
	                if (index %2 == 0) {
	             		int temp = (*label_scheme)[0];
	             		(*label_scheme)[0] = (*label_scheme)[index];
	             		(*label_scheme)[index] = temp;
	                }
	                else{
	                	int temp = (*label_scheme)[(*c)[index]];
	                	(*label_scheme)[(*c)[index]] = 
	                		(*label_scheme)[index];
	                	(*label_scheme)[index] = temp;
	                }
	            	(*c)[index] += 1;
	            	return 3;
	        }
	        else{
	            	(*c)[index] = 0;
	            	return 2;
	        }
	}

	return 4;
}

/* Purpose: Print a vector
 * Parameters: vector <int> * - vector to print
 * Returns: void
 *
 */ 
void printVector(vector <int> *to_print)
{
	for (int i = 0; i < (int) to_print->size(); i++){
		cerr << (int) (*to_print)[i];
	}
	cerr << endl;
}

/* Purpose: Permute labels in graph using vector as representation of pairing
 * Parameters: Graph * - ciphertext in graph, vector <int> * - labeling scheme
 * Returns: void
 *
 */ 
void swapLabels(Graph *cipher, vector <int> *label_scheme)
{
	//cerr << "Preswap:" << endl;
	//cipher->print();
	//cerr << endl;
	for (int i = 0; i < (int) label_scheme->size() - 1; i++){
		cipher->permute((*label_scheme)[i], (*label_scheme)[i+1]);
	}
	//cerr << "Postswap:" << endl;
	//cipher->print();
	//cerr << endl;
}

/* Purpose: Repermute labels in graph using vector as representation of pairing
 * Parameters: Graph * - ciphertext in graph, vector <int> * - labeling scheme
 * Returns: void
 *
 */ 
void reswapLabels(Graph *cipher, vector <int> *label_scheme)
{
	for (int i = label_scheme->size() - 1; i > 0; i--){
		cipher->permute((*label_scheme)[i], (*label_scheme)[i-1]);
	}
	//cerr << "Post reswap:" << endl;
	//cipher->print();
	//cerr << endl;
}