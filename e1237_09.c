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

//ラグランジュ補間 1階微分係数
double lagrangian(int target, double f[5]) {
    int i, j, k;
    double L, N, D, l;

    for(i = 0, L = 0; i < 5; i++) {
        for(j = 0, N = 0, D = 1; j < 5; j++) {
            if(i != j) {
                D *= i - j;
                l = 1;
                for(k = 0; k < 5; k++) {
                    if(k != i && k != j)
                        l *= target - k;
                }
                N += l;
            }
        }
        L += N / D * f[i];
    }

    return L;
}

int main(void) {
    int i;
    double f[5], ans, trueValue;
    
    for(i = 0; i < 5; i++)
        f[i] = Function(i);
    trueValue = Function(TARGET);

    //前進差分近似
    printf("[forward difference]\n");
    ans = forwardDifference1(TARGET, f);
    printf("first   :f'(%d) = %lf,  diff = %lf\n", TARGET, ans, ans - trueValue);
    ans = forwardDifference2(TARGET, f);
    printf("second  :f''(%d) = %lf, diff = %lf\n", TARGET, ans, ans - trueValue);

    //後退差分近似
    printf("[backward difference]\n");
    ans = backwardDifference1(TARGET, f);
    printf("first   :f'(%d) = %lf,  diff = %lf\n", TARGET, ans, ans - trueValue);
    ans = backwardDifference1(TARGET, f);
    printf("second  :f''(%d) = %lf, diff = %lf\n", TARGET, ans, ans - trueValue);

    //中間差分近似
    printf("[intermediate difference]\n");
    ans = intermediateDifference1(TARGET, f);
    printf("first   :f'(%d) = %lf,  diff = %lf\n", TARGET, ans, ans - trueValue);
    ans = intermediateDifference1(TARGET, f);
    printf("second  :f''(%d) = %lf, diff = %lf\n", TARGET, ans, ans - trueValue);

    //ラグランジュ補間
    printf("[lagrangian]\n");
    ans = lagrangian(TARGET, f);
    printf("first   :f'(%d) = %lf,  diff = %lf\n", TARGET, ans, ans - trueValue);

    return 0;
}