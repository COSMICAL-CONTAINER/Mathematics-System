#ifndef _MARTRIX_H 
#define _MARTRIX_H 

#define Det_Max_n 10

#define Check_NULL_Matrix_return(mat)         if( mat == NULL ){Matrix_Error("The matrix is NULL!");return NULL;}
#define Check_NULL_Matrix_exit(mat)           if( mat == NULL ){Matrix_Error("The matrix is NULL!");exit(-1);}

typedef struct 
{
    int row;
    int col;
    float **data;
}Matrix;

// 矩阵的内存申请与释放函数
void * Matrix_malloc(size_t _Size);
void Matrix_free(void *_Memory);

void Matrix_Error(char * _Message);

// 创建矩阵
Matrix *createMatrix(int row, int col);

// 创建单位矩阵
Matrix *createUnitMatrix(int dimension);

// 初始化矩阵
Matrix *matrix_init(Matrix * M, int arr[]);

// 打印矩阵
void printMatrix(Matrix * M);

// 释放矩阵
void destroyMatrix(Matrix **mat);

// 矩阵加法
Matrix *matrix_add(Matrix *a, Matrix *b);

// 矩阵乘法 matrix multiplication
Matrix *matrix_mul(Matrix *a, Matrix *b);

// 矩阵数乘 matrix scalar multiplication
Matrix *matrix_sca_mul(Matrix *M, float k);

// 矩阵数除
Matrix *matrix_sca_div(Matrix *M, float k);

// 计算行列式 Determinant
float matrix_Det_Cal(Matrix *M);
float matrix_Det(Matrix *M, int x);

// 矩阵转置
Matrix *matrix_transpose(Matrix *mat);

// 矩阵求逆
Matrix *matrix_inverse(Matrix *mat);

// 矩阵求秩
int matrix_rank(Matrix* mat);

#endif _MARTRIX_H 