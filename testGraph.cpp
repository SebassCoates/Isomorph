/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  testGraph.cpp
 *  Complete Graph Testing Main 
 *  Modified By (UTLN):scoate02
 *           On       :April 13, 2017
 *  
 *
 *  This is my testing file for the Graph data structure. It ensures full 
 *  functionality, like going from file to graph and graph to file. It also 
 *  tests the permute functionality, which enables the encryption/decryption
 *  of files. 
 *
 */

#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

void displayError();
void testConstructor(string);
void testPermute(string);
void testComparison(string, string);

int main(int argc, char *argv[])
{
	if (argc != 3){
		displayError();
	}
	
	string filename = (string) argv[1];
	string other_filename = (string) argv[2];

	testConstructor(filename);
	testPermute(filename);
	testComparison(filename, other_filename);

	return 0;
}

/*display error on invalid input and exit*/
void displayError()
{
	cerr << "Usage: file_name file_name" << endl;
	exit(1);
}

/*Test constructor and destructor*/
void testConstructor(string file_name)
{
	Graph g(file_name);
}

/*Test permute function works properly*/
void testPermute(string file_name)
{
	Graph g(file_name);
	cerr << "printing original graph..." << endl;
	g.print();
	cerr << "permuting 0,1..." << endl;
	g.permute(0,1);
	g.print();
}

/*Test overloaded operator == works properly*/
void testComparison(string file_name, string other_file_name)
{
	Graph g0(file_name);
	Graph g1(other_file_name);

	if (g0 == g1){
		cerr << "Files are the same!" << endl;
	}
	else{
		cerr << "Files are different!" << endl;
	}
}
