#include <stdio.h>
#include <math.h>

#define N 6

typedef struct {
    double x;
    double y;
} Data;

int main(void) {
    int i;
    Data data[N] = {{0.0, 10.2} , {1.0, 12.0} , {2.0, 15.7} , {3.0, 17.0} , {4.0, 20.5} , {5.0, 22.4}};
    double a = 0, b = 0;
    double xy = 0, x = 0, y = 0, x2 = 0;

    for (i = 0; i < N; i ++) {
        xy += data[i].x * data[i].y;
        x += data[i].x;
        y += data[i].y;
        x2 += pow(data[i].x, 2);
    }
    
    a = (N * xy - x * y) / (N * x2 - pow(x, 2));
    b = (x2 * y - xy * x) / (N * x2 - pow(x, 2));

    printf("y = %f x + %f\n", a, b);

    return 0;
}