#include <stdio.h>
#include <math.h>

int main(void) {
	int i, a;
	float x_f, y_f;
	double x, temp, x_d, y_d;

	/* 問1 */
	printf("x_1:");
	scanf("%lf", &x);

	for(i = 2; x - temp > 0.0001 || x - temp < -0.0001; i++) {
		temp = x;
		x = 1 + 1 / x;
		printf("x_%2d = %lf\n", i, x);
	}

	printf("\nx_1:");
	scanf("%lf", &x);

	for(i = 2; x - temp > 0.0001 || x - temp < -0.0001; i++) {
		temp = x;
		x = (pow(x, 2) + 1) / (2 * x - 1);
		printf("x_%2d = %lf\n", i, x);
	}

	/* 問2 */
	printf("\n%lf\n", fabs((1 - pow(M_PI / 6, 2) / 2) - 0.8660));

	/* 問3 */
	x_f = 1234567;
	y_f = 0.01;
	printf("\nfloat:%f\n", sqrtf(x_f + y_f) - sqrtf(x_f));

	x_d = 1234567;
	y_d = 0.01;
	printf("double:%lf\n", sqrt(x_d + y_d) - sqrt(x_d));

	x_f = 1234567;
	y_f = 0.01;
	printf("float(improved):%f\n", y_f / (sqrt(x_d + y_d) + sqrt(x_d)));

	return 0;
}