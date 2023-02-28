/*
 * Matrix.c 
 *
 * Copyright 2023 Cosmical Container
 * All rights reserved.
 * 
 * this file is created by Cosmical Container 
 * who want to write a Mathematics system with C program.
 * 
 * thanks you for using it. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

void * Matrix_malloc(size_t _Size)
{
    return malloc(_Size);
}

void Matrix_free(void *_Memory)
{
    free(_Memory);
}

void Matrix_Error(char * _Message)
{
    printf("%s\n", _Message);
}

// 创建矩阵
Matrix *createMatrix(int row, int col) 
{
    Matrix *mat = (Matrix*)Matrix_malloc(sizeof(Matrix));

    if( mat == NULL )
    {
        Matrix_Error("createMatrix: create matrix failed");
        exit(-1);
    } 

    mat->row = row;
    mat->col = col;
    mat->data = (float**)Matrix_malloc(row * sizeof(float*));

    if(mat->data == NULL)
    {
        Matrix_Error("createMatrix: create matrix data failed");
        exit(-1);
    }

    for (int i = 0; i < row; i++) 
    {
        mat->data[i] = (float*)Matrix_malloc(col * sizeof(float));
        if(mat->data[i] == NULL)
        {
            Matrix_Error("createMatrix: create matrix data failed");
            exit(-1);
        }
        for (int j = 0; j < col; j++) 
        {
            mat->data[i][j] = 0;
        }
    }
    return mat;
}

Matrix * createUnitMatrix(int dimension)
{
    Matrix *mat = createMatrix(dimension, dimension);

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
Matrix *matrix_init(Matrix * M, int arr[])
{
    Check_NULL_Matrix_return (M);

    for (int i = 0; i < M->row; i++) 
    {
        for (int j = 0; j < M->col; j++) 
        {
            M->data[i][j] = arr[i * M->col + j];
        }
    }
    return M;
}

// 打印矩阵
void printMatrix(Matrix * M)
{
    if(M != NULL)
    {
        for (int i = 0; i < M->row; i++) 
        {
            for (int j = 0; j < M->col; j++) 
            {
                printf("%.2f ",M->data[i][j]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

// 释放矩阵
void destroyMatrix(Matrix **mat) 
{
    if( *mat == NULL )
    {
        return ;
    }

    for (int i = 0; i < (*mat)->row; i++) 
    {
        Matrix_free((*mat)->data[i]);
    }
    Matrix_free((*mat)->data);
    Matrix_free(*mat);
    *mat = NULL;
}

// 矩阵加法
Matrix *matrix_add(Matrix *a, Matrix *b) 
{
    if(a == NULL || b == NULL)
    {
        Matrix_Error("The matrix is NULL!");
        return NULL;
    }

    if (a->row != b->row || a->col != b->col) 
    {
        Matrix_Error("Error: The sizes of two matrices are not equal.\n");
        exit(-1);
    }

    Matrix *mat = createMatrix(a->row, a->col);
    for (int i = 0; i < a->row; i++) 
    {
        for (int j = 0; j < a->col; j++) 
        {
            mat->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return mat;
}

// 矩阵乘法
Matrix *matrix_mul(Matrix *a, Matrix *b) 
{
    if(a == NULL || b == NULL)
    {
        return NULL;
    }

    if (a->col != b->row) 
    {
        Matrix_Error("Error: The sizes of two matrices are not compatible for multiplication.\n");
        exit(-1);
    }

    Matrix *mat = createMatrix(a->row, b->col);
    for (int i = 0; i < a->row; i++) 
    {
        for (int j = 0; j < b->col; j++) 
        {
            for (int k = 0; k < a->col; k++) 
            {
                mat->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return mat;
}

// 矩阵数乘 matrix scalar multiplication
Matrix *matrix_sca_mul(Matrix *M, float k)
{
    Check_NULL_Matrix_return (M)

    for (int i = 0; i < M->row; i++) 
    {
        for (int j = 0; j < M->col; j++) 
        {
            M->data[i][j] *= k;
        }
    }
    return M;
}

// 矩阵数除
Matrix *matrix_sca_div(Matrix *M, float k) 
{
    Check_NULL_Matrix_return (M);

    if(k == 0)
    {
        Matrix_Error("The divisor cannot be 0!");
        return M;
    }

    for (int i = 0; i < M->row; i++) 
    {
        for (int j = 0; j < M->col; j++) 
        {
            M->data[i][j] /= k;
        }
    }

    return M;
}

// 计算矩阵转换为行列式之后的值
float matrix_Det_Cal(Matrix *M)
{
    Check_NULL_Matrix_exit(M);

    if( M->col != M->row )
    {
        Matrix_Error("Error: The matrix is not square!");
        exit(-1);
    }

    return matrix_Det(M, M->col);
}

float matrix_Det(Matrix *M, int x)
{
    int i=0,j=0,s=0,k=0;
    Matrix* c = createMatrix(Det_Max_n, Det_Max_n);  //用c数组来表示余子列
    if(x == 1)
    {
        s = M->data[0][0];
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
                        c->data[i][k]=M->data[i+1][k];
                    if(k>=j)
                        c->data[i][k]=M->data[i+1][k+1];
                }
            }
            s += pow(-1,j) * M->data[0][j] * matrix_Det(c, x-1); //递归算法求出值
            Matrix_free(c);
        }
    }
	return s;
}

// 矩阵转置
Matrix *matrix_transpose(Matrix *mat) 
{
    Check_NULL_Matrix_return(mat);

    Matrix *transpose_mat = createMatrix(mat->col, mat->row);
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
Matrix *matrix_inverse(Matrix *mat) 
{
    Check_NULL_Matrix_return(mat);

    if (mat->row != mat->col) 
    {
        Matrix_Error("Error: matrix not square, can't be inversed.\n");
        return NULL;
    }

    int n = mat->row;
    Matrix* res = createMatrix(n, n * 2);

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
            Matrix_Error("Error: matrix can't be inversed.\n");
            destroyMatrix(&res);
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
    Matrix* inv = createMatrix(n, n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            inv->data[i][j] = res->data[i][n + j];
        }
    }

    // 释放资源
    destroyMatrix(&res);

    return inv;
}

// 矩阵求秩
int matrix_rank(Matrix* mat)
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

