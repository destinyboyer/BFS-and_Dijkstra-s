/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Professor:	Min Chen
	Class:		CSS343
	Project:	Assignment 3

-------------------------------------------------------------------------------------------------*/

#pragma once
#ifndef graphl_h
#define graphl_h

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

int const MAXNODES_L = 101; 

class GraphL {

	public:

		GraphL(void);
		~GraphL(void);

		void buildGraph(ifstream& inFile);
		void depthFirstSearch(void);
		void displayGraph(void);
	
	private:

		struct EdgeNode {
			int adjacentNode;
			EdgeNode* next;
			EdgeNode(void) : adjacentNode(0), next(nullptr) {};
		};

		struct GraphNode {
			EdgeNode* edgeHead;
			NodeData* data;
			bool visited;
			GraphNode(void) : edgeHead(nullptr), data(nullptr), visited(false) {};
		};
		
		void dfs(int index);
		void makeEmpty(void);
		int size;
		GraphNode node_array[MAXNODES_L];

};


#endif //graphl_h
