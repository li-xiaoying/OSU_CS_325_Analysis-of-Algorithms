/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #1
***********************/


#include <iostream>
#include <cstdlib>
#include <ctime>

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
	srand(time(0));
	int n = 5000;
	int* array;

	// Collect 10 running time and size n data pairs.
	for (int i = 0; i < 10; i++) {
		array = new int[n];
		float total = 0;

		// Collect 5 running times to take the average 
		// time for each value of size n.
		for (int j = 0; j < 5; j++) {
			// Generate array of size n containing random
			// integer values from 0 to 10,000.
			for (int k = 0; k < n; k++) {
				array[k] = rand() % 10001;
			}

			// Use the system clock to record the running times.
			clock_t timeStart, timeEnd;
			timeStart = clock();
			mergeSort(array, 0, n - 1);
			timeEnd = clock();
			float time = (float)timeEnd - (float)timeStart;
			float seconds = time / CLOCKS_PER_SEC;
			total = total + seconds;
		}

		float average = total / 5;
		// Output the array size nand time to the terminal.
		cout << "size: " << n << "  time: " << average << endl;
		// Move to next array size.
		n = n + 5000;
		delete[] array;
	}
}