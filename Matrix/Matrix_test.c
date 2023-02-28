#include <stdio.h>
#include "Matrix.h"

int main() 
{
    // 创建矩阵
    Matrix *A = createMatrix(2, 3);
    Matrix *B = createMatrix(3, 2);
    Matrix *Det = createMatrix(2, 2);

    // 初始化矩阵
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int arr3[] = {1, 2, 3, 4};
    matrix_init(A, arr1);
    matrix_init(B, arr2);
    matrix_init(Det, arr3);

    //打印a b矩阵
    printf("A(2,3):\n");
    printMatrix(A);
    printf("B(3,2):\n");
    printMatrix(B);

    // 矩阵转置
    Matrix *C = matrix_transpose(A);
    printf("C = A^T:\n");
    printMatrix(C);

    // 矩阵加法
    Matrix *D = matrix_add(A, A);
    printf("D = A + A:\n");
    printMatrix(D);

    // 矩阵数乘
    Matrix *E = matrix_mul(A, B);
    printf("E = A * B:\n");
    printMatrix(E);

    // 矩阵数除
    Matrix *F = matrix_sca_div(A, 2.0);
    printf("F = A / k:%.2f\n", 2.0);
    printMatrix(F);

    // 求矩阵转化为行列式的值
    printf("Det:\n|1 2|\n|3 4| =  %.2f\n\n",matrix_Det_Cal(Det));

    // 创建单位矩阵
    Matrix* G = createUnitMatrix(5);
    printf("UnitMatrix E(5):\n");
    printMatrix(G);

    // 求矩阵的逆矩阵并验算
    Matrix* Det_inverse = matrix_inverse(Det);
    printf("InverseMatrix Det_inverse = Det^-1:\n");
    printMatrix(Det_inverse);
    Matrix *result = matrix_mul(Det, Det_inverse);
    printf("result = Det * Det_inverse:\n");
    printMatrix(result);

    //求矩阵的秩
    printf("\nrank(Det) %d:\n", matrix_rank(Det));

    // 释放内存
    destroyMatrix(&A);
    destroyMatrix(&B);
    destroyMatrix(&C);
    destroyMatrix(&D);
    destroyMatrix(&E);
    destroyMatrix(&F);
    destroyMatrix(&G);
    destroyMatrix(&Det_inverse);
    destroyMatrix(&result);

    return 0;
}