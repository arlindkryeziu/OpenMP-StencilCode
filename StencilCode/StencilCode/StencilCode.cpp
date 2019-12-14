// StencilCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <math.h>

using namespace std;

void printElements(int argc, char** argv, float** matrix, int N);

int main(int argc, char** argv)
{
	int N = 8192;
	int threadNumber = 10;
	int threadsRatio = 1000; //edge true => (i / threadsRatio) + 1; edge false => ((N + N - i) / threadsRatio) + 1;

	double start;
	double end;

	float** S = new float* [N]; //sequential
	float** A = new float* [N]; //parallel

	for (size_t i = 0; i < N; i++)
	{
		A[i] = new float[N];
		S[i] = new float[N];
		for (size_t j = 0; j < N; j++)
		{
			A[0][j] = 250;
			A[i][0] = 150;

			S[0][j] = 250;
			S[i][0] = 150;
		}
	}

	A[0][0] = 0;
	S[0][0] = 0;

	start = omp_get_wtime();
	for (int i = 2; i < N + N; i++)
	{
		if (i < N)
		{
			//#pragma omp parallel for num_threads((i / threadsRatio) + 1)
#pragma omp parallel for num_threads(threadNumber)
			for (int j = 1; j < i; j++)
			{
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1])) + fabs(sin(A[i - j][j - 1])) + fabs(sin(A[i - j - 1][j]))) * 100;
			}
		}
		else {
			//#pragma omp parallel for num_threads(((N + N - i) / threadsRatio) + 1)
#pragma omp parallel for num_threads(threadNumber)
			for (int j = N - 1; j >= i - N + 1; j--)
			{
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1])) + fabs(sin(A[i - j][j - 1])) + fabs(sin(A[i - j - 1][j]))) * 100;
			}
		}
	}
	end = omp_get_wtime();
	cout << "Parallel time: " << end - start;
	printElements(argc, argv, A, N);

	start = omp_get_wtime();
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			S[i][j] = (fabs(sin(S[i - 1][j - 1])) + fabs(sin(S[i][j - 1])) + fabs(sin(S[i - 1][j]))) * 100;
		}
	}
	end = omp_get_wtime();
	cout << "Sequential time: " << end - start;
	printElements(argc, argv, S, N);

	cin;
}

void printElements(int argc, char** argv, float** matrix, int N)
{
	if (argc % 2 == 1) {
		for (int i = 1; i < argc; i = i + 2)
		{
			int firstIndex = atoi(argv[i]);
			int secondIndex = atoi(argv[i + 1]);

			if (firstIndex < N && secondIndex < N)
				cout << "\nA[" << firstIndex << "][" << secondIndex << "]: " << matrix[firstIndex][secondIndex];
		}
	}
	else
		cout << "Arguments number should be even!";
	cout << "\n\n";
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
