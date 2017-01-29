#include <stdio.h>
#include <math.h>

#define Function(x) exp(x)
#define TARGET 2

//前進差分近似 1階微分係数
double forwardDifference1(int target, double f[5]) {
    return f[target + 1] - f[target];
}

//前進差分近似 2階微分係数
double forwardDifference2(int target, double f[5]) {
    return f[target + 2] - 2 * f[target + 1] + f[target];
}

//後退差分近似 1階微分係数
double backwardDifference1(int target, double f[5]) {
    return f[target] - f[target - 1];
}

//後退差分近似 2階微分係数
double backwardDifference2(int target, double f[5]) {
    return f[target] - 2 * f[target - 1] + f[target - 2];
}

//中間差分近似 1階微分係数
double intermediateDifference1(int target, double f[5]) {
    return (f[target + 1] - f[target - 1]) / 2;
}

//中間差分近似 2階微分係数
double intermediateDifference2(int target, double f[5]) {
    return f[target + 1] - 2 * f[target] + f[target - 1];
}

int main(void) {
    int i;
    double f[5];
    
    for(i = 0; i < 5; i++)
        f[i] = Function(i);

    //前進差分近似
    printf("[forward difference]\n");
    printf("first   :%lf\n", forwardDifference1(TARGET, f));
    printf("second  :%lf\n", forwardDifference2(TARGET, f));

    //後退差分近似
    printf("[backward difference]\n");
    printf("first   :%lf\n", backwardDifference1(TARGET, f));
    printf("second  :%lf\n", backwardDifference2(TARGET, f));

    //中間差分近似
    printf("[intermediate difference]\n");
    printf("first   :%lf\n", intermediateDifference1(TARGET, f));
    printf("second  :%lf\n", intermediateDifference2(TARGET, f));

    return 0;
}