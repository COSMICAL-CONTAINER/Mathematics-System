#include <stdio.h>
#include "Matrix.h"

int main() 
{
    // 创建矩阵
    Matrix *A = CreateMatrix(2, 3);
    Matrix *B = CreateMatrix(3, 2);
    Matrix *det = CreateMatrix(2, 2);

    // 初始化矩阵
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {1, 2, 3, 4, 5, 6};
    int arr3[] = {1, 2, 3, 4};

    printf("Create and Init Matrix:\n\n");
    InitMatrix(A, arr1);
    InitMatrix(B, arr2);
    InitMatrix(det, arr3);
    
    // 打印A矩阵
    printf("A(2,3):\n");
    PrintMatrix(A);

    // 打印B矩阵
    printf("B(3,2):\n");
    PrintMatrix(B);

    // 矩阵数乘
    MatrixNumMul(A, 6.0);
    printf("MatrixNumMul:\nA_mul = A * k(%.2f)\n", 6.0);
    PrintMatrix(A);

    // 矩阵数除
    MatrixNumDiv(A, 3.0);
    printf("MatrixNumDiv:\nA_div = A / k(%.2f)\n", 3.0);
    PrintMatrix(A);

    MatrixNumDiv(A, 2.0); // 只是把A恢复原样

    // 矩阵转置
    Matrix *C = MatrixTranspose(A);
    printf("MatrixTranspose:\nC = A^T:\n");
    PrintMatrix(C);

    // 矩阵加法
    Matrix *D = MatrixAdd(A, A);
    printf("MatrixAdd:\nD = A + A:\n");
    PrintMatrix(D);

    // 矩阵乘法
    Matrix *E = MatrixMul(A, B);
    printf("MatrixMul:\nE = A * B:\n");
    PrintMatrix(E);

    // 求矩阵转化为行列式的值
    printf("DetCalc:\ndet = \n|1 2|\n|3 4| = %.2f\n\n", MatrixDetCalc(det));

    // 创建单位矩阵
    Matrix *F = CreateUnitMatrix(5);
    printf("UnitMatrix E(5):\n");
    PrintMatrix(F);

    // 求矩阵的逆矩阵并验算
    Matrix *detInverse = MatrixInverse(det);
    printf("InverseMatrix\ndetInverse = det^-1:\n");
    PrintMatrix(detInverse);

    Matrix *result = MatrixMul(det, detInverse);
    printf("CheckInverse:\nresult = det * detInverse:\n");
    PrintMatrix(result);

    // 求矩阵的秩
    printf("Rank(det) %d:\n", MatrixRankCalc(det));

    // 释放内存
    DestroyMatrix(A);
    DestroyMatrix(B);
    DestroyMatrix(C);
    DestroyMatrix(D);
    DestroyMatrix(E);
    DestroyMatrix(F);
    DestroyMatrix(detInverse);
    DestroyMatrix(result);

    getchar();
    return 0;
}