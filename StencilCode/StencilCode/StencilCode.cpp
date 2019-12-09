// StencilCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

int main()
{
	int N = 10;
	//int N = 8192;
	double start, end;
	float** A = new float* [N];
	float** sequentialMatrix = new float* [N];

	for (int i = 0; i < N; i++)
	{
		float* rowA = new float[N];
		float* squentialMatrixRow = new float[N];
		for (int j = 0; j < N; j++)
		{
			if (i != 0 && j != 0)
			{
				rowA[j] = -1;
				squentialMatrixRow[j] = -1;
			}
			else if (i == 0 && j > 0)
			{
				rowA[j] = 250;
				squentialMatrixRow[j] = 250;
			}
			else if (j == 0 && i > 0)
			{
				rowA[j] = 150;
				squentialMatrixRow[j] = 150;
			}
			else {
				rowA[0] = 0;
				squentialMatrixRow[0] = 0;
			}
		}
		A[i] = rowA;
		sequentialMatrix[i] = squentialMatrixRow;
	}

	start = omp_get_wtime();
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			sequentialMatrix[i][j] = (fabs(sin(sequentialMatrix[i - 1][j - 1])) + fabs(sin(sequentialMatrix[i][j - 1])) + fabs(sin(sequentialMatrix[i - 1][j]))) * 100;
		}
	}
	end = omp_get_wtime();

	cout << "Sequential time " << end - start << "\n\n";

	/*for (int i = 1; i < N * 2; i++)
	{
		for (int j = 0; j < i; j++)
		{
			A[i][j] = (fabs(sin(A[i - 1][j - 1])) + fabs(sin(A[i][j - 1])) + fabs(sin(A[i - 1][j]))) * 100;
		}
	}*/

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << sequentialMatrix[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n\n";

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}

	cin;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
