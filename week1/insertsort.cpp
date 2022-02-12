/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #1
***********************/


#include <iostream>
#include <fstream>

using namespace std;


/***************************************************************
** Function to sort an array of integers using insertion sort.
***************************************************************/
void insertionSort(int array[], int n)
{
	int current;
	int index;

	for (int i = 1; i < n; i++) {
		current = array[i];
		index = i - 1;

		// Move all elements that are greater than array[i]
		// in array[0] to array[i-1] one position ahead.
		while (index >= 0 && array[index] > current) {
			array[index + 1] = array[index];
			index = index - 1;
		}

		array[index + 1] = current;
	}
}


int main()
{
	// Read inputs from file data.txt.
	ifstream readFile("data.txt");
	ofstream outputFile("insert.out");

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

		// Sort the array using insertion sort.
		insertionSort(array, numberOfInteger);

		// Write the output to file insert.out.
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