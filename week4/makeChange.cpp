/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #4
***********************/


#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;


/**********************************************************
** Function of implement of the greedy algorithm to make 
** change for n cents using the fewest number of coins.
** Suppose the available coins are in the denominations 
** that are powers of c, and the exponents are from 0 to k.
**********************************************************/
vector<int> makeChange(int c, int k, int n) {
	vector<int> solution;

	// Loop until all cents have been changed.
	while (n > 0) {
		// Denominations are powers of c, and pick the
		// largest denomination first.
		int denomination = pow(c, k);

		// If the value of left cents is no less than this
		// denomination, use this denomination to make change.
		if (n >= denomination) {
			// Add this denomination to the solution.
			solution.push_back(denomination);
			// Calculate the number of this denomination,
			// and add it to the solution.
			int cardinality = n / denomination;
			solution.push_back(cardinality);
			// Calculate the value of left cents.
			n = n - cardinality * denomination;
		}

		// Move to the next denomination.
		k--;
	}

	return solution;
}


int main()
{
	// Read inputs from file data.txt.
	ifstream inputFile("data.txt");
	ofstream outputFile("change.txt");
	string line;
	int lineNumber = 0;

	// Get the number of lines in data.txt.
	while (getline(inputFile, line)) {
		lineNumber++;
	}

	// Go back to the beginning of data.txt.
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Read input from data.txt.
	// Loop all input lines.
	for (int i = 0; i < lineNumber; i++) {
		int C;
		int K;
		int N;

		// Read values of c, k, n in specified order.
		for (int j = 0; j < 3; j++) {
			if (j == 0) {
				inputFile >> C;
			}
			else if (j == 1) {
				inputFile >> K;
			}
			else {
				inputFile >> N;
			}
		}

		// Use the greedy algorithm to make change.
		vector<int> optimalSolution = makeChange(C, K, N);
		int size = optimalSolution.size();

		// Write the output to change.txt.
		for (int l = 0; l < size; l++) {
			if (l % 2 == 0) {
				outputFile << optimalSolution[l] << "  ";
			}
			else {
				outputFile << optimalSolution[l] << endl;
			}
		}

		// Write a delimiter line to separate the outputs
		// generated for different inputlines.
		if (lineNumber - i > 1) {
			outputFile << "----------" << endl;
		}
	}

	inputFile.close();
	outputFile.close();
	return 0;
}