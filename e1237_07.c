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

int main(void) {
    double ans = function(TARGET), y;

    printf("[Linear interpolation]\n");
    y = liner(TARGET);
    printf("|%lf - %lf| = %lf\n", ans, y, fabs(ans - y));

    return 0;
}