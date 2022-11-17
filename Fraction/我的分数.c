#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MAX_POOL_NUM 100

//ll的范围也就-1410065407 ~ 1410065408   10^9 < ~ < 10^10
typedef long long ll;

typedef struct my_Fractional
{
    ll Numerator;   //分子
    ll Denominator; //分母
}Fractional;


typedef struct my_Fractional* ptr_Fractional;

ptr_Fractional malloc_space[MAX_POOL_NUM];

void * my_malloc_temp(size_t _Size);
void * my_malloc(size_t _Size);
void my_free();

void exchang(ll *A, ll *B);

ll gcd(ll x, ll y);
void Fractional_init(ptr_Fractional Fractional,ll Numerator, ll Denominator);
void Fractional_print(ptr_Fractional Fractional, int flag);

ptr_Fractional Fractional_temp(ll Numerator, ll Denominator);

//float_to_Fractional
ptr_Fractional float_to_Fractional(double data_float, ll circle_body);

//base opertor
ptr_Fractional Fractional_opposite(ptr_Fractional Fractional);    //取相反数  1/2 -> -1/2
ptr_Fractional Fractional_reciprocal(ptr_Fractional Fractional);  //取倒数    1/2 -> 2/1

//addtion
ptr_Fractional Fractional_add_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2);
ptr_Fractional Fractional_add(int n, ...);

//subtraction
ptr_Fractional Fractional_sub_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2);
ptr_Fractional Fractional_sub(int n, ...);

//multiplication
ptr_Fractional Fractional_mcl_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2);
ptr_Fractional Fractional_mcl(int n, ...);

//division
ptr_Fractional Fractional_div_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2);
ptr_Fractional Fractional_div(int n, ...);

//pow
ll long_integer_pow(ll x, int n);
ptr_Fractional Fractional_pow(ptr_Fractional Fractional,int n);

//calculate
ptr_Fractional Fractional_calc(const char *, ... );

int main()
{
    // Fractional Fractional_1,Fractional_2,Fractional_3;
    // Fractional_init(&Fractional_1,1,10);
    // Fractional_init(&Fractional_2,2,10);
    // Fractional_init(&Fractional_3,15,10);
    // Fractional_print(Fractional_add_2(&Fractional_1,&Fractional_2),true);
    // Fractional_print(Fractional_add(3, &Fractional_1, &Fractional_2, &Fractional_3),true);
    // Fractional_print(Fractional_div(3, &Fractional_3, &Fractional_2, &Fractional_1),true);
    // Fractional_print(&Fractional_1,true);
    // Fractional_print(&Fractional_2,true);
    // Fractional_print(&Fractional_3,true);
    // Fractional_print(float_to_Fractional(0.125),true);
    // ptr_Fractional temp = Fractional_temp(1,2);
    // printf("|%p|\n",temp);
    // Fractional_print(temp,true);
    Fractional_print(float_to_Fractional(0.1123, 123),true);
    Fractional_print(float_to_Fractional(0.12345, 0),true);
    my_free();
    return 0;
}

void * my_malloc_temp(size_t _Size)
{
    static int malloc_space_i = 0;
    //第一次调用先初始化
    if(malloc_space_i == 0)
    {
        for(int i = 0 ; i < MAX_POOL_NUM; ++i)
        {
            malloc_space[i] = NULL;
        }
    }
    ptr_Fractional result = (ptr_Fractional)malloc(_Size);
    malloc_space[malloc_space_i++] = result;
    return (void *)result;
}

void * my_malloc(size_t _Size)
{
    return malloc(_Size);
}

void my_free()
{
    for(int i = 0 ; i < MAX_POOL_NUM; ++i)
    {
        if(malloc_space[i] != NULL)
        {
            //printf("free:|%p|\n",malloc_space[i]);
            free(malloc_space[i]);
        }
    }
}

ll gcd(ll x, ll y)
{
    return !y ? x : gcd(y, x % y);
}

void Fractional_init(ptr_Fractional Fractional,ll Numerator, ll Denominator)
{
    if(Denominator == 0)
    {
        printf("error : 分母不能为0!");
        exit(0);
    }
    else if(Denominator < 0)
    {
        //这里有两重含义->分子分母同时小于0 && 分子大于0分母小于0 处理方法都一样
        Numerator = -Numerator;
        Denominator = -Denominator;
    }
    //求公因数
    ll common_factor = gcd(Numerator, Denominator);
    Fractional->Numerator = Numerator / common_factor;
    Fractional->Denominator = Denominator / common_factor;
}

/**
 * @brief flag表示是否输出有空行
 * 
 * @param Fractional 
 * @param flag 
 */
void Fractional_print(ptr_Fractional Fractional, int flag)
{
    printf("%d/%d",Fractional->Numerator,Fractional->Denominator);
    if(flag)
    {
        putchar('\n');
    }
}

ptr_Fractional Fractional_temp(ll Numerator, ll Denominator)
{
    ptr_Fractional result = (ptr_Fractional)my_malloc_temp(sizeof(Fractional));
    result->Numerator = Numerator;
    result->Denominator = Denominator;
    return result;
}

