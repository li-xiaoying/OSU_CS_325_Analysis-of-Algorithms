/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #5
***********************/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

using namespace std;


// Structure to represent wrestlers (vertices).
struct wrestler {
	string name;
	string type;
	bool visited;
};


int main(int argc, char* argv[])
{
	// Read in data from a file specified in the command line at run time.
	ifstream inputFile(argv[1]);
	int wrestlerNumber;
	// Read in number of wrestlers.
	inputFile >> wrestlerNumber;

	// Read in wrestlers' name.
	string* wrestlerName = new string[wrestlerNumber];
	for (int i = 0; i < wrestlerNumber; i++) {
		inputFile >> wrestlerName[i];
	}

	// Read in number of rivalries.
	int rivalryNumber;
	inputFile >> rivalryNumber;

	// Construct a 2d vector to store wrestlers (vertices), and build a graph using adjacency
	// list. Initialize the first column to be wrestlers (vertices).
	vector<vector<wrestler> > graph(wrestlerNumber, vector<wrestler>(1));
	for (int i = 0; i < wrestlerNumber; i++) {
		graph[i][0].name = wrestlerName[i];
		graph[i][0].type = "unknown";
		graph[i][0].visited = false;
	}

	// Read in rivalries and fill in the adjacency list for every wrestlers (vertices).
	// All wrestlers's type is initialized to "unknown", and bool visited to "false". 
	for (int i = 0; i < rivalryNumber; i++) {
		wrestler rival1;
		wrestler rival2;
		inputFile >> rival1.name;
		inputFile >> rival2.name;
		rival1.type = "unknown";
		rival1.visited = false;
		rival2.type = "unknown";
		rival2.visited = false;

		for (int j = 0; j < wrestlerNumber; j++) {
			if (graph[j][0].name == rival1.name) {
				graph[j].push_back(rival2);
			}
			else if (graph[j][0].name == rival2.name) {
				graph[j].push_back(rival1);
			}
		}
	}

	int unvisitedNumber = wrestlerNumber;
	bool possible = true;

	// If the graphe is not connected, the BFS algorithm need to be performed more than once, 
	// until all connected components are traversed.
	while (unvisitedNumber > 0) {
		// Find the unvisited component, and perforem BFS algorithm on it.
		for (int x = 0; x < wrestlerNumber; x++) {
			// Initialize the first vertice of the component, its type to be "Babyface" and
			// bool visited to be "true".
			if (graph[x][0].visited == false) {
				graph[x][0].type = "Babyface";
				graph[x][0].visited = true;

				// Traverse through the graph and set type and bool visited for all the
				// vertices has same name as the vertex above.
				for (int i = 1; i < wrestlerNumber; i++) {
					for (int j = 0; j < graph[i].size(); j++) {
						if (graph[i][j].name == graph[x][0].name) {
							graph[i][j].type = "Babyface";
							graph[i][j].visited = true;
						}
					}
				}

				// Once a vertex is "visited", lower the number of unvisited vertices by 1.
				unvisitedNumber--;
				// The queue to perform the BFS algorithm.
				queue<string> next;

				// Set type of all adjacent vertices of the first vertex of the component to be "Heel".
				// And push them to the queue next.
				for (int i = 1; i < graph[x].size(); i++) {
					graph[x][i].type = "Heel";
					for (int j = 1; j < wrestlerNumber; j++) {
						for (int k = 0; k < graph[j].size(); k++) {
							if (graph[j][k].name == graph[x][i].name) {
								graph[j][k].type = "Heel";
							}
						}
					}
					next.push(graph[x][i].name);
				}

				// While there are still vertices in the next queue, perform the BFS algorithm.
				while (!next.empty()) {
					for (int i = 1; i < wrestlerNumber; i++) {
						if (next.empty()) {
							break;
						}
						// Find the vertex has the same name as the first element in the next queue.
						// Set its bool visited to "true".
						if (graph[i][0].name == next.front() && graph[i][0].visited == false) {
							graph[i][0].visited = true;
							unvisitedNumber--;
							// For this vertex's adjacent vertices, if their type is "unknown", 
							// then set their type to be different from the original vertex, and
							// push them to the queue next.
							for (int j = 1; j < graph[i].size(); j++) {
								if (graph[i][j].type == "unknown") {
									if (graph[i][0].type == "Babyface") {
										graph[i][j].type = "Heel";
									}
									else if (graph[i][0].type == "Heel") {
										graph[i][j].type = "Babyface";
									}
									for (int k = 1; k < wrestlerNumber; k++) {
										for (int l = 0; l < graph[k].size(); l++) {
											if (graph[k][l].name == graph[i][j].name) {
												graph[k][l].type = graph[i][j].type;
											}
										}
									}
									next.push(graph[i][j].name);
								}
								// If any of the vertex's adjacent vertices has same type as the vertex, 
								// the rivals can not be divided into two types, return impossible.
								else if (graph[i][j].type == graph[i][0].type) {
									possible = false;
									break;
								}
							}
							next.pop();
						}
					}
				}
			}
		}
	}

	// Output result according to the value of "possible".
	if (possible == true) {
		cout << "Yes" << endl;
		cout << "Babyfaces: ";
		for (int i = 0; i < wrestlerNumber; i++) {
			if (graph[i][0].type == "Babyface") {
				cout << graph[i][0].name << " ";
			}
		}
		cout << endl;
		cout << "Heels: ";
		for (int i = 0; i < wrestlerNumber; i++) {
			if (graph[i][0].type == "Heel") {
				cout << graph[i][0].name << " ";
			}
		}
		cout << endl;
	}

	else {
		cout << "No, impossible." << endl;
	}

	delete[] wrestlerName;
	inputFile.close();
	return 0;
}