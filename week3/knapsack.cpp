/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #3
***********************/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/******************************************************************************
** Function of implement of the 0-1 Knapsack Algorithm.
******************************************************************************/
int knapsack(int W, int weight[], int value[], int n)
{
	int i, w;
	// Allocate an matrix to store the value of every subproblem.
	int** V = new int* [n + 1];
	for (int j = 0; j < n + 1; j++) {
		V[j] = new int[W + 1];
	}

	// Compute every subproblem and fill the matrix.
	for (i = 0; i <= n; i++) {
		for (w = 0; w <= W; w++) {

			// Set values of first row and first column to 0.
			if (i == 0 || w == 0) {
				V[i][w] = 0;
			}

			// If this item's weight is no more than the capacity, then this 
			// item can be in the solution, and we choose the case with 
			// greater value.
			else if (weight[i - 1] <= w) {
				if (value[i - 1] + V[i - 1][w - weight[i - 1]] > V[i - 1][w]) {
					V[i][w] = value[i - 1] + V[i - 1][w - weight[i - 1]];
				}
				else {
					V[i][w] = V[i - 1][w];
				}
			}

			// Else the item's weight is greater than the capacity, it can not 
			// be in the solution. So we select the ¡°optimal¡± using items 
			// before it.
			else {
				V[i][w] = V[i - 1][w];
			}
		}
	}

	// Store the optimal value to be return.
	int optimalValue = V[n][W];

	for (int k = 0; k < n + 1; k++) {
		delete[] V[k];
	}
	delete[] V;
	
	return optimalValue;
}


int main()
{
	// Read inputs from file data.txt.
	ifstream inputFile("data.txt");
	string line;
	int n = 0;

	// Get the number of lines in data.txt, which is the number of items.
	while (getline(inputFile, line)) {
		n++;
	}

	// Go back to the beginning of data.txt.
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Allocate two arrays to store the weights and values of items.
	int* weight;
	int* value;
	weight = new int[n];
	value = new int[n];

	// Read input from data.txt, which has two columns. The first column is
	// the weights of items. The second column is the values of items.
	for (int i = 0; i < n * 2; i++) {
		if (i % 2 == 0) {
			inputFile >> weight[i / 2];
		}
		if (i % 2 == 1) {
			inputFile >> value[(i - 1) / 2];
		}
	}

	// Prompt capacity of the knapsack and output the optimal value of the 
	// knapsack problem.
	int W;
	cout << "Enter the capacity W of the knapsack: ";
	cin >> W;
	cout << "Optimal value: " << knapsack(W, weight, value, n) << endl;

	delete[] weight;
	delete[] value;
	inputFile.close();
	return 0;
}