void exchang(ll *A, ll *B)
{
    *A = *B - *A;
    *B = *B - *A;
    *A = *B + *A;
}

ptr_Fractional float_to_Fractional(double data_float, ll circle_body)
{
    const static int pow_ten[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000, 1000000000};
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    if( circle_body < 0)
    {
        exit(0);
    }

    if( !circle_body )
    {
        ll num = 100000000;
        Fractional_init(result, (ll)(data_float * num), num);
    }
    else
    {
        //0.123,123 => 123/(1000 - 1);
        //0.228,8   => 228.8 - 22.8   (1000x - 100x)  目的是为了消除无限循环小数
        //循环体的数字个数
        int circle_body_count = 0;
        //循环小数前面不循环的数字的个数
        int float_front;
        ll circle_body_temp = circle_body;

        ll temp = data_float * 1000000000;

        while(circle_body_temp)
        {
            circle_body_temp /= 10;
            circle_body_count++;
        }

        char float_num[10] = {0};
        char circle_num[10] = {0};
        int i = 0;

        for(int j = circle_body_count - 1; j >= 0; j--)
        {
            circle_num[i++] = (circle_body / pow_ten[j]) % 10;
        }
        i = 0;
        for(int j = 8; j >= 0; j--)
        {
            float_num[i++] = (temp / pow_ten[j]) % 10;
        }

        char flag = false;
        float_front = 0;
        for(int j = 0; j < 10; ++j)
        {
            //第一次相等我们就开始记录长度
            if(float_num[j] == circle_num[0] && flag == false)
            {
                flag = true;
            }

            if( flag )
            {
                char flag_circle = true;
                int circle_num_i = 0;
                for(int k = j; k < j + circle_body_count; k++)
                {
                    if(float_num[k] != circle_num[circle_num_i++])
                    {
                        flag_circle = false;
                    }
                }
                if( flag_circle )
                {
                    float_front = j;
                    break;
                }
                else
                {
                    flag = false;
                }
            }
        }

        int temp1 = data_float * pow_ten[float_front + circle_body_count];
        int temp2 = data_float * pow_ten[float_front];
        //printf("%d/%d\n", temp1-temp2 ,pow_ten[float_front + circle_body_count] - pow_ten[float_front]);
        Fractional_init(result, temp1-temp2, pow_ten[float_front + circle_body_count] - pow_ten[float_front]);
    }
    return result;
}

ptr_Fractional Fractional_opposite(ptr_Fractional Fractional)    //取相反数  1/2 -> -1/2
{
    Fractional->Numerator = -Fractional->Numerator;
    return Fractional;
}

ptr_Fractional Fractional_reciprocal(ptr_Fractional Fractional)  //取倒数    1/2 -> 2/1
{
    //如果是分子已经是小于0的时候 这时候交换就会出现 1/-2 不太好看的情况所以先把-号弄去
    if(Fractional->Numerator < 0)
    {
        Fractional->Numerator = -Fractional->Numerator;
        Fractional->Denominator = -Fractional->Denominator;
    }
    exchang(&(Fractional->Numerator),&(Fractional->Denominator));
    return Fractional;
}

//标准两个分数相加
ptr_Fractional Fractional_add_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2)
{
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));

    ll Denominator_New = Fractional_1->Denominator * Fractional_2->Denominator;
    ll Numerator_New = Fractional_1->Denominator * Fractional_2->Numerator + Fractional_2->Denominator * Fractional_1->Numerator;
    
    //求公因数
    ll common_factor = gcd(Numerator_New, Denominator_New);
    result->Numerator = Numerator_New / common_factor;
    result->Denominator = Denominator_New / common_factor;

    return result;
}

ptr_Fractional Fractional_add(int n, ...)
{
    int i;
    va_list valist;

    ptr_Fractional ptr_Fractional_temp = NULL;
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    Fractional result_temp;

    result->Denominator = 1;
    result->Numerator = 0;

    //初始化参数列表；
    va_start(valist, n);

    //读取参数列表
    for(i = 0; i < n; i++)
    {
        ptr_Fractional_temp =  va_arg(valist, ptr_Fractional);
        result = Fractional_add_2(ptr_Fractional_temp,result);
        //下面主要就是要free掉内存，防止溢出
        result_temp.Denominator = result->Denominator;
        result_temp.Numerator = result->Numerator;
        free(result);   //实际上free的是Fractional_add_2内部动态申请的内存哦
        result = &result_temp;
    }

    //清理参数内存
    va_end(valist);
    return result;
}

//标准两个数相减
ptr_Fractional Fractional_sub_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2)
{
    //因为Fractional_opposite变成相反数是连值一起改变的，所以需要操作两遍反过来
    Fractional temp;   
    Fractional_opposite(Fractional_2);
    temp = *Fractional_2;   //相同类型的结构体可以这样赋值捏
    Fractional_opposite(Fractional_2);
    return Fractional_add_2(Fractional_1,&temp);
}

