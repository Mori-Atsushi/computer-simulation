#include <stdio.h>
#include <math.h>

#define TARGET 0.15
#define function(x) 1237 * (x) * (x)

/* 線形補間 */
double liner(double x) {
    double a, b, alpha;

    a = ((int)(x * 10)) / 10.0;
    b = a + 0.1;
    alpha = (x - a) / (b - a);
    return (1 - alpha) * function(a) + alpha * function(b);
}

/* ニュートンの2次前進差分補間(1) */
double newton1(double x) {
    double a[3], b[3], r, ans, temp, delta;
    int i, j;

    a[0] = ((int)(x * 10)) / 10.0;
    for(i = 1; i < 3; i++)
        a[i] = a[i - 1] + 0.1;
    r = (x - a[0]) / 0.1;
    
    for(i = 0; i < 3; i++)
        b[i] = function(a[i]);

    return b[0] + r * (b[1] - b[0]) + r * (r - 1) / 2 * ((b[2] - b[1]) - (b[1] - b[0]));
}

int main(void) {
    const double ans = function(TARGET);
    double y;

    printf("[Linear interpolation]\n");
    y = liner(TARGET);
    printf("|%lf - %lf| = %lf\n\n", ans, y, fabs(ans - y));

    printf("[Newton polynomial(1)]\n");
    y = newton1(TARGET);
    printf("|%lf - %lf| = %lf\n\n", ans, y, fabs(ans - y));

    return 0;
}