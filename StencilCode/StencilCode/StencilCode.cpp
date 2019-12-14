// StencilCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

int main()
{
	int N = 8192;
	int threadsRatio = 50;

	bool edge = true;

	double start;
	double end;

	float** S = new float* [N]; //sequential
	float** A = new float* [N]; //parallel

	for (size_t i = 0; i < N; i++)
	{
		float* rowS = new float[N];
		float* rowA = new float[N];
		for (size_t j = 0; j < N; j++)
		{
			if (i != 0 && j != 0)
			{
				rowS[j] = -1;
				rowA[j] = -1;
			}
			else if (i == 0 && j > 0)
			{
				rowS[j] = 250;
				rowA[j] = 250;
			}
			else if (j == 0 && i > 0)
			{
				rowS[j] = 150;
				rowA[j] = 150;
			}
			else {
				rowS[0] = 0;
				rowA[0] = 0;
			}
		}
		S[i] = rowS;
		A[i] = rowA;
	}

	start = omp_get_wtime();
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			S[i][j] = (fabs(sin(S[i - 1][j - 1])) + fabs(sin(S[i][j - 1])) + fabs(sin(S[i - 1][j]))) * 100;
		}
	}
	end = omp_get_wtime();
	cout << "Sequential time " << end - start << "\n\n";

	start = omp_get_wtime();
	for (int i = 2; i < N + N; i++)
	{
		if (edge)
		{
#pragma omp parallel for num_threads(4)
			for (int j = 1; j < i; j++)
			{
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1])) + fabs(sin(A[i - j][j - 1])) + fabs(sin(A[i - j - 1][j]))) * 100;
			}

			if (i >= N)
			{
				edge = false;
			}
		}
		else {
#pragma omp parallel for num_threads(4)
			for (int j = 9; j >= i - N + 1; j--)
			{
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1])) + fabs(sin(A[i - j][j - 1])) + fabs(sin(A[i - j - 1][j]))) * 100;
			}
		}
	}
	end = omp_get_wtime();
	cout << "Parallel time " << end - start << "\n\n";

	/*for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << S[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n\n";

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}*/

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
