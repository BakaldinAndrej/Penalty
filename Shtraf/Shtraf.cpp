#include "stdafx.h"
#include <stdio.h>
#include <cmath>
#include <math.h>
#include <windows.h>

#define var_count 2
#define max_iterations 5000
#define C 100

double r = 0.1, eps = 0.0000001;

//исходная функция
double F(double *x)
{
	return 4 * x[0] * x[0] + 8 * x[0] - x[1] - 3;
}

//функция ограничения
double G(double *x)
{
	return x[0] + x[1] + 2;
}

//функция штрафа
double T(double *x)
{
	return G(x)*G(x);
}

//штрафная функция
double P(double *x, double r)
{
	return F(x) + r*T(x);
}

//золотое сечение
double golden_section(double* vars, int var_index, double eps, double a, double b, int max_steps_count)
{
	double res = 0.0;
	double phi = (1 + sqrt(5.0)) / 2.0;
	double A = 0.0f, B = 0.0f;
	double x1 = a + phi * (b - a), x2 = b - phi * (b - a);

	int step = 0;

	while ((b - a > eps))
	{
		x1 = b - ((b - a) / phi);
		vars[var_index] = x1;
		A = P(vars, r);
		x2 = a + ((b - a) / phi);
		vars[var_index] = x2;
		B = P(vars, r);
		if (A > B)
			a = x1;
		else
			b = x2;

		step++;
		if (step > max_steps_count)
			break;
	}

	res = (a + b) / 2;
	return res;
}

//покоординатный спуск
void descent_method(double* vars, double eps, int max_steps_count)
{
	double B = P(vars, r), A = 0;
	bool was_counted = false;
	int stpes_ellapsed = 0;
	double delta = 0.0;
	for (int i = 0; i < max_steps_count; i++) {
		A = B;

		for (int var_index = 0; var_index < var_count; var_index++)
			vars[var_index] = golden_section(vars, var_index, eps, -5000, 5000, max_steps_count);

		B = P(vars, r);

		delta = fabs(A - B);

		if (delta <= eps)
		{
			stpes_ellapsed = i + 1;
			was_counted = true;
			break;
		}
	}
}

int main()
{
	double X[2] = { 0.0 };
	int K = 0;

	printf("Enter X0[0]: ");
	scanf("%f", &X[0]);

	printf("Enter X0[1]: ");
	scanf("%f", &X[1]);

	while (true)
	{
		descent_method(X, eps, max_iterations);

		if (abs(r*T(X)) <= eps)
		{
			printf("results(%d): X[0] = %f; X[1] = %f; F(X) = %f; \n", K, X[0], X[1], F(X));
			break;
		}

		K += 1;

		r *= C;
	}

	system("pause");

	return 0;
}