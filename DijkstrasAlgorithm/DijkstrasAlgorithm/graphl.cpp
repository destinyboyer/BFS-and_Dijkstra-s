/*-------------------------------------------------------------------------------------------------

	Author:		Destiny Boyer
	Professor:	Min Chen
	Class:		CSS343
	Project:	Assignment 3

-------------------------------------------------------------------------------------------------*/

#include "graphl.h"

/*-------------------------------------------------------------------------------------------------

	Default no-args constructor.

-------------------------------------------------------------------------------------------------*/


GraphL::GraphL(void) {

};

/*-------------------------------------------------------------------------------------------------

	Destructor. Calls make empty to deallocate all memory.

-------------------------------------------------------------------------------------------------*/


GraphL::~GraphL(void) {
	makeEmpty();
};

/*-------------------------------------------------------------------------------------------------

	Method takes in a file stream and populates the adjacency lsit with the correct data.
	Sets the description for each Graph Node.

-------------------------------------------------------------------------------------------------*/

void GraphL::buildGraph(ifstream& inFile) {
	int numNodes;
	int headNode = 0;
	int toInsert = 0;

	inFile >> numNodes;
	size = numNodes + 1;

	string nodeName = "";
	getline(inFile, nodeName);

	//inserts nodes with names for each of the head nodes
	for (int index = 1; index < size; index++) {
		NodeData* temp = new NodeData();
		temp->setData(inFile);
		node_array[index].data = temp;
		temp = nullptr;
	}

	//cycles through the nodes and inserts them in to the list
	while (inFile >> headNode >> toInsert) {
		if (headNode == 0) {	//if we reach the end of the data
			break;
		}
		//creates new node and inserts it directly to the
		//Graph Node if there are no other nodes in the list
		if (node_array[headNode].edgeHead == nullptr) {
			EdgeNode* insertNode = new EdgeNode();
			insertNode->adjacentNode = toInsert;
			node_array[headNode].edgeHead = insertNode;
			node_array[headNode].edgeHead->next = nullptr;
		//inserts node betweem the Graph Node and
		//its adjacent node
		} else {
			EdgeNode* insertNode = new EdgeNode();
			insertNode->adjacentNode = toInsert;
			insertNode->next = node_array[headNode].edgeHead;
			node_array[headNode].edgeHead = insertNode;
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
	for (int index = 1; index < size; index++) {	//cycles through each unvisited node
		if (node_array[index].visited == false) {	//in the list
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
		cout << "Node " << row <<"\t" << *node_array[row].data << endl;
		EdgeNode* current = node_array[row].edgeHead;
		while (current != nullptr) {
			cout << "   edge " << row << " " << current->adjacentNode << endl;
			current = current->next;
		}
	}
	cout << endl;
};

/*-------------------------------------------------------------------------------------------------

	Recursive method to calculate the depth first search.

-------------------------------------------------------------------------------------------------*/

void GraphL::dfs(int index) {
	cout << index << " ";
	node_array[index].visited = true;
	EdgeNode* current = node_array[index].edgeHead;

	while (current != nullptr) {
		if (node_array[current->adjacentNode].visited == false) {
			dfs(current->adjacentNode);
		}
		current = current->next;
	}
};

/*-------------------------------------------------------------------------------------------------

	Method deallocate all memory allocated in the nodes in the adjacency list.

-------------------------------------------------------------------------------------------------*/

void GraphL::makeEmpty(void) {
	for (int row = 1; row < size; row++) {
		node_array[row].visited = false;	//sets all nodes visited to false
		delete node_array[row].data;		//deletes the data
		node_array[row].data = nullptr;		//nullptr to data

		//if there is a list for that node we need to deallocate memory
		if (node_array[row].edgeHead != nullptr) {
			EdgeNode* toDelete = node_array[row].edgeHead;	//ptr to head

			//cycles through list in that row deleting all nodes and
			//the data for each node
			while (toDelete != nullptr) {
				//re-links list
				node_array[row].edgeHead = node_array[row].edgeHead->next;
				delete toDelete;
				toDelete = node_array[row].edgeHead;
			}
		}
	}
};
