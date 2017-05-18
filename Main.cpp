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

void addVertex(vector<Vertex*> graph, int adjacencyMatrix[20][20], Vertex* newVertex);
void addEdge(Vertex* firstNode, Vertex* secondNode, int adjacencyMatrix[20][20]);
void removeVertex(vector<Vertex*> graph, int adjacencyMatrix[20][20]);
void removeEdge(Vertex* firstNode, Vertex* secondNode, int adjacencyMatrix[20][20]);


int main() {
	int adjacencyMatrix[20][20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			adjacencyMatrix[i][j] = -1;
		}
	}
	vector<Vertex*> graph;
	bool running = true;
	while (running) {
		char choose;
		cout << "Would you like to \"ADD\" something, \"REMOVE\" something, or \"QUIT\" the program?" << endl << "?: ";
		cin >> choose;
		cin.ignore(256, '\n');
		if (choose == 'a' || choose == 'A') {
			cout << "Would you like to add a \"VERTEX\" or an \"EDGE\"?" << endl << "?: ";
			cin >> choose;
			cin.ignore(256, '\n');
			if (choose == 'v' || choose == 'V') {
				//TODO Add vertex
			}
			else if (choose == 'e' || choose == 'E') {
				//TODO Add edge
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
				//TODO Remove vertex
			}
			else if (choose == 'e' || choose == 'E') {
				//TODO Remove edge
			}
			else {
				cout << "That input is invalid. Please try again." << endl;
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