/**
 * @brief 先输入要操作的个数，然后用第一个分数减去后面所有的分数 eg f(3,3/3,1/3/1/3) = 3/3-1/3-1/3
 * 
 * @param n 
 * @param fist
 * @param ... 
 * @return ptr_Fractional 
 */
ptr_Fractional Fractional_sub(int n, ...)
{
    int i;
    va_list valist;

    ptr_Fractional ptr_Fractional_temp = NULL;
    ptr_Fractional first;
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    Fractional result_temp;

    //初始化参数列表；
    va_start(valist, n);

    first = va_arg(valist, ptr_Fractional);

    //这里将要运行加法,要有个初始值为0
    result->Numerator = 0;
    result->Denominator = 1;
    //读取参数列表 记得前面已经读取了一个了
    for(i = 1; i < n; i++)
    {
        ptr_Fractional_temp =  va_arg(valist, ptr_Fractional);
        result = Fractional_add_2(result,ptr_Fractional_temp);
        //下面主要就是要free掉内存，防止溢出
        result_temp.Denominator = result->Denominator;
        result_temp.Numerator = result->Numerator;
        free(result);   //实际上free的是Fractional_add_2内部动态申请的内存哦
        result = &result_temp;
    }
    
    result = Fractional_sub_2(first,result);
    //清理参数内存
    va_end(valist);
    return result;
}

//标准两个数相乘
ptr_Fractional Fractional_mcl_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2)
{
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));

    ll Denominator_New = Fractional_1->Denominator * Fractional_2->Denominator;
    ll Numerator_New = Fractional_1->Numerator * Fractional_2->Numerator;
    
    Fractional_init(result, Numerator_New, Denominator_New);

    return result;
}

ptr_Fractional Fractional_mcl(int n, ...)
{
    int i;
    va_list valist;

    ptr_Fractional ptr_Fractional_temp = NULL;
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    Fractional result_temp;

    result->Denominator = 1;
    result->Numerator = 1;

    //初始化参数列表；
    va_start(valist, n);

    //读取参数列表
    for(i = 0; i < n; i++)
    {
        ptr_Fractional_temp =  va_arg(valist, ptr_Fractional);
        result = Fractional_mcl_2(ptr_Fractional_temp,result);
        //下面主要就是要free掉内存，防止溢出
        result_temp.Denominator = result->Denominator;
        result_temp.Numerator = result->Numerator;
        free(result);   //实际上free的是Fractional_add_2内部动态申请的内存哦
        result = &result_temp;
    }

    //清理参数内存
    va_end(valist);
    return result;
}

//标准两个数相除
ptr_Fractional Fractional_div_2(ptr_Fractional Fractional_1, ptr_Fractional Fractional_2)
{
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    ptr_Fractional temp;

    //先把后面的取倒数,然后计算乘法
    temp = Fractional_reciprocal(Fractional_2);
    result = Fractional_mcl_2(Fractional_1, temp);
    //别忘了倒回来
    Fractional_reciprocal(Fractional_2);
    
    Fractional_init(result, result->Numerator, result->Denominator);

    return result;
}
ptr_Fractional Fractional_div(int n, ...)
{
    int i;
    va_list valist;

    ptr_Fractional ptr_Fractional_temp = NULL;
    ptr_Fractional result = (ptr_Fractional)my_malloc(sizeof(Fractional));
    Fractional result_temp;

    //初始化参数列表；
    va_start(valist, n);
    if(n < 1)
    {
        //Error("别搞");
        return NULL;
    }
    else if(n == 1)
    {
        return va_arg(valist, ptr_Fractional);
    }
    ptr_Fractional ptr_Fractional_first = va_arg(valist, ptr_Fractional);
    ptr_Fractional ptr_Fractional_second = va_arg(valist, ptr_Fractional);
    result = Fractional_div_2(ptr_Fractional_first,ptr_Fractional_second);
    //读取参数列表
    for(i = 2; i < n; i++)
    {
        ptr_Fractional_temp =  va_arg(valist, ptr_Fractional);
        result = Fractional_div_2(result, ptr_Fractional_temp);
        //下面主要就是要free掉内存，防止溢出
        result_temp.Denominator = result->Denominator;
        result_temp.Numerator = result->Numerator;
        free(result);   //实际上free的是Fractional_div_2内部动态申请的内存哦
        result = &result_temp;
    }

    //清理参数内存
    va_end(valist);
    return result;
}

//计算分数的乘方
ll long_integer_pow(ll x, int n)
{
    ll r = 1;
    while (n--)
    {
       r *= x;
    }
    return r; 
}

ptr_Fractional Fractional_pow(ptr_Fractional Fractional, int n)
{
    Fractional->Denominator = long_integer_pow(Fractional->Denominator, n);
    Fractional->Numerator = long_integer_pow(Fractional->Numerator, n);
    Fractional_init(Fractional,Fractional->Denominator, Fractional->Numerator);
    return Fractional;
}

ptr_Fractional Fractional_calc(const char * str, ... )
{
    ;
}
