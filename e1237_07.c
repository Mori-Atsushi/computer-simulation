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

/* ニュートンの2次前進差分補間 */
double newton1(double x) {
    double a[3], b[3], r;
    int i, j;

    a[0] = ((int)(x * 10)) / 10.0;
    for(i = 1; i < 3; i++)
        a[i] = a[i - 1] + 0.1;
    r = (x - a[0]) / 0.1;
    
    for(i = 0; i < 3; i++)
        b[i] = function(a[i]);

    return b[0] + r * (b[1] - b[0]) + r * (r - 1) / 2 * ((b[2] - b[1]) - (b[1] - b[0]));
}

/* ニュートンの3次前進差分補間 */
double newton2(double x) {
    double a[4], b[4], r, ans;
    int i, j;

    a[0] = ((int)(x * 10)) / 10.0;
    for(i = 1; i < 4; i++)
        a[i] = a[i - 1] + 0.1;
    r = (x - a[0]) / 0.1;
    
    for(i = 0; i < 4; i++)
        b[i] = function(a[i]);

    ans = b[0];
    ans += r * (b[1] - b[0]);
    ans += r * (r - 1) / 2 * ((b[2] - b[1]) - (b[1] - b[0]));
    ans += (r * (r - 1) * (r - 2)) / (3 * 2) * (((b[3] - b[2]) - (b[2] - b[1])) - ((b[2] - b[1]) - (b[1] - b[0])));

    return  ans;
}

/* ラグランジュ補間 */
double lagrange(double x) {
    double a[3], b[3], n, d, ans = 0;
    int i, j;

    a[0] = ((int)(x * 10)) / 10.0;
    for(i = 1; i < 3; i++)
        a[i] = a[i - 1] + 0.1;
    for(i = 0; i < 3; i++)
        b[i] = function(a[i]);
    
    for(i = 0; i < 3; i++) {
        n = d = 1;
        for(j = 0; j < 3; j++) {
            if(i != j) {
                n *= x - a[j];
                d *= a[i] - a[j];
            }
        }
        ans += n / d * b[i];
    }

    return ans;
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

    printf("[Newton polynomial(2)]\n");
    y = newton2(TARGET);
    printf("|%lf - %lf| = %lf\n\n", ans, y, fabs(ans - y));

    printf("[Lagrange interpolation]\n");
    y = lagrange(TARGET);
    printf("|%lf - %lf| = %lf\n", ans, y, fabs(ans - y));

    return 0;
}