/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Date:		2/14/2017
	Version:	1.0

-------------------------------------------------------------------------------------------------*/

#include "graphl.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
//								Constructors / Destructors										 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------

	Default no-args constructor.

-------------------------------------------------------------------------------------------------*/

GraphL::GraphL(void) {

};

/*-------------------------------------------------------------------------------------------------

	Destructor.

-------------------------------------------------------------------------------------------------*/

GraphL::~GraphL(void) {

};

///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
//										Public Methods											 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------

	Method takes in a file stream and populates the adjacencyList with each node's description
	as well as the adjacent nodes.

	NOTES:	populating node's with data is the responsibility of the NodeData class.

-------------------------------------------------------------------------------------------------*/

void GraphL::buildGraph(ifstream& inFile) {
	int numNodes;		//temp variable for size
	int headNode = 0;	//temp variables for populating list
	int toInsert = 0;

	inFile >> numNodes;		//sets size equal to the number of nodes + 1
	size = numNodes + 1;

	string clearLine = "";
	getline(inFile, clearLine);

	//inserts nodes with names for each of the head nodes
	for (int index = 1; index < size; index++) {
		NodeData* temp = new NodeData();
		temp->setData(inFile);
		adjacencyList[index].data = temp;
		temp = nullptr;
	}

	//cycles through the nodes and inserts them in to the list
	while (inFile >> headNode >> toInsert) {
		if (headNode == 0) {	//if we reach the end of the data
			break;
		}
		//creates new node and inserts it directly to the
		//Graph Node if there are no other nodes in the list
		if (adjacencyList[headNode].edgeHead == nullptr) {
			EdgeNode* insertNode = new EdgeNode();
			insertNode->adjacentNode = toInsert;
			adjacencyList[headNode].edgeHead = insertNode;
			adjacencyList[headNode].edgeHead->next = nullptr;
		//inserts node betweem the Graph Node and
		//its adjacent node
		} else {
			EdgeNode* insertNode = new EdgeNode();
			insertNode->adjacentNode = toInsert;
			insertNode->next = adjacencyList[headNode].edgeHead;
			adjacencyList[headNode].edgeHead = insertNode;
		}
		if (inFile.eof()) {
			break;
		}
	}
}

/*-------------------------------------------------------------------------------------------------

	Method performs a depth first search by calling dfs() and recursing through
	the nodes in the graph.

-------------------------------------------------------------------------------------------------*/

void GraphL::depthFirstSearch(void) {
	cout << "Depth-first ordering: ";	//prints heading
	for (int index = 1; index < size; index++) {		//cycles through each unvisited node
		if (adjacencyList[index].visited == false) {
			dfs(index);
		}
	}
};

/*-------------------------------------------------------------------------------------------------

	Method displays the graph, with each of the nodes and the nodes in each rows
	adjacency list.

-------------------------------------------------------------------------------------------------*/

void GraphL::displayGraph(void) {
	cout << "Graph:" << endl;
	for (int row = 1; row < size; row++) {
		cout << "Node " << row <<"\t" << *adjacencyList[row].data << endl;
		EdgeNode* current = adjacencyList[row].edgeHead;
		while (current != nullptr) {
			cout << "   edge " << row << " " << current->adjacentNode << endl;
			current = current->next;
		}
	}
	cout << endl;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
//										Private Methods											 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------

	Recursive method to calculate the depth first search.

-------------------------------------------------------------------------------------------------*/

void GraphL::dfs(int index) {
	cout << index << " ";
	adjacencyList[index].visited = true;
	EdgeNode* current = adjacencyList[index].edgeHead;

	while (current != nullptr) {
		if (adjacencyList[current->adjacentNode].visited == false) {
			dfs(current->adjacentNode);
		}
		current = current->next;
	}
};