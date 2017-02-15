/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Professor:	Min Chen
	Class:		CSS343
	Project:	Assignment 3

-------------------------------------------------------------------------------------------------*/

#include "graphm.h"

/*-------------------------------------------------------------------------------------------------

	Default no-args constructor. Initializes all indices in the cost array to INT_MAX.

-------------------------------------------------------------------------------------------------*/

GraphM::GraphM(void) {
	size = 0;
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++) {
			cost[i][j] = INT_MAX;
		}
	}
};

/*-------------------------------------------------------------------------------------------------

	Default destructor

-------------------------------------------------------------------------------------------------*/

GraphM::~GraphM(void) {

};

/*-------------------------------------------------------------------------------------------------

	Method takes in a file stream and populates the cost matrix with the correct data.
	Sets the description for each of node.

-------------------------------------------------------------------------------------------------*/

void GraphM::buildGraph(istream & inFile) {
	int numNodes;					//temp variable
	string temp;
	inFile >> numNodes;				//inputs number of nodes
	getline(inFile, temp);
	size = numNodes + 1;			//initializes size to the number of
									//nodes + 1 to account for starting index
	for (int index = 1; index < size; index++) {
		data[index].setData(inFile);	//sets the description for each node
	}

	int firstNode, secondNode, weight;		//temp variables

	while (inFile >> firstNode) {

		if (firstNode == 0) {	//checks if we have reached the end of
			break;				//the data for the graph
		}

		inFile >> secondNode >> weight;
		if (inFile.eof()) {			//break if end of file is reached
			break;
		}
		cost[firstNode][secondNode] = weight;	//sets adjacency matrix with data
	}
};

/*-------------------------------------------------------------------------------------------------

	Method finds the shortest path between each node and all other nodes in the graph.
	Method uses Dijkstra's Algorithm to find the shortest path.

-------------------------------------------------------------------------------------------------*/

void GraphM::findShortestPath(void)  {
	//iterates over each node in the graph
	for (int source = 1; source < size; source++) {
		T[source][source].distance = 0;				//node cannot visit itself
		T[source][source].visited = true;			//node has been visited
		int minWeight = INT_MAX;					//min weight
		int v = 0;									//to hold child value

		//iterates over the nodes and sets the corresponding weight
		//data in the T matrix
		for (int n = 1; n < size; n++) {
			if (cost[source][n] != INT_MAX) {
				T[source][n].distance = cost[source][n];
				T[source][n].path = source;
			}
		}

		//iterates over adjacent nodes
			for (int child = 1; child < size; child++) {

				//checks that the node has not been visited and has a valid weight
				if (T[source][child].visited == false && cost[source][child] != INT_MAX) {

					if (cost[source][child] < minWeight) {			//if this is the shortest path
						minWeight = cost[source][child];			//set min weight to this weight
						v = child;									//set v to this lowest node
					}
				}
			}

			T[source][v].visited = true;			//lowest known child has been visited
			
			//iterates over lowestVertex's adjacent nodes to find the smallest
			//weighted unvisited path		
			for (int w = 1; w < size; w++) {
				if (T[source][w].visited == false && cost[v][w] != INT_MAX) {
					if (T[source][w].distance > T[source][v].distance + cost[v][w]) {
						T[source][w].distance = T[source][v].distance + cost[v][w];	//sets new lowest distance
						T[source][w].path = v;	//sets new lowest path
						v = w;	//sets vertex to lowest visited node in pathway
					}
				}
			}
		}
};

/*-------------------------------------------------------------------------------------------------

	Method displays all pathways from each node to all other nodes, including the weight
	and the shortest pathway.

	NOTE:	Method cannot change any data members

-------------------------------------------------------------------------------------------------*/

void GraphM::displayAll(void) const {
	cout << "Description" << setw(20) << "From node" << setw(10) << "To node";	//prints heading
	cout << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

	for (int row = 1; row < size; row++) {	//prints the node we are starting from
		cout << data[row] << endl << endl;

		for (int column = 1; column < size; column++) {		//cycle's through node's adjacent nodes
			if (T[row][column].distance != 0) {
				cout << setw(27) << row;		//prints start node
				cout << setw(10) << column;		//prints destination node

				if (T[row][column].distance == INT_MAX) {	//if there are no adjacent nodes...
					cout << setw(12) << "----" << endl;
				} else {
					cout << setw(12) << T[row][column].distance;
					cout << setw(10);

					printPath(row, column);
					cout << endl;
				}
			}
		}
	}
};

/*-------------------------------------------------------------------------------------------------

	Method prints the path for a given node by calling printPath and printData as hepler
	functions.

-------------------------------------------------------------------------------------------------*/

void GraphM::display(int row, int column) const {
	//checks for validity
	if ((row > size || row < 0) || (column > size || column < 0)) {
		cout << setw(7) << row << setw(7) << column;
		cout << setw(15) << "----" << endl;
		return;
	}
	cout << setw(7) << row << setw(7) << column;
	if (T[row][column].distance != INT_MAX) {
		cout << setw(12) << T[row][column].distance << setw(15);
		printPath(row, column);
		cout << endl;
		printData(row, column);
	} else {
		cout << setw(15) << "----" << endl;
	}
	cout << endl;
};

/*-------------------------------------------------------------------------------------------------

	Method prints the path for a given node and recursively calls itself to print all
	relevant data.

-------------------------------------------------------------------------------------------------*/

void GraphM::printPath(int row, int column) const {
	if (T[row][column].distance != INT_MAX) {
		if (row == column) {
			cout << column << " ";
			return;
		}
		int pathData = column;
		printPath(row, column = T[row][column].path);
		cout << pathData << " ";
	}
};

/*-------------------------------------------------------------------------------------------------

	Method prints the data for a given row and column and then recursively calls itself
	until all the relevant data is printed.

-------------------------------------------------------------------------------------------------*/

void GraphM::printData(int row, int column) const {
	if (T[row][column].distance != INT_MAX) {
		if (row == column) {	//base case
			cout << data[column] << endl;
			return;
		}
		int temp = column;
		printData(row, column = T[row][column].path);  //recursive call incrementing the column
		cout << data[temp] << endl << endl;
	}
};

/*-------------------------------------------------------------------------------------------------

	Method inserts an edge with a specified distance and calls findShortestPath() to recalculate
	the shortest path.

-------------------------------------------------------------------------------------------------*/

bool GraphM::insertEdge(int row, int column, int distance) {
	bool successful = true;		//return value
	
	//checking for valid data
	if (row > size || row < 1 || column > size || column < 1) {
		successful = false;
	}

	if (distance != 0 && row == column || distance < 0) {
		successful = false;
	}

	//insert edge and recalculate shortest path
	cost[row][column] = distance;
	findShortestPath();

	return successful;
};