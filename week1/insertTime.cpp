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
			insertionSort(array, n);
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