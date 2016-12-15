#include <stdio.h>
#include <math.h>

#define NUM 3 //行列のサイズ
#define EP 0.001 //終了条件

const double array[NUM][NUM] = {
    {2, -1, 0},
    {-1, 2, -1},
    {0, -1, 2}
};

/* 行列arrayをNにコピーする N=A */
void M_copy(const double A[NUM][NUM], double N[NUM][NUM]) {
    int i, j;

    for(i = 0; i < NUM; i++) {
        for(j = 0; j < NUM; j++)
            N[i][j] = A[i][j];
    }
}

/* 行列を転置する C=A^T */
void M_transpose(const double A[NUM][NUM], double C[NUM][NUM]) {
    int i, j;

    for(i = 0; i < NUM; i++) {
        for(j = 0; j < NUM; j++)
            C[j][i] = A[i][j];
    }

}

/* 行列積C=ABを計算する．行列なので，掛け算の順序に注意 */
void M_multiply(const double A[NUM][NUM], const double B[NUM][NUM], double C[NUM][NUM]) {
    int i, j, k;

    for(i = 0; i < NUM; i++) {
        for(j = 0; j < NUM; j++) {
            C[i][j] = 0;
            for(k = 0; k < NUM; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* y=Ax（Aは行列，x,yはベクトル）を計算する */
void v_multiply(const double A[NUM][NUM], const double x[NUM], double y[NUM]) {
    int i, j;

    for(i = 0; i < NUM; i++) {
        y[i] = 0;
        for(j = 0; j < NUM; j++)
            y[i] += A[i][j] * x[j];
    }
}

/* ベクトルの長さを計算する関数 */
double length(double l[NUM]) {
    int i;
    double sum = 0;

    for(i = 0; i < 3; i++)
        sum += pow(l[i], 2);
    return sqrt(sum);
}

/* ヤコビ法(最大固有値を返す) */
double jacobi() {
    int i, j, p, q, flag = 0;
    double A[NUM][NUM], M[NUM][NUM], Mt[NUM][NUM], temp[NUM][NUM], eigenvetor[NUM][NUM];
    double max = 0, theta;

    M_copy(array, A);

    while(1) {
        p = 0; q = 1;
        for(i = 0; i < NUM; i++) {
            for(j = 0; j < NUM; j++) {
                if(i != j && fabs(A[p][q]) < fabs(A[i][j])) {
                    p = i;
                    q = j;
                }
            }
        }

        if(fabs(A[p][q]) < EP)
            break;

        if(A[p][p] == A[q][q])
            theta = M_PI / 4;
        else
            theta = atan((2 * A[p][q]) / (A[q][q] - A[p][p])) / 2;

        for(i = 0; i < NUM; i++) {
            for(j = 0; j < NUM; j++) {
                if(i == p && j == p)
                    M[i][j] = cos(theta);
                else if(i == p && j == q)
                    M[i][j] = sin(theta);
                else if(i == q && j == p)
                    M[i][j] = -sin(theta);
                else if(i == q && j == q)
                    M[i][j] = cos(theta);
                else if(i == j)
                    M[i][j] = 1;
                else
                    M[i][j] = 0;
            }
        }

        M_transpose(M, Mt);
        M_multiply(Mt, A, temp);
        M_multiply(temp, M, A);

        if(flag == 0) {
            M_copy(M, eigenvetor);
            flag = 1;
        } else {
            M_multiply(eigenvetor, M, temp);
            M_copy(temp, eigenvetor);
        }
    }

    for(i = 0; i < NUM; i++) {
        if(fabs(max) < fabs(A[i][i]))
            max = A[i][i];
        printf("eigenvalue:%lf\neigenvetor:(", A[i][i]);
        for(j = 0; j < NUM; j++) {
            printf("%lf", eigenvetor[j][i]);
            if(j != NUM - 1)
                printf(", ");
        }
        printf(")\n\n");
    }

    return fabs(max);
}

/* 累乗法(最大固有値を返す) */
double power_iteration() {
    int i, n = 1;
    double v[NUM], v_old[NUM], temp[NUM], max, x;

    for(i = 0; i < NUM; i++)
        v[i] = 1;

    do {
        for(i = 0; i < NUM; i++)
            v_old[i] = v[i];
        
        v_multiply(array, v, temp);
        max = length(temp);
        for(i = 0; i < NUM; i++)
            v[i] = temp[i] / max;

        for(i = 0; i < NUM; i++)
            temp[i] = v[i] - v_old[i];

        printf("%d:%lf\n", n++, max);
    } while(length(temp) > EP);

    printf("\nmax-eigenvalue:%lf\nmax-eigenvetor:(", max);
    for(i = 0; i < NUM; i++) {
        printf("%lf", v[i]);
        if(i != NUM - 1)
            printf(", ");
    }
    printf(")\n\n");

    return max;
}

int main(void) {
    double jacobi_max, power_iteration_max;

    printf("[Jacobi method]\n");
    jacobi_max = jacobi();

    printf("[Power iteration]\n");
    power_iteration_max = power_iteration();

    printf("[Difference]\n");
    printf("max-eigenvalue difference:%lf\n", fabs(jacobi_max - power_iteration_max));

    return 0;
}