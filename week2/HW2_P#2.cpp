#include<iostream>
using namespace std;


void maximumSubarray(int A1[], int sizeA1, int A2[]) {
	int maxSumA1 = 0;
	int tempSumA1 = 0;
	int rightA1 = 0;

	// Using Kadane¡¯s Algorithm to find the max sum of contiguous subarray of A1.
	for (int i = 0; i < sizeA1; i++) {
		tempSumA1 = tempSumA1 + A1[i];
		if (maxSumA1 < tempSumA1) {
			maxSumA1 = tempSumA1;
			rightA1 = i;
		}
		if (tempSumA1 < 0) {
			tempSumA1 = 0;
		}
	}

	// Using the max sum and the right index of the contiguous subarray to
	// calculate the left index of the subarray.
	int temp = maxSumA1;
	int leftA1 = rightA1;

	while (temp != 0) {
		temp = temp - A1[leftA1];
		leftA1--;
	}

	leftA1++;

	// Print the result.
	cout << "The maximum subarray of A1 is [" << leftA1 << ", " << rightA1 << "]."
		 << endl;
	cout << "The maximun contiguous sum is " << maxSumA1 << "." << endl;

	int currentSumA2 = 0;
	int maxSumA2 = 0;
	int sizeA2 = sizeA1 + 1;
	int rightA2 = sizeA2-1;
	int leftA2 = sizeA2-1;

	// Calculate the sum of elements of A2 from the right end and find the max sum.
	for (int i = 1; i <= sizeA2; i++) {
		currentSumA2 = currentSumA2 + A2[sizeA2-i];
		if (currentSumA2 > maxSumA2) {
			maxSumA2 = currentSumA2;
			leftA2 = sizeA2 - i;
		}
	}

	// Compare the max sum of A2 with the maximum sum of A1.
	// If the max sum of A2 is greater than the max sum of A1, 
	// then the max sum of contiguous subarray of A2 is the max sum of A2.
	if (maxSumA1 < maxSumA2) {
		cout << "The maximum subarray of A2 is [" << leftA2 << ", " << rightA2 
			 << "]." << endl;
		cout << "The maximun contiguous sum is " << maxSumA2 << "." << endl;
	}

	// Else, the max sum of contiguous subarray of A2 is the maximum sum of A1.
	else {
		cout << "The maximum subarray of A2 is [" << leftA1 << ", " << rightA1 
			 << "]." << endl;
		cout << "The maximun contiguous sum is " << maxSumA1 << "." << endl;
	}
}


int main()
{
	int a1[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	int a2[] = { -2, -3, 4, -1, -2, 1, 5, -3 ,10 };
	int size = sizeof(a1) / sizeof(a1[0]);
	maximumSubarray(a1, size, a2);
	return 0;
}