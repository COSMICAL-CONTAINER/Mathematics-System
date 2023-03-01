/*
 * Matrix.c 
 *
 * Copyright (c) 2023,Cosmical Container
 * All rights reserved.
 * 
 * 文件名称：Matrix.h
 * 摘    要：本文件主要是矩阵相关函数的声明
 * 
 * this file is created by Cosmical Container 
 * who want to write a Mathematics system with C program.
 * 
 * thanks you for using it. 
 * 
 * 当前版本：1.0.1
 * 作    者：寰宇体(Cosmical Container)
 * 完成日期：2023年3月1日
 * 
 * 取代版本：1.0.0
 * 原作者  ：寰宇体(Cosmical Container)
 * 完成日期：2023年2月28日
 */
#ifndef _MARTRIX_H 
#define _MARTRIX_H 

#define Check_NULL_Matrix_return(mat)         \
    if ( mat == NULL )                        \
    {                                         \
        MatrixError("The matrix is NULL!");   \
        return NULL;                          \
    }

#define Check_NULL_Matrix_exit(mat)           \
    if ( mat == NULL )                        \
    {                                         \
        MatrixError("The matrix is NULL!");   \
        exit(-1);                             \
    }

typedef struct 
{
    int row;
    int col;
    float **data;
}Matrix;

// 矩阵的内存申请函数
void *MatrixMalloc(size_t _Size);

// 矩阵的内存释放函数
void MatrixFree(void *_Memory);

// 矩阵的报错信息
void MatrixError(const char * _Message);

// 创建矩阵
Matrix *CreateMatrix(int row, int col);

// 创建单位矩阵
Matrix *CreateUnitMatrix(int dimension);

// 初始化矩阵
Matrix *InitMatrix(Matrix *mat, int arr[]);

// 打印矩阵
void PrintMatrix(Matrix *mat);

// 删除矩阵
void DestroyMatrix(Matrix *mat);

// 矩阵加法
Matrix *MatrixAdd(Matrix *mat1, Matrix *mat2);

// 矩阵乘法 matrix multiplication
Matrix *MatrixMul(Matrix *mat1, Matrix *mat2);

// 矩阵数乘 matrix number multiplication
Matrix *MatrixNumMul(Matrix *mat, float k);

// 矩阵数除
Matrix *MatrixNumDiv(Matrix *mat, float k);

// 计算行列式(Determinant)
float MatrixDetCalc(Matrix *mat);
// 计算行列式(Determinant)中的递归函数
float MatrixDet(Matrix *mat, int x);

// 矩阵转置
Matrix *MatrixTranspose(Matrix *mat);

// 矩阵求逆
Matrix *MatrixInverse(Matrix *mat);

// 矩阵求秩
int MatrixRankCalc(Matrix* mat);

#endif //_MARTRIX_H 