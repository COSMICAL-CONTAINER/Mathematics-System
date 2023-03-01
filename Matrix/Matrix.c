/*
 * Matrix.c 
 *
 * Copyright (c) 2023,Cosmical Container
 * All rights reserved.
 * 
 * 文件名称：Matrix.c
 * 摘    要：本文件主要是矩阵相关函数的实现
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

void *MatrixMalloc(size_t _Size)
{
    return malloc(_Size);
}

void MatrixFree(void *_Memory)
{
    free(_Memory);
}

void MatrixError(const char *_Message)
{
    printf("%s\n", _Message);
}

// 创建矩阵
Matrix *CreateMatrix(int row, int col) 
{
    Matrix *mat = (Matrix*)MatrixMalloc(sizeof(Matrix));

    if ( mat == NULL )
    {
        MatrixError("CreateMatrix: create matrix failed");
        exit(-1);
    } 

    mat->row = row;
    mat->col = col;
    mat->data = (float**)MatrixMalloc(row * sizeof(float*));

    if (mat->data == NULL)
    {
        MatrixError("CreateMatrix: create matrix data failed");
        exit(-1);
    }

    for (int i = 0; i < row; i++) 
    {
        mat->data[i] = (float*)MatrixMalloc(col * sizeof(float));
        if (mat->data[i] == NULL)
        {
            MatrixError("CreateMatrix: create matrix data failed");
            exit(-1);
        }

        for (int j = 0; j < col; j++) 
        {
            mat->data[i][j] = 0;
        }
    }
    return mat;
}

Matrix *CreateUnitMatrix(int dimension)
{
    Matrix *mat = CreateMatrix(dimension, dimension);

    for (int i = 0; i < dimension; i++) 
    {
        for (int j = 0; j < dimension; j++) 
        {
            mat->data[i][j] = (i == j ? 1 : 0);
        }
    }
    return mat;
}

// 初始化矩阵
Matrix *InitMatrix(Matrix *mat, int arr[])
{
    Check_NULL_Matrix_return (mat);

    for (int i = 0; i < mat->row; i++) 
    {
        for (int j = 0; j < mat->col; j++) 
        {
            mat->data[i][j] = arr[i * mat->col + j];
        }
    }
    return mat;
}

// 打印矩阵
void PrintMatrix(Matrix *mat)
{
    if ( mat != NULL )
    {
        for (int i = 0; i < mat->row; i++) 
        {
            for (int j = 0; j < mat->col; j++) 
            {
                printf("%.2f ",mat->data[i][j]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

// 释放矩阵
void DestroyMatrix(Matrix *mat) 
{
    if ( mat == NULL )
    {
        return ;
    }

    for (int i = 0; i < mat->row; i++) 
    {
        MatrixFree(mat->data[i]);
    }

    MatrixFree(mat->data);
    MatrixFree(mat);
}

// 矩阵加法
Matrix *MatrixAdd(Matrix *mat1, Matrix *mat2) 
{
    if (mat1 == NULL || mat2 == NULL)
    {
        MatrixError("The matrix is NULL!");
        return NULL;
    }

    if (mat1->row != mat2->row || mat1->col != mat2->col) 
    {
        MatrixError("Error: The sizes of two matrices are not equal.\n");
        exit(-1);
    }

    Matrix *mat = CreateMatrix(mat1->row, mat2->col);
    for (int i = 0; i < mat1->row; i++) 
    {
        for (int j = 0; j < mat1->col; j++) 
        {
            mat->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }
    return mat;
}

// 矩阵乘法
Matrix *MatrixMul(Matrix *mat1, Matrix *mat2) 
{
    if (mat1 == NULL || mat2 == NULL)
    {
        return NULL;
    }

    if (mat1->col != mat2->row) 
    {
        MatrixError("Error: The sizes of two matrices are not compatible for multiplication.\n");
        exit(-1);
    }

    Matrix *mat = CreateMatrix(mat1->row, mat2->col);
    
    for (int i = 0; i < mat1->row; i++) 
    {
        for (int j = 0; j < mat2->col; j++) 
        {
            for (int k = 0; k < mat1->col; k++) 
            {
                mat->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }
    return mat;
}

// 矩阵数乘 matrix number multiplication
Matrix *MatrixNumMul(Matrix *mat, float k)
{
    Check_NULL_Matrix_return (mat)

    for (int i = 0; i < mat->row; i++)
    {
        for (int j = 0; j < mat->col; j++) 
        {
            mat->data[i][j] *= k;
        }
    }
    return mat;
}

// 矩阵数除 matrix number division
Matrix *MatrixNumDiv(Matrix *mat, float k) 
{
    Check_NULL_Matrix_return (mat);

    if ( k == 0 )
    {
        MatrixError("The divisor cannot be 0!");
        return mat;
    }

    for (int i = 0; i < mat->row; i++) 
    {
        for (int j = 0; j < mat->col; j++) 
        {
            mat->data[i][j] /= k;
        }
    }

    return mat;
}

// 计算矩阵转换为行列式之后的值
float MatrixDetCalc(Matrix *mat)
{
    Check_NULL_Matrix_exit(mat);

    if ( mat->col != mat->row )
    {
        MatrixError("Error: The matrix is not square!");
        exit(-1);
    }

    return MatrixDet(mat, mat->col);
}

//计算矩阵的行列式递归函数
float MatrixDet(Matrix *mat, int x)
{
    int i=0, j=0, s=0, k=0;
    Matrix* c = CreateMatrix(x, x);  //用c数组来表示余子列
    if (x == 1)
    {
        s = mat->data[0][0];
    }
    else
    {
        for(j=0;j<x;j++)
        {
            for(i=0;i<x-1;i++)
            {
                for(k=0;k<x-1;k++)
                {
                    if(k<j)
                        c->data[i][k]=mat->data[i+1][k];
                    if(k>=j)
                        c->data[i][k]=mat->data[i+1][k+1];
                }
            }
            s += pow(-1,j) * mat->data[0][j] * MatrixDet(c, x-1); //递归算法求出值
            DestroyMatrix(c);
        }
    }
	return s;
}

// 矩阵转置
Matrix *MatrixTranspose(Matrix *mat) 
{
    Check_NULL_Matrix_return(mat);

    Matrix *transpose_mat = CreateMatrix(mat->col, mat->row);
    for (int i = 0; i < mat->row; i++) 
    {
        for (int j = 0; j < mat->col; j++) 
        {
            transpose_mat->data[j][i] = mat->data[i][j];
        }
    }
    return transpose_mat;
}

// 矩阵求逆
Matrix *MatrixInverse(Matrix *mat) 
{
    Check_NULL_Matrix_return(mat);

    if (mat->row != mat->col) 
    {
        MatrixError("Error: matrix not square, can't be inversed.\n");
        return NULL;
    }

    int n = mat->row;
    Matrix* res = CreateMatrix(n, n * 2);

    // 将原矩阵和单位矩阵拼接成增广矩阵
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            res->data[i][j] = mat->data[i][j];
        }
        res->data[i][n + i] = 1.0;
    }

    // 高斯-约旦消元法
    for (int i = 0; i < n; i++) 
    {
        float t = res->data[i][i];
        if (t == 0) 
        {
            MatrixError("Error: matrix can't be inversed.\n");
            DestroyMatrix(res);
            return NULL;
        }
        for (int j = i; j < n * 2; j++) 
        {
            res->data[i][j] /= t;
        }
        for (int j = 0; j < n; j++) 
        {
            if (j != i) 
            {
                t = res->data[j][i];
                for (int k = i; k < n * 2; k++) 
                {
                    res->data[j][k] -= t * res->data[i][k];
                }
            }
        }
    }

    // 提取逆矩阵
    Matrix* inv = CreateMatrix(n, n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            inv->data[i][j] = res->data[i][n + j];
        }
    }

    // 释放资源
    DestroyMatrix(res);

    return inv;
}

// 矩阵求秩
int MatrixRankCalc(Matrix* mat)
{
    Check_NULL_Matrix_exit(mat);

    int rank = 0;
    int n = mat->row;
    int m = mat->col;
    int i, j, k;

    // 构造矩阵的行阶梯型矩阵
    for (i = 0; i < n; i++) 
    {
        // 如果行阶梯型矩阵的最后一行是全0，则矩阵的秩为当前行数
        if (mat->data[i][i] == 0) 
        {
            break;
        }
        rank++;

        // 对于每一行，将该行以下的行通过高斯消元变为全0，得到行阶梯型矩阵
        for (j = i + 1; j < n; j++) 
        {
            float factor = mat->data[j][i] / mat->data[i][i];
            for (k = i; k < m; k++) 
            {
                mat->data[j][k] -= factor * mat->data[i][k];
            }
        }
    }

    return rank;
}

