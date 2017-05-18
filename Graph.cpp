/*
 *
 *  COMP 15 Project 2 - ISOMORPH
 *
 *  Graph.cpp
 *  Complete Graph Implementation
 *  Modified By (UTLN):scoate02
 *           On       :April 13, 2017
 *  
 *
 *  This is the implementation of the graph data structure as needed in my 
 *  program. It represents graphs using 2D arrays with the invariant that if
 *  data in two rows are swapped, the data in the corresponding columns must
 *  also be swapped. 
 *
 */

#include "Graph.h"
#include <fstream>
#include <math.h>
#include <bitset>
#include <iostream>
#include <sstream>

using namespace std;

/*Constructor*/
Graph::Graph(string file_name)
{
	ifstream infile;
	infile.open(file_name);
	
	if (!infile.is_open()){
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}

	string complete_filetext = "";
	stringstream strStream;
	strStream << infile.rdbuf(); /*Read complete file to string stream*/
	complete_filetext = strStream.str(); /*Store complete file text*/

	infile.close();
	populateGraph(&complete_filetext);
}

/*Destructor*/
Graph::~Graph()
{
	for (int i = 0; i < dimension; i++){
		delete [] graph[i];
	}
	delete [] graph;
}

/*Comparison Overload Operator*/
bool Graph::operator==(const Graph &other_graph) const 
{
	if (dimension != other_graph.size()){
		return false;
	}

	for (int r = 0; r < dimension; r++){
		for (int c = 0; c < dimension; c++){
			if (graph[r][c] != other_graph.getValue(r,c)){
				return false;
			}
		}
	}

	return true;
}

/* Purpose: Return size of graph (height/width dimension)
 * Parameters: None
 * Returns: int - dimension of graph
 *
 */ 
int Graph::size() const
{
	return dimension;
}

/* Purpose: Access value at graph (is there edge between two vertices?)
 * Parameters: int - row value, int col value
 * Returns: int - value at specified coordinates
 * 		if int value = 1, there is edge between vertex of label row
 * 		and vertex of label col in graph
 *
 */ 
int Graph::getValue(int row, int col) const
{
	return graph[row][col];
}

/* Purpose: Return the length of padding (0s added to end of graph)
 * Parameters: None
 * Returns: int - num chars in pad
 *
 */ 
int Graph::getPadLength()
{
	return pad_length;
}

/* Purpose: Return string of chars represented by graph
 * Parameters: None
 * Returns: string - bits of graph converted to chars and joined together
 *
 */ 
string Graph::getPadText()
{
	if (pad_length == 0){
		return "";
	}

	int bits_counted = 0;
	int target = dimension * dimension - pad_length;
	string pad_text;

	for (int r = 0; r < dimension; r++){
		for (int c = 0; c < dimension; c++){
			bits_counted++;
			if (bits_counted > target){
				pad_text.push_back(graph[r][c] + 48);
			}
		}
	}
	return pad_text;
}

/* Purpose: Set the pad text to new values
 * Parameters: string - bits represented in string to add to end of graph
 * Returns: void
 *
 */ 
void Graph::setPadText(string pad_text)
{
	int row_index = dimension - 1;
	int column_index = row_index;
	int length = (int) pad_text.length();

	for (int i = length -1; i >= 0; i--){
		graph[row_index][column_index] = pad_text.at(i) - 48;
		column_index--;
		if (column_index < 0){
			column_index = dimension-1;
			row_index--;
		}
	}
}

/* Purpose: Swap two labels in the graph 
 * Parameters: 2 ints - indices of labels to swap [0-dimension)
 * Returns: void
 *
 */ 
void Graph::permute(int label_1, int label_2)
{
	if (label_1 < 0 || label_1 >= dimension){
		cerr << "Invalid label = " << label_1 << endl;
		//throw runtime_error ("bad_permute");
	}

	else if (label_2 < 0 || label_2 >= dimension){
		cerr << "Invalid label = " << label_2 << endl;
		//throw runtime_error ("bad_permute");
	}

	else{
		/*copy rows*/
		bool *temp_array = graph[label_1];
		graph[label_1] = graph[label_2];
		graph[label_2] = temp_array;

		/*copy columns*/
		for (int c = 0; c < dimension; c++){
			int temp = graph[c][label_1];
			graph[c][label_1] = graph[c][label_2];
			graph[c][label_2] = temp;
		}
	}
}

/* Purpose: Get string of chars stored in graph
 * Parameters: None
 * Returns: string - bits in graph converted to chars and joined together
 * 
 * Additional Info:
 * 		This ignores chars in the padding. Those can be accessed with
 *		getPadText()
 */ 
string Graph::getString()
{
	int total_bits_read = 0; /*serves as flag for end of valid bits*/
	int curr_bit = 0; /*counts bits*/
	int curr_bits_read = 0;
	char char_value = 0;
	int bits_to_read = dimension * dimension - pad_length;

	string graph_text = "";
	for (int r = 0; r < dimension; r++){
		for (int c = 0; c < dimension; c++){
			curr_bit = graph[r][c];
			char_value += curr_bit * pow(2, (7 - curr_bits_read));
			curr_bits_read++;
			total_bits_read++;
			if (curr_bits_read == 8){
				graph_text += char_value;
				curr_bits_read = 0;
				char_value = 0;
			}
			if (total_bits_read == bits_to_read){ /*end loops*/
				c = dimension;
				r = dimension;
			}
		}
	}
	return graph_text;
}

/* Purpose: Print graph in row x col grid
 * Parameters: None
 * Returns: void
 *
 */ 
void Graph::print()
{
	for (int r = 0; r < dimension; r++){
		for (int c = 0; c < dimension; c++){
			cout << graph[r][c]; 
		}
		cout << endl;
	}
}


/******************PRIVATE FUNCTIONS******************/

/* Purpose: Store file data in graph
 * Parameters: string - complete text in file
 * Returns: void
 *
 */ 
void Graph::populateGraph(string *filetext)
{
	/*round up to nearest int, 8 bits in a char*/
	dimension = ceil(sqrt(filetext->size() * 8)); 
	
	graph = new bool*[dimension];
	for (int i = 0; i < dimension; i++){
		graph[i] = new bool[dimension];
	}

	string bits = ""; /*Convert string of chars to string of bits*/
	for (int i = 0; i < (int) filetext->size(); i++){
		/*Convert char to binary, cast as string + append*/
		bits += bitset<8>(filetext->c_str()[i]).to_string();
	}

	pad_length = dimension * dimension - bits.size();

	int bit_count = 0; /*Add bits, pad_length to graph*/
	for (int r = 0; r < dimension; r++){
		for (int c = 0; c < dimension; c++){
			bit_count = (dimension * r) + c;
			if (bit_count >= (int) bits.size()){
				graph[r][c] = 0; /*Add pad_length*/
			}
			else{
				/*Add bit to graph '0' or '1'*/
				graph[r][c] = bits.at(bit_count) - 48;
			}
		}
	}
}
