#include <stdio.h>
#include <math.h>

#define N 37 //学籍番号
#define NUM 3 //xの数
#define EP 0.001 //終了条件
#define PARA 1.1 //SOR法 パラメータ

const double array[NUM][NUM + 1] = {
    {15, 5, 4, 8},
    {12, 13, 10, 16},
    {1, 2, 17, N + 1}
};

/* ヤコビ法 */
void jacobi() {
    int i, j, n = 1;
    double x[NUM], x_new[NUM], dif;

    for(i = 0; i < NUM; i++)
        x[i] = 0;

    do {
        printf("%d\n", n++);
        for(i = 0; i < NUM; i++) {
            x_new[i] = array[i][NUM];
            for(j = 0; j < NUM; j++) {
                if(i != j)
                    x_new[i] -= array[i][j] * x[j];
            }
            x_new[i] /= array[i][i];
        }

        for(i = 0, dif = 0; i < NUM; i++)
            dif += pow(x[i] - x_new[i], 2);
        dif = sqrt(dif);

        for(i = 0; i < NUM; i++) {
            x[i]  = x_new[i];
            printf(" x[%d]:%lf\n", i, x[i]);
        }

        printf("\n");
    } while(dif > EP);
}

/* ガウス=ザイデル法 */
void gauss_seidel() {
    int i, j, n = 1;
    double x[NUM], x_old[NUM], dif;

    for(i = 0; i < NUM; i++) {
        x[i] = 0;
        x_old[i] = 0;
    }

    do {
        printf("%d\n", n++);
        for(i = 0; i < NUM; i++) {
            x[i] = array[i][NUM];
            for(j = 0; j < NUM; j++) {
                if(i != j)
                    x[i] -= array[i][j] * x[j];
            }
            x[i] /= array[i][i];
        }

        for(i = 0, dif = 0; i < NUM; i++)
            dif += pow(x[i] - x_old[i], 2);
        dif = sqrt(dif);

        for(i = 0; i < NUM; i++) {
            x_old[i]  = x[i];
            printf(" x[%d]:%lf\n", i, x[i]);
        }

        printf("\n");
    } while(dif > EP);
}

/* SOR法 */
void sor() {
    int i, j, n = 1;
    double x[NUM], x_old[NUM], dif, temp;

    for(i = 0; i < NUM; i++) {
        x[i] = 0;
        x_old[i] = 0;
    }

    do {
        printf("%d\n", n++);
        for(i = 0; i < NUM; i++) {
            temp = array[i][NUM];
            for(j = 0; j < NUM; j++)
                temp -= array[i][j] * x[j];
            temp /= array[i][i];
            temp *= PARA;
            x[i] += temp;
        }

        for(i = 0, dif = 0; i < NUM; i++)
            dif += pow(x[i] - x_old[i], 2);
        dif = sqrt(dif);

        for(i = 0; i < NUM; i++) {
            x_old[i]  = x[i];
            printf(" x[%d]:%lf\n", i, x[i]);
        }

        printf("\n");
    } while(dif > EP);
}

int main(void) {
    
    printf("[Jacobi method]\n");
    jacobi();

    printf("[Gauss-Seidel method]\n");
    gauss_seidel();

    printf("[Successive Over-Relaxation]\n");
    sor();

    return 0;
}