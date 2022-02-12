/***********************
** Xiaoying Li
** CS 325 Winter 2020
** Homework #8
***********************/


#include <iostream>
#include <fstream>

using namespace std;


/******************************************************************************
** Function to sort an array of integers in decreasing order using insertion 
** sort.
******************************************************************************/
void insertionSort(int array[], int n)
{
	int current;
	int index;

	for (int i = 1; i < n; i++) {
		current = array[i];
		index = i - 1;

		// Move all elements that are greater than array[i]
		// in array[0] to array[i-1] one position ahead.
		while (index >= 0 && array[index] < current) {
			array[index + 1] = array[index];
			index = index - 1;
		}

		array[index + 1] = current;
	}
}


/******************************************************************************
** Function of bin packing problem using First-Fit algorithm, which put each 
** item as you come to it into the first bin which it fits. If there is no 
** available bin then open a new bin.
******************************************************************************/
int firstFit(int weight[], int number, int capacity) {
	// Initialize bin's number to 0.
	int binNumber = 0;
	// Allocate an array to store the left room in bins, 
	// whose size is the number of items.
	int* binRoom;
	binRoom = new int[number];

	// Pack items one by one.
	for (int i = 0; i < number; i++) {
		int j;
		// Put each item into the first bin which it fits.
		for (j = 0; j < binNumber; j++) {
			// If such a bin is found, update this bin's left room and move to
			// the next item.
			if (binRoom[j] >= weight[i]) { 
				binRoom[j] = binRoom[j] - weight[i];
				break;
			}
		}

		// If there is no available bin then open a new bin, set its left room, 
		// and update bins' number, then move to the next item.
		if (j == binNumber) {
			binRoom[binNumber] = capacity - weight[i];
			binNumber++;
		}
	}

	delete[] binRoom;
	// After all items are packed into bins, return the number of bins.
	return binNumber;
}


/******************************************************************************
** Function of bin packing problem using Best-Fit algorithm, which place the
** items in the order in which they arrive. Place the next item into the bin
** which will leave the least room left over after the item is placed in the 
** bin. If it does not fit in any bin, start a new bin.
******************************************************************************/
int bestFit(int weight[], int number, int capacity) {
	// Initialize bin's number to 0.
	int binNumber = 0;
	// Allocate an array to store the left room in bins, 
	// whose size is the number of items.
	int* binRoom;
	binRoom = new int[number];

	// Pack items one by one.
	for (int i = 0; i < number; i++) {
		int j;
		// Initialize the least left room to bin's capacity plus 1,
		// and the index of bin with the least left room to 0;
		int least = capacity + 1;
		int index = 0;

		// Place the item into the bin which will leave the least room left
		// over after the item is placed in the bin.
		for (j = 0; j < binNumber; j++) {
			// Compare every bin's left room after the item is placed in the
			// bin if the item fits the bin to find the bin which will leave
			// the least room left over after the item is placed in the bin.
			if (binRoom[j] >= weight[i] && binRoom[j] - weight[i] < least) {
				// Update the least left room and the index of the bin with the
				// least left room.
				index = j;
				least = binRoom[j] - weight[i];
			}
		}

		// If the item does not fit in any bin, start a new bin, set its left
		// room, and update bins' number, then move to the next item.
		if (least == capacity + 1) {
			binRoom[binNumber] = capacity - weight[i];
			binNumber++;
		}

		// If such a bin is found, update this bin's left room and move to the
		// next item.
		else {
			binRoom[index] -= weight[i];
		}
	}

	delete[] binRoom;
	// After all items are packed into bins, return the number of bins.
	return binNumber;
}


int main()
{
	// Read in a text file named bin.txt with multiple test cases.
	ifstream inputFile("bin.txt");
	// Read in the number of test cases.
	int caseNumber;
	inputFile >> caseNumber;

	// For every test case, read in the capacity of bins for that test case,
	// the number of items and the weight of each item.
	for (int i = 0; i < caseNumber; i++) {
		int capacity;
		int itemNumber;
		inputFile >> capacity;
		inputFile >> itemNumber;
		int* weight;
		weight = new int[itemNumber];

		for (int j = 0; j < itemNumber; j++) {
			inputFile >> weight[j];
		}

		// Implement First-Fit, Best-Fit and First-Fit Decreasing algorithms on every 
		// test case.
		int firstFitResult;
		int firstFitDecreasingResult;
		int bestFitResult;
		firstFitResult = firstFit(weight, itemNumber, capacity);
		bestFitResult = bestFit(weight, itemNumber, capacity);
		// For First-Fit-Decreasing algorithm, first sort the items in decreasing
		// order by size, then use First-Fit on the resulting list.
		insertionSort(weight, itemNumber);
		firstFitDecreasingResult = firstFit(weight, itemNumber, capacity);
		// Output to the terminal the number of bins each algorithm calculated for
		// each test case.
		cout << "Test Case " << i + 1 << ": First Fit - " << firstFitResult
			 << "; First Fit Decreasing - " << firstFitDecreasingResult
			 << "; Best Fit - " << bestFitResult << endl;
		delete[] weight;
	}

	inputFile.close();
	return 0;
}