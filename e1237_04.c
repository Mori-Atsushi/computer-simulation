#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X 37 + 1 //学籍番号+1
#define N 3

/* スワップ計算 */
void swap(double x, double y) {
    double temp =  x;
    x = y;
    y = temp;
}

/* 掃き出し法計算ルーチン */
void sweep(double a[N][N], double x[N], double b[N]) {
    int i, j, k, max;
    double akk, aik, copy;

    for(k = 0; k < N; k++) {
        max = k;

        for(i = k + 1; i < N; i++) {
            if(fabs(a[i][k]) > fabs(a[max][k]))
                max = i;
        }

        /* 例外処理(対角成分が小さな値になったとき) */
        if(fabs(a[max][k]) < 1.0e-7)
            exit(0);

        /* 行の入れ替え */
        if(max != k) {
            for(j = 0; j < N; j++) {
                copy = a[k][j];
                a[k][j] = a[max][j];
                a[max][j] = copy;
            }
            copy = b[k];
            b[k] = b[max];
            b[max] = copy;
        }

        /* 掃き出し */
        akk = a[k][k];
        for(i = k; i < N; i++) {
            a[k][i] /= akk;
        }
        b[k] /= akk;

        for(i = 0; i < N; i++) {
            aik = a[i][k];
            if(i != k) {
                for(j = k; j < N; j++)
                    a[i][j] -= aik * a[k][j];
                b[i] -= aik * b[k];
            }
        }
    }

    for(k = 0; k < N; k++)
        x[k] = b[k];
}

/* ガウスの消去法計算ルーチン */
void gauss(double a[N][N], double x[N], double b[N]) {
    double akk, aik, copy;
    int i, j, k, max;

    /* ピポッド選択 */
    for(k = 0; k < N - 1; k++) {
        max = k;

        for(i = k + 1; i < N; i++) {
            if(fabs(a[i][k]) > fabs(a[max][k]))
                max = i;
        }

        /* 例外処理(対角成分が小さな値になったとき) */
        if(fabs(a[max][k]) < 1.0e-7)
            exit(0);
        
        /* 行の入れ替え */
        if(max != k) {
            for(j = 0; j < N; j++) {
                copy = a[k][j];
                a[k][j] = a[max][j];
                a[max][j] = copy;
            }
            copy = b[k];
            b[k] = b[max];
            b[max] = copy;
        }

        /* 前進消去 */
        akk = a[k][k];

        for(j = k; j < N; j++)
            a[k][j] /= akk;
        b[k] /= akk;

        for(i = k + 1; i < N; i++) {
            aik = a[i][k];

            for(j = k; j < N; j++)
                a[i][j] -= aik * a[k][j];
            b[i] -= aik * b[k];
        }
    }

    /* 後退代入 */
    x[k] = b[k] / a[k][k];

    for(k = N - 2; k >= 0; k--) {
        for(j = 0; j < N; j++)
            x[k] -= a[k][j] * x[j];
        x[k] += b[k];
    }
}

int main(void) {
    double _a[N][N] = {{6, 5, 4}, {12, 13, 10}, {18, 21, 17}}, a[N][N], x[N];
    double _b[N] = {8, 16, X}, b[N];
    int i, j;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++)
            a[i][j] = _a[i][j];
        b[i] = _b[i];
    }

    /* 掃き出し法のアルゴリズム */
    printf("Sweeping-out method\n");
    sweep(a, x, b);
    for(i = 0; i < N; i++)
        printf("x[%d] = %f\n", i, x[i]);

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++)
            a[i][j] = _a[i][j];
        b[i] = _b[i];
    }

    /* ガウスの消去法 */
    printf("\nGaussian elimination method\n");
    gauss(a, x, b);
    for(i = 0; i < N; i++)
        printf("x[%d] = %f\n", i, x[i]);

    return 0;
}