/*
 * Main.cpp
 *
 *  Created on: May 16, 2017
 *      Author: 293359
 */

//Import everything I need
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

//Structure Vertex: Holds a label (the character label for the vertex that the user sees) and a true ID (the ID that the program uses)
struct Vertex {
	char label;
	int trueID;
};


//Function prototypes
void addVertex(vector<Vertex*>* graph, Vertex* newVertex);
void addEdge(Vertex* firstNode, Vertex* secondNode, int weight, int** adjacencyMatrix);
void removeVertex(vector<Vertex*>* graph, int** adjacencyMatrix);
void removeEdge(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix);
char findNode(vector<Vertex*>* graph, int IDTarget);
int findPath(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix, int* shortestLength);

//Main method, does everything!
int main() {
	//Initialize adjacency matrix as empty (all values -1)
	int** adjacencyMatrix = new int*[20];
	for (int i = 0; i < 20; i++) {
		adjacencyMatrix[i] = new int[20];
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			adjacencyMatrix[i][j] = -1;
		}
	}

	//Initialize vector for holding the Vertices of the graph
	vector<Vertex*> graph;
	vector<Vertex*>* graphPtr;
	graphPtr = &graph;
	bool running = true;
	//While the program is running, prompt the user for what they want to do.
	while (running) {
		char choose;
		//Figure out what the user wants to do via their input, then do it
		cout << "Would you like to \"ADD\" something, \"REMOVE\" something, \"DISPLAY\" the adjacency matrix, \"SEARCH\" for a path between two nodes, or \"QUIT\" the program?" << endl << "?: ";
		cin >> choose;
		cin.ignore(256, '\n');
		if (choose == 'a' || choose == 'A') {
			cout << "Would you like to add a \"VERTEX\" or an \"EDGE\"?" << endl << "?: ";
			cin >> choose;
			cin.ignore(256, '\n');
			if (choose == 'v' || choose == 'V') {
				cout << "Enter in the character label for this vertex." << endl << "Label: ";
				cin >> choose;
				Vertex* temp = new Vertex;
				temp->label = choose;
				addVertex(graphPtr, temp);
			}
			else if (choose == 'e' || choose == 'E') {
				cout << "Enter the label of the starting vertex." << endl << "Label: ";
				char firstChoose;
				cin >> firstChoose;
				Vertex* first = NULL;
				for (int i = 0; i < graphPtr->size(); i++) {
					if (graphPtr->at(i)->label == firstChoose) {
						first = graphPtr->at(i);
					}
				}
				if (first == NULL) {
					cout << "A vertex with that label does not exist. Please try again." << endl;
					continue;
				}
				cout << "Enter the label of the ending vertex." << endl << "Label: ";
				char secondChoose;
				cin >> secondChoose;
				Vertex* second = NULL;
				for (int i = 0; i < graphPtr->size(); i++) {
					if (graphPtr->at(i)->label == secondChoose) {
						second = graphPtr->at(i);
					}
				}
				if (second == NULL) {
					cout << "A vertex with that label does not exist. Please try again." << endl;
					continue;
				}
				cout << "Enter the weight of the edge." << endl << "Weight: ";
				int weight;
				cin >> weight;
				addEdge(first, second, weight, adjacencyMatrix);
			}
			else {
				cout << "That input is invalid. Please try again." << endl;
			}
		}
		else if (choose == 'r' || choose == 'R') {
			cout << "Would you like to remove a \"VERTEX\" or an \"EDGE\"?" << endl << "?: ";
			cin >> choose;
			cin.ignore(256, '\n');
			if (choose == 'v' || choose == 'V') {
				removeVertex(graphPtr, adjacencyMatrix);
			}
			else if (choose == 'e' || choose == 'E') {
				cout << "Enter the label of the starting vertex." << endl << "Label: ";
				char firstChoose;
				cin >> firstChoose;
				Vertex* first = NULL;
				for (int i = 0; i < graphPtr->size(); i++) {
					if (graphPtr->at(i)->label == firstChoose) {
						first = graphPtr->at(i);
					}
				}
				if (first == NULL) {
					cout << "A vertex with that label does not exist. Please try again." << endl;
					continue;
				}
				cout << "Enter the label of the ending vertex." << endl << "Label: ";
				char secondChoose;
				cin >> secondChoose;
				Vertex* second = NULL;
				for (int i = 0; i < graphPtr->size(); i++) {
					if (graphPtr->at(i)->label == secondChoose) {
						second = graphPtr->at(i);
					}
				}
				if (second == NULL) {
					cout << "A vertex with that label does not exist. Please try again." << endl;
					continue;
				}
				removeEdge(first, second, adjacencyMatrix);
			}
			else {
				cout << "That input is invalid. Please try again." << endl;
			}
		}
		else if (choose == 'd' || choose == 'D') {
			cout << "Here is the adjacency matrix:" << endl;
			cout << " \t";
			for (int i = 0; i < 20; i++) {
				cout << findNode(graphPtr, i) << '\t';
			}
			cout << endl;
			for (int i = 0; i < 20; i++) {
				cout << findNode(graphPtr, i) << '\t';
					for (int j = 0; j < 20; j++) {
						cout << adjacencyMatrix[i][j] << '\t';
					}
					cout << endl;
				}
		}
		else if (choose == 's' || choose == 'S') {
			cout << "Enter the label of the starting vertex." << endl << "Label: ";
			char firstChoose;
			cin >> firstChoose;
			Vertex* first = NULL;
			for (int i = 0; i < graphPtr->size(); i++) {
				if (graphPtr->at(i)->label == firstChoose) {
					first = graphPtr->at(i);
				}
			}
			if (first == NULL) {
				cout << "A vertex with that label does not exist. Please try again." << endl;
				continue;
			}
			cout << "Enter the label of the ending vertex." << endl << "Label: ";
			char secondChoose;
			cin >> secondChoose;
			Vertex* second = NULL;
			for (int i = 0; i < graphPtr->size(); i++) {
				if (graphPtr->at(i)->label == secondChoose) {
					second = graphPtr->at(i);
				}
			}
			if (second == NULL) {
				cout << "A vertex with that label does not exist. Please try again." << endl;
				continue;
			}
			int* shortestLength = new int[20];
			for (int i = 0; i < 20; i++) {
				shortestLength[i] = -1;
			}
			shortestLength[first->trueID] = 0;
			int length = findPath(first, second, adjacencyMatrix, shortestLength);
			if (length > -1) {
				cout << "The shortest path between vertex " << firstChoose << " and vertex " << secondChoose << " is " << length << "." << endl;
			}
			else {
				cout << "There is no path between vertex " << firstChoose << " and vertex " << secondChoose << "." << endl;
			}
		}
		else if (choose == 'q' || choose == 'Q') {
			cout << "Thanks for using this program!" << endl;
			running = false;
		}
		else {
			cout << "That input is invalid. Please try again." << endl;
		}
	}

	return 0;
}
//Add a vertex to the graph.
void addVertex(vector<Vertex*>* graph, Vertex* newVertex) {
	bool whatExists[20];
	for (int i = 0; i < 20; i++) {
		whatExists[i] = false;
	}
	bool labelAlreadyUsed = false;
	for (int i = 0; i < graph->size(); i++) {
		whatExists[graph->at(i)->trueID] = true;
		if (graph->at(i)->label == newVertex->label) {
			labelAlreadyUsed = true;
		}
	}
	//Check whether the label that the user assigned to the Vertex has already been used
	if (labelAlreadyUsed) {
		cout << "A vertex with that label already exists in the graph! Please try again." << endl;
		return;
	}
	//Check if the adjacency matrix isn't already full
	for (int i = 0; i < 20; ++i) {
		if (whatExists[i] == false) {
			graph->push_back(newVertex);
			newVertex->trueID = i;
			cout << "The vertex with label " << newVertex->label << " was successfully added." << endl;
			return;
		}
	}
	cout << "Fatal: Graph is already full! (Limit: 20 vertices)" << endl;
}
//Adds an edge to the graph between two existing Vertices
void addEdge(Vertex* firstNode, Vertex* secondNode, int weight, int** adjacencyMatrix) {
	int firstIndex = firstNode->trueID;
	int secondIndex = secondNode->trueID;
	//Set the weight to the proper position in the adjacency matrix
	adjacencyMatrix[firstIndex][secondIndex] = weight;
	cout << "Edge successfully added from vertex " << firstNode->label << " to vertex " << secondNode->label << "." << endl;
}
//Remove a vertex
void removeVertex(vector<Vertex*>* graph, int** adjacencyMatrix) {
	cout << "Enter the label of the vertex to be removed." << endl << "Label: ";
	char choose;
	cin >> choose;
	//Find which Vertex they are targeting, if it exists
	Vertex* target = NULL;
	int targetIndex = 0;
	for (int i = 0; i < graph->size(); i++) {
		if (graph->at(i)->label == choose) {
			target = graph->at(i);
			targetIndex = i;
		}
	}
	if (target == NULL) {
		cout << "A vertex with that label does not exist. Please try again." << endl;
		return;
	}
	//Reset all values that involve the target Vertex within the adjacency matrix
	int index = target->trueID;
	for (int i = 0; i < 20; i++) {
		adjacencyMatrix[i][index] = -1;
		adjacencyMatrix[index][i] = -1;
	}
	cout << "The vertex with label " << target->label << " was removed." << endl;
	graph->erase(graph->begin() + targetIndex);
	delete target;
}
//Removes an edge from the graph
void removeEdge(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix) {
	int firstIndex = firstNode->trueID;
	int secondIndex = secondNode->trueID;
	//Reset the value for that edge in the adjacency matrix
	adjacencyMatrix[firstIndex][secondIndex] = -1;
	cout << "Edge successfully removed from vertex " << firstNode->label << " to vertex " << secondNode->label << "." << endl;
}
//Find the character label of the Vertex with the given ID
char findNode(vector<Vertex*>* graph, int IDTarget) {
	for (int i = 0; i < graph->size(); i++) {
		if (graph->at(i)->trueID == IDTarget) {
			return graph->at(i)->label;
		}
	}
	return ' ';
}
//Find the shortest path length between two nodes, if there is one
int findPath(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix, int* shortestLength) {
	bool foundNew = true;
	//While the previous iteration lead to a new shorter path being found between the first node and ANY other node...
	while (foundNew) {
		foundNew = false;
		for (int i = 0; i < 20; i++) {
			//For each node where the length from first node to that node is existant (i.e. > -1), check paths from that node to other nodes and update lengths
			if (shortestLength[i] > -1) {
				for (int j = 0; j < 20; j++) {
					//For each path from that node to other nodes...
					if (adjacencyMatrix[i][j] > -1) {
						int testPath = shortestLength[i] + adjacencyMatrix[i][j];
						//If the new path formed is shorter than the current value of path from first node to that node, set it as the shortest path from first node to that node
						if (shortestLength[j] == -1 || testPath < shortestLength[j]) {
							shortestLength[j] = testPath;
							//Since we found something new, foundNew is true!
							foundNew = true;
						}
					}
				}
			}
		}
	}
	//Return the shortest path value calculated between first node and second node
	return shortestLength[secondNode->trueID];
}
