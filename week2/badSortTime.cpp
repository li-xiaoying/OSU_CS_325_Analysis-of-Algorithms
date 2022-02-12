/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #2
***********************/


#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

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
		float bound = (float)2 / (float)3;
		int m;

		// If alpha<=2/3, use ceil() to calculate m.
		if (alpha <= bound) {
			m = ceil(alpha * (right - left + 1));
		}

		// If alpha>2/3, use round() to calculate m.
		if (alpha > bound) {
			m = round(alpha * (right - left + 1));
		}

		// Recurvisely sort three parts of the array.
		badSort(array, left, left + m - 1, alpha);
		badSort(array, right - m + 1, right, alpha);
		badSort(array, left, left + m - 1, alpha);
	}
}


int main()
{
	srand(time(0));
	int n = 50;
	int* array;
	int choice = 0;
	float alpha = 0;

	// Prompt the value of alpha.
	while (choice != 1 && choice != 2) {
		cout << "Choose the value of alpha: enter 1 to choose 2/3; enter 2 to choose 3/4." << endl;
		cout << "Your choice: ";
		cin >> choice;
		if (choice == 1) {
			alpha = (float)2 / (float)3;
			cout << "Running time for alpha=2/3:" << endl;
		}
		else if (choice == 2) {
			alpha = 0.75;
			cout << "Running time for alpha=3/4:" << endl;
		}
		else {
			cout << "Your choice is invalid. Please choose again." << endl;
		}
	}
	
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
			badSort(array, 0, n - 1, alpha);
			timeEnd = clock();
			float time = (float)timeEnd - (float)timeStart;
			float seconds = time / CLOCKS_PER_SEC;
			total = total + seconds;
		}

		float average = total / 5;
		// Output the array size nand time to the terminal.
		cout << "size: " << n << "  time: " << average << endl;
		// Move to next array size.
		n = n + 50;
		delete[] array;
	}
}