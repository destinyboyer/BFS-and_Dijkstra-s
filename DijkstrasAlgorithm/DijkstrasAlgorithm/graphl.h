/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Date:		2/14/2017
	Version:	1.0

-------------------------------------------------------------------------------------------------*/

#pragma once
#ifndef graphl_h
#define graphl_h

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

int const MAXNODES_L = 101; //maximum number of nodes in the graph

class GraphL {

	public:

		GraphL(void);
		~GraphL(void);

		void buildGraph(ifstream& inFile);		//builds a GraphL object
		void depthFirstSearch(void);			//performs a depth-first-search
		void displayGraph(void);				//displays description of node and
												//other nodes it can reach
	
	private:
		
		//class for nodes that can be reached by nodes
		//nodes in the adjacencyList
		class EdgeNode {
			public:
				int adjacentNode;
				EdgeNode* next;
				EdgeNode(void) : adjacentNode(0), next(nullptr) {};
				~EdgeNode(void) {
					delete next;
					next = nullptr;
			};
		};

		//class for nodes in the adjacencyList
		class GraphNode {
			public:
				EdgeNode* edgeHead;
				NodeData* data;
				bool visited;
				GraphNode(void) : edgeHead(nullptr), data(nullptr), visited(false) {};
				~GraphNode(void) {
					delete data;
					data = nullptr;
					delete edgeHead;
					edgeHead = nullptr;
			};
		};
		
		void dfs(int index);
		int size;		//number of active nodes in adjacencyList
		GraphNode adjacencyList[MAXNODES_L];	//stores nodes in graph

};


#endif //graphl_h
