/*
 *
 *  COMP 15 Project 2 - ISOMORPH 
 *
 *  Graph.h
 *  Complete Graph Header and Declaration
 *  Modified By (UTLN):scoate02
 *           On       :April 13, 2017
 *  
 *
 *  This is the interface of the graph data structure as needed in my 
 *  program. It represents graphs using 2D arrays with the invariant that if
 *  data in two rows are swapped, the data in the corresponding columns must
 *  also be swapped. 
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>

using namespace std;

class Graph
{
	public: 
		Graph(string file_name);
		~Graph();
		bool operator==(const Graph &) const;
		
		/*Return dimension*/
		int size() const;

		/*Allow client to access values of graph*/
       		int getValue(int row_value, int colum_value) const;

       		/*Return length of pad (0s added to fill graph)*/
       		int getPadLength();

       		/*Return bits in pad as string*/
       		string getPadText();

       		/*Update pad with string of bits*/
       		void setPadText(string);
		
		/*Switch labels in graph*/
		void permute(int label_1, int label_2);

		/*Get string of chars stored in graph as bits*/
		string getString();

		/*Debug function, print graph bits in square shape*/
		void print();

	private:
		/*Dynamic 2D array to store data*/
		bool ** graph;

		/*Width/height of graph array*/
		int dimension;

		/*Number of bits added to pad back of graph*/
		int pad_length;

		/*Add contents of file to graph*/
		void populateGraph(string *);		
};

#endif
