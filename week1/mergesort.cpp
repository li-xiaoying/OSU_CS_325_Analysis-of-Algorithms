/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #1
***********************/


#include <iostream>
#include <fstream>

using namespace std;


/***************************************************************
** Function to merge two subarrays of array[]. One subarray is 
** array[left-mid], the other subarray is array[mid+1-right].
***************************************************************/
void merge(int array[], int left, int mid, int right)
{
	int i, j, k;
	// Allocate two temp arrays.
	int* arrayLeft;
	int* arrayRight;
	int sizeLeft = mid - left + 1;
	int sizeRight = right - mid;
	arrayLeft = new int[sizeLeft];
	arrayRight = new int[sizeRight];

	// Copy elements from subarrays to temp arrays.
	for (i = 0; i < sizeLeft; i++) {
		arrayLeft[i] = array[left + i];
	}

	for (j = 0; j < sizeRight; j++) {
		arrayRight[j] = array[mid + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	// Merge elements from temp arrays to array[].
	while (i < sizeLeft && j < sizeRight) {
		if (arrayLeft[i] <= arrayRight[j]) {
			array[k] = arrayLeft[i];
			i++;
		}

		else {
			array[k] = arrayRight[j];
			j++;
		}

		k++;
	}

	// Copy the remaining elements in temp arrays to array[].
	while (i < sizeLeft) {
		array[k] = arrayLeft[i];
		i++;
		k++;
	}

	while (j < sizeRight) {
		array[k] = arrayRight[j];
		j++;
		k++;
	}

	delete[] arrayLeft;
	delete[] arrayRight;
}


/***************************************************************
** Function to sort an array of integers using merge sort.
***************************************************************/
void mergeSort(int array[], int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		// Implement merge sort recursively.
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);
		// Merge two subarrays.
		merge(array, left, mid, right);
	}
}


int main()
{
	// Read inputs from file data.txt.
	ifstream readFile("data.txt");
	ofstream outputFile("merge.out");

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

		// Sort the array using merge sort.
		mergeSort(array, 0, numberOfInteger-1);

		// Write the output to file merge.out.
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