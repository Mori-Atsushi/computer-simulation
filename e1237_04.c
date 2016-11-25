#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X 37 + 1 //学籍番号+1
#define N 3

/* ガウスの消去法計算ルーチン */
void gauss(double a[N][N], double x[N], double b[N]) {
    double copy, akk, aik;
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
    double a[N][N] = {{6, 5, 4}, {12, 13, 10}, {18, 21, 17}}, x[N];
    double b[N] = {8, 16, X};
    int i;

    /* ガウスの消去法 */
    gauss(a, x, b);

    for(i = 0; i < N; i++)
        printf("x[%d] = %f\n", i, x[i]);

    return 0;
}