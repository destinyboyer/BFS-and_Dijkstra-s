/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Professor:	Min Chen
	Class:		CSS343
	Project:	Assignment 3

-------------------------------------------------------------------------------------------------*/

#pragma once
#ifndef graphm_h
#define graphm_h

#include <iostream>
#include <string>
#include <iomanip>
#include "nodedata.h"

using namespace std;

int const MAXNODES = 101;

class GraphM {

	public:

		struct TableType {		//struct to keep the current shortest distance
			bool visited;		//whether the Node has been visited
			int distance;		//shortest distance from source know so far
			int path;			//previous Node in path of min distance
			TableType(void) : visited(false), distance(INT_MAX), path(0) {};
		};

		GraphM(void);
		~GraphM(void);
		void buildGraph(istream& inFile);
		bool insertEdge(int, int, int);
		void findShortestPath(void);
		void displayAll(void) const;
		void display(int from, int to) const;

	private:

		NodeData data[MAXNODES];
		int cost[MAXNODES][MAXNODES];
		int size;
		TableType T[MAXNODES][MAXNODES];
		void printPath(int row, int column) const;
		void printData(int row, int column) const;
};

#endif // !graphm_h
