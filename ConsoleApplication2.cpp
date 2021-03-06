// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread> 
#include <ctime> 


 int N;

using namespace std;

double numerator(double f1, double f2, double At[2][2]) {
	double f[2] = { f1, f2 };

	///At * f = D
	double D[2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			D[i] = 0;
			for (int k = 0; k < 2; k++)
				D[i] += (At[i][k] * f[k]);
		}
	///(At*f)^2///
	double result = 0;
	for (int i = 0; i < 2; i++)
		result += D[i]*D[i];
	return result;
}

double denominator(double A[2][2], double At[2][2], double f1, double f2) {
	///A*At///
	double C[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < 2; k++)
				C[i][j] += (A[i][k] * At[k][j]);
		}
	///(A*At)*f///
	double E[2];
	double f[2] = { f1, f2 };
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			E[i] = 0;
			for (int k = 0; k < 2; k++)
				E[i] += (C[i][k] * f[k]);
		}
	///((A*At)*f)^2///
	double result = 0;
	for (int i = 0; i < 2; i++)
		result += E[i] * E[i];
	return result;

}

void transpose(double matrix[2][2])
{
	double t;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = i; j < 2; ++j)
		{
			t = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = t;
		}
	}
}

double derivativex(double x, double y) {
	return 40 * x - 20 * y + 20;
}
	
double derivativey(double x, double y) {
	return -20 * x + 20 * y - 40;
}

int main()
{
	double x, y, lambda;
	//cout << "Enter approximation x, y: " << endl;
	x = 2;//cin >> x;
	y = 2;//cin >> y;
	lambda = 1;
	//cout << "First approximation for x = " << x << " y = " << y << endl;

	///f0///
	double f1 = 2 * x + y - 5;
	double f2 = 4 * x - 3 * y + 5;
	double f[2] = { f1, f2 };

	cout << "Vector f(x0, y0): " << endl;
	cout << " \t ";
	for (int i = 0; i < 2; i++)
		cout << f[i] << "  ";
	cout << " \n ";

	///МАТРИЦА A///
	double A[2][2] = { {2,1},
					   {4,3} };
	
	//cout << "Enter Matrix A:" << endl;
	/*double A[2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			cin >> A[i][j];*/

	cout << "Matrix A: " << endl;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
			cout << setw(4) << A[i][j];
		cout << '\n';
	}

	///ТРАНСПОНИРОВАННАЯ МАТРИЦА A///
	double At[2][2];
	memcpy(At, A, sizeof(At));
	transpose(At);
	cout << "Transpose matrix: " << endl;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
			cout << setw(4) << At[i][j];
		cout << '\n';
	}
	/////////////////////////////////////////
		double x1, y1, F;
		int k = 0;
		do {
			k++;
			cout <<"Step: " << k << endl;

			double f1 = 2 * x + y - 5;
			double f2 = 4 * x - 3 * y + 5;

			unsigned int start_time = clock();

			double resultdenominator;
			thread t([&resultdenominator](double A[2][2], double At[2][2], double f1, double f2) {
				 resultdenominator = denominator(A, At, f1, f2);
			}, A, At, f1, f2);
			double resultnumerator = numerator(f1,f2,At);

			t.join();
			
			lambda = (numerator(f1, f2, At) / denominator(A, At, f1, f2)) / 2;

			cout << "lambda: " << lambda << "\n" << endl;

			x1 = x - derivativex(x, y) * lambda;
			x = x1;
			y1 = y - derivativey(x, y) * lambda;
			y = y1;
			
			cout << "x:" << x << "   " << "y: " << y << "\n" << endl;
	
			F = 20 * (x * x) + 10 * (y * y) - 20 * x * y + 20 * x - 40 * y + 50;
		} while (F >= 0.0001);

	system("PAUSE");
}

