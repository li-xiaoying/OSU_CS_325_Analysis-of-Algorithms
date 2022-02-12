/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #2
***********************/


#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;


/***************************************************************
** Function to sort an array of integers using bad sort.
***************************************************************/
void badSort(int array[], int left, int right, float alpha)
{
	// If the array only has 2 elements and the first element 
	// is greater than the second element, swap them.
	if (right - left + 1 == 2 && array[left] > array[right]) {
		int temp = array[left];
		array[left] = array[right];
		array[right] = temp;
	}

	// If the array has more than 2 elements.
	else if (right - left + 1 > 2) {
		int m = ceil(alpha * (right - left + 1));
		// Recurvisely sort three parts of the array.
		badSort(array, left, left + m - 1, alpha);
		badSort(array, right - m + 1, right, alpha);
		badSort(array, left, left + m - 1, alpha);
	}
}


int main()
{
	// Prompt the value of alpha.
	float alpha;
	cout << "Enter the value of alpha (1/2 < alpha <= 2/3): ";
	cin >> alpha;

	// Read inputs from file data.txt.
	ifstream readFile("data.txt");
	ofstream outputFile("bad.out");

	while (!readFile.eof()) {
		int numberOfInteger;
		int* array;
		// Read in the first value of each line, which is
		// the number of integers that need to be sorted.
		readFile >> numberOfInteger;
		array = new int[numberOfInteger];
		int integer;

		// Read in the following integers and fill the array.
		for (int i = 0; i < numberOfInteger; i++) {
			readFile >> integer;
			array[i] = integer;
		}

		// Sort the array using bad sort.
		badSort(array, 0, numberOfInteger - 1, alpha);

		// Write the output to file bad.out.
		for (int i = 0; i < numberOfInteger; i++) {
			outputFile << array[i] << " ";
		}

		outputFile << endl;
		delete[] array;
	}

	readFile.close();
	outputFile.close();

	return 0;
}