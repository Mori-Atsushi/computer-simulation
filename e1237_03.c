#include <stdio.h>
#include <math.h>

#define N 37

/* f(x) */
double f(double x) {
	return 15 * pow(x, 2) - N - exp(x);
}

/* f'(x) */
double fd(double x) {
	return 30 * x - exp(x);
}

/* ニュートン法 */
double newton(double s) {
	double x;
	int i;

	x = s;
	i = 0;
	while(fabs(f(x)) > 0.0001) {
		printf(" %2d : x = %lf\n", i++, x);
		x = x - f(x) / fd(x);
	}

	return x;
}

/* 割線法 */
double secant(double s1, double s2) {
	double x, old, temp;
	int i;

	old = s1;
	x = s2;
	i = 0;
	while(fabs(f(x)) > 0.0001) {
		printf(" %2d : x = %lf\n", i++, x);
		temp = x - f(x) * ((x - old) / (f(x) - f(old)));
		old = x;
		x = temp;
	}

	return x;
}

/* 二分法 */
double bisection(double s1, double s2) {
	double a, b, c;
	int i;

	a = s1;
	b = s2;
	printf("f(a) * f(b) = %lf < 0\n", f(a) * f(b));
	i = 0;
	while(fabs(b - a) > 0.0001) {
		printf(" %2d : x = %lf\n", i++, a);
		c = (a + b) / 2;
		if(fabs(f(c)) < 0.0001)
			return c;
		if(f(a) * f(c) < 0)
			b = c;
		else
			a = c;		
	}

	return a;
}

/* 黄金分割法 */
double golden(double s1, double s2) {
	double a, b, c;
	int i;

	a = s1;
	b = s2;
	c = 0;
	printf("f(a) * f(b) = %lf < 0\n", f(a) * f(b));
	i = 0;
	while(fabs(b - a) > 0.0001) {
		printf(" %2d : x = %lf\n", i++, a);
		c = ((1 + sqrt(5)) * a + 2 * b) / (3 + sqrt(5));
		if(fabs(f(c)) < 0.0001)
			return c;
		if(f(a) * f(c) < 0)
			b = c;
		else
			a = c;		
	}

	return a;	
}

/* 狭撃法 */
double false(double s1, double s2) {
	double a, b, c;
	int i;

	a = s1;
	b = s2;
	c = 0;
	printf("f(a) * f(b) = %lf < 0\n", f(a) * f(b));
	i = 0;
	while(fabs(b - a) > 0.0001) {
		printf(" %2d : x = %lf\n", i++, a);
		c = (a * f(b) - b * f(a)) / (f(b) - f(a));
		if(fabs(f(c)) < 0.0001)
			return c;
		if(f(a) * f(c) < 0)
			b = c;
		else
			a = c;		
	}

	return a;	
}


int main(void) {
	printf("[Newton method]\n");
	printf("ans : x = %lf\n", newton(1));

	printf("\n[Secant method]\n");
	printf("ans : x = %lf\n", secant(1, 2));	

	printf("\n[Bisection method]\n");
	printf("ans : x = %lf\n", bisection(1, 2));

	printf("\n[Golden section method]\n");
	printf("ans : x = %lf\n", golden(1, 2));

	printf("\n[False position method]\n");
	printf("ans : x = %lf\n", false(1, 2));

	return 0;
}