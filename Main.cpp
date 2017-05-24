/*
 * Main.cpp
 *
 *  Created on: May 16, 2017
 *      Author: 293359
 */

//#include "Vertex.h"
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct Vertex {
	char label;
	int trueID;
};

void addVertex(vector<Vertex*>* graph, Vertex* newVertex);
void addEdge(Vertex* firstNode, Vertex* secondNode, int weight, int** adjacencyMatrix);
void removeVertex(vector<Vertex*>* graph, int** adjacencyMatrix);
void removeEdge(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix);
char findNode(vector<Vertex*>* graph, int IDTarget);
int findPath(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix, int* shortestLength);


int main() {
	int** adjacencyMatrix = new int*[20];
	for (int i = 0; i < 20; i++) {
		adjacencyMatrix[i] = new int[20];
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			adjacencyMatrix[i][j] = -1;
		}
	}
	vector<Vertex*> graph;
	vector<Vertex*>* graphPtr;
	graphPtr = &graph;
	bool running = true;
	while (running) {
		char choose;
		for (int i = 0; i < graphPtr->size(); i++) {
			cout << graphPtr->at(i)->label << " " << graphPtr->at(i)->trueID << endl;
		}
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

void addVertex(vector<Vertex*>* graph, Vertex* newVertex) {
	cout << newVertex->label << endl;
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
	if (labelAlreadyUsed) {
		cout << "A vertex with that label already exists in the graph! Please try again." << endl;
		return;
	}
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

void addEdge(Vertex* firstNode, Vertex* secondNode, int weight, int** adjacencyMatrix) {
	int firstIndex = firstNode->trueID;
	int secondIndex = secondNode->trueID;
	adjacencyMatrix[firstIndex][secondIndex] = weight;
	cout << "Edge successfully added from vertex " << firstNode->label << " to vertex " << secondNode->label << "." << endl;
}
void removeVertex(vector<Vertex*>* graph, int** adjacencyMatrix) {
	cout << "Enter the label of the vertex to be removed." << endl << "Label: ";
	char choose;
	cin >> choose;
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
	int index = target->trueID;
	for (int i = 0; i < 20; i++) {
		adjacencyMatrix[i][index] = -1;
		adjacencyMatrix[index][i] = -1;
	}
	cout << "The vertex with label " << target->label << " was removed." << endl;
	graph->erase(graph->begin() + targetIndex);
	delete target;
}

void removeEdge(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix) {
	int firstIndex = firstNode->trueID;
	int secondIndex = secondNode->trueID;
	adjacencyMatrix[firstIndex][secondIndex] = -1;
	cout << "Edge successfully removed from vertex " << firstNode->label << " to vertex " << secondNode->label << "." << endl;
}

char findNode(vector<Vertex*>* graph, int IDTarget) {
	for (int i = 0; i < graph->size(); i++) {
		if (graph->at(i)->trueID == IDTarget) {
			return graph->at(i)->label;
		}
	}
	return ' ';
}

int findPath(Vertex* firstNode, Vertex* secondNode, int** adjacencyMatrix, int* shortestLength) {
	bool foundNew = true;
	while (foundNew) {
		foundNew = false;
		for (int i = 0; i < 20; i++) {
			if (shortestLength[i] > -1) {
				for (int j = 0; j < 20; j++) {
					if (adjacencyMatrix[i][j] > -1) {
						int testPath = shortestLength[i] + adjacencyMatrix[i][j];
						if (shortestLength[j] == -1 || testPath < shortestLength[j]) {
							shortestLength[j] = testPath;
							foundNew = true;
						}
					}
				}
			}
		}
	}
	return shortestLength[secondNode->trueID];
}
