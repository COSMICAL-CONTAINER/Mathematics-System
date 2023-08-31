#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"
#include "string_math.h"
#include "Memmanager.h"

#include <time.h>

typedef enum __Positive_negative
{
    BIS_Positive,
    BIS_Negative
}BigIntergeSign;

typedef struct __BigInterge
{
    BigIntergeSign      sign_member;
    String              num_member;
    unsigned long long  digit_capacity_member;
}BigInterge;
typedef BigInterge* P_BigInterge;

void ERROR(String Inf);

P_BigInterge BigIntergeInit(String num);
void *BigIntergeMalloc(size_t _Size);
void *BigIntergeCalloc(size_t _NumOfElements,size_t _SizeOfElements);
void BigIntergeFree(void *_Memory);

__Bool BigIntergeIsZero(P_BigInterge num);
__Bool BigIntergeIsOne(P_BigInterge num);
__Bool BigIntergeIsPositive(P_BigInterge num);
__Bool BigIntergeIsNegative(P_BigInterge num);
__Bool BigIntergeIsSameSign(P_BigInterge num1, P_BigInterge num2);
__Bool BigIntergeIsOppositeSign(P_BigInterge num1, P_BigInterge num2);

P_BigInterge BigIntergeOpposite(P_BigInterge num);
P_BigInterge BigIntergeOppositeTemp(P_BigInterge num);

void BigIntergePrint(P_BigInterge num);
BI_CmpResult BigIntergeCmp(P_BigInterge num1, P_BigInterge num2);
P_BigInterge BigIntergeAdd(P_BigInterge num1, P_BigInterge num2);
P_BigInterge BigIntergeSub(P_BigInterge num1, P_BigInterge num2);
P_BigInterge BigIntergeMul(P_BigInterge num1, P_BigInterge num2);
P_BigInterge BigIntergeDiv(P_BigInterge num1, P_BigInterge num2);

void BigIntergeDestroy(P_BigInterge num);


void *BigIntergeMalloc(size_t _Size)
{
    return malloc(_Size);
}

void *BigIntergeCalloc(size_t _NumOfElements,size_t _SizeOfElements)
{
    return calloc(_NumOfElements, _SizeOfElements);
}

void BigIntergeFree(void *_Memory)
{
    free(_Memory);
}

void ERROR(String Inf)
{
    printf("%s",Inf);
    exit(-1);
}

void MemCheck(void * _Mem)
{
    if(_Mem == NULL)
    {
        ERROR("NULL Mem");
    }
}

P_BigInterge BigIntergeInit(String num)
{
    int len = strlen(num);
    if (num == NULL || len == 0)
    {
        return NULL;
    }
    
    for(int i = 0 ; i < len; ++i)
    {
        if(i == 0)
        {
            if(num[i] == '-' || num[i] == '+')
            {
                continue;
            }
        }
        if(num[i] < '0' || num[i] > '9')
        {
            return NULL;
        }
    }
    
    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    char now_str[len];
    switch (num[0])
    {
        case '-':
            p->sign_member = BIS_Negative;
            for(int i = 0; i < len; ++i)
            {
                now_str[i] = num[i + 1];
            }
            len--;  //去掉'-'后长度减一
            break;
        case '+':
            p->sign_member = BIS_Positive;

        default:
            p->sign_member = BIS_Positive;
            strcpy(now_str, num);
            break;
    }
    p->num_member = (String)BigIntergeCalloc(len, sizeof(char));
    strcpy(p->num_member, now_str);
    p->digit_capacity_member = len;
    return p;
}

__Bool BigIntergeIsPositive(P_BigInterge num)
{
    return (__Bool)(num->sign_member == BIS_Positive);
}

__Bool BigIntergeIsNegative(P_BigInterge num)
{
    return (__Bool)(num->sign_member == BIS_Negative);
}

__Bool BigIntergeIsSameSign(P_BigInterge num1, P_BigInterge num2)
{
    return (__Bool)(num1->sign_member == num2->sign_member);
}

__Bool BigIntergeIsOppositeSign(P_BigInterge num1, P_BigInterge num2)
{
    return (__Bool)(!((num1->sign_member == num2->sign_member)));
}

__Bool BigIntergeIsZero(P_BigInterge num)
{
    return String_IsZero(num->num_member);
}

__Bool BigIntergeIsOne(P_BigInterge num)
{
    return String_IsOne(num->num_member);
}

P_BigInterge BigIntergeOpposite(P_BigInterge num)
{
    if(num->sign_member == BIS_Positive)
    {
        num->sign_member = BIS_Negative;
    }
    else
    {
        num->sign_member = BIS_Positive;
    }
    return num;
}

P_BigInterge BigIntergeOppositeTemp(P_BigInterge num)
{
    size_t len = strlen(num->num_member);
    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    if(num->sign_member == BIS_Positive)
    {
        p->sign_member = BIS_Negative;
    }
    else
    {
        p->sign_member = BIS_Positive;
    }

    p->num_member = (String)calloc(len, sizeof(char));
    strcpy(p->num_member, num->num_member);
    p->digit_capacity_member = len;
    return p;
}

void BigIntergePrint(P_BigInterge num)
{
    if(num->sign_member == BIS_Negative)
    {
        printf("-%s", num->num_member);
    }
    else
    {
        printf("%s", num->num_member);
    }
}

BI_CmpResult BigIntergeCmp(P_BigInterge num1, P_BigInterge num2)
{
    if(num1->sign_member != num2->sign_member)
    {
        if(num1->sign_member == BIS_Positive)
        {
            return big;
        }
        else
        {
            return small;
        }
    }
    else
    {
        return String_Cmp(num1->num_member, num2->num_member);
    }
}

P_BigInterge BigIntergeAdd(P_BigInterge num1, P_BigInterge num2)
{
    if(num1->sign_member == BIS_Negative && num2->sign_member == BIS_Negative)
    {
        // -a + -b  =>  -(a + b)
        return BigIntergeOpposite(BigIntergeAdd(BigIntergeOppositeTemp(num1),BigIntergeOppositeTemp(num2)));
    }
    else if(num1->sign_member == BIS_Negative && num2->sign_member == BIS_Positive)
    {
        // -a + b  =>  b - a
        return BigIntergeSub(num2, BigIntergeOppositeTemp(num1));
    }
    else if(num1->sign_member == BIS_Positive && num2->sign_member == BIS_Negative)
    {
        // a + -b  =>  a - b
        return BigIntergeSub(num1, BigIntergeOppositeTemp(num2));
    }

    String result = add(num1->num_member, num2->num_member);
    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    p->sign_member = BIS_Positive;
    p->num_member = result;
    p->digit_capacity_member = strlen(result);
    return p;
}

P_BigInterge BigIntergeSub(P_BigInterge num1, P_BigInterge num2)
{
    if(num1->sign_member == BIS_Negative && num2->sign_member == BIS_Negative)
    {
        // -a - -b  =>  b - a
        return BigIntergeSub(BigIntergeOppositeTemp(num2), BigIntergeOppositeTemp(num1));
    }
    else if(num1->sign_member == BIS_Negative && num2->sign_member == BIS_Positive)
    {
        // -a - b  =>  -(a + b)
        return BigIntergeOpposite(BigIntergeAdd(BigIntergeOppositeTemp(num1), num2));
    }
    else if(num1->sign_member == BIS_Positive && num2->sign_member == BIS_Negative)
    {
        // a - -b  =>  a + b
        return BigIntergeAdd(num1, BigIntergeOppositeTemp(num2));
    }

    //保证大数减小数
    if(BigIntergeCmp(num1, num2) == small)
    {
        return BigIntergeOpposite(BigIntergeSub(num2, num1));
    }

    String result;
    result = sub(num1->num_member, num2->num_member);
    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    p->num_member = result;
    p->sign_member = BIS_Positive;
    p->digit_capacity_member = strlen(result);
    return p;
}

P_BigInterge BigIntergeMul(P_BigInterge num1, P_BigInterge num2)
{
    if(BigIntergeIsZero(num1) == True || BigIntergeIsZero(num2) == True)
    {
        return BigIntergeInit("0");
    }

    if(BigIntergeIsOne(num1) == True)
    {
        if(BigIntergeIsPositive(num1))
            return num2;
        else
            return BigIntergeOpposite(num2);
    }
    else if(BigIntergeIsOne(num2) == True)
    {
        if(BigIntergeIsPositive(num2))
            return num1;
        else
            return BigIntergeOpposite(num1);
    }

    String result = mul(num1->num_member, num2->num_member);
    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    if(BigIntergeIsSameSign(num1, num2))
    {
        p->sign_member = BIS_Positive;
    }
    else
    {
        p->sign_member = BIS_Negative;
    }
    p->num_member = result;
    p->digit_capacity_member = strlen(result);
    return p;
}

P_BigInterge BigIntergeDiv(P_BigInterge num1, P_BigInterge num2)
{
    if(BigIntergeIsSameSign(num1, num2))
    {
        if(BigIntergeIsNegative(num1))
            return BigIntergeDiv(BigIntergeOppositeTemp(num1), BigIntergeOppositeTemp(num2));
    }

    if(BigIntergeIsOppositeSign(num1, num2))
    {
        if(BigIntergeIsNegative(num1))
            return BigIntergeOpposite(BigIntergeDiv(BigIntergeOppositeTemp(num1), num2));
        else
            return BigIntergeOpposite(BigIntergeDiv(num1, BigIntergeOppositeTemp(num2)));
    }

    if(BigIntergeIsZero(num1) == True)
    {
        return BigIntergeInit("0");
    }
    else if(BigIntergeIsZero(num2) == True)
    {
        ERROR("BigIntergeDiv():Operand are forbidden!\n");
    }
    else if(BigIntergeIsOne(num2) == True)
    {
        return num1;
    }
    else if(BigIntergeCmp(num1, num2) == equ)
    {
        return BigIntergeInit("1");
    }

    printf("%s / %s = ", num1->num_member, num2->num_member);
    String result = (String)calloc(num1->digit_capacity_member, sizeof(char));
    String remainder = (String)calloc(num1->digit_capacity_member, sizeof(char));

    String_Math_div(num1->num_member, num2->num_member, result, remainder);
    printf("%s ...... %s\n",result, remainder);

    P_BigInterge p = (P_BigInterge)BigIntergeMalloc(sizeof(BigInterge));
    p->sign_member = BIS_Positive;
    p->num_member = result;
    p->digit_capacity_member = strlen(result);
    return p;
}

void BigIntergeDestroy(P_BigInterge num)
{
    BigIntergeFree(num->num_member);
    BigIntergeFree(num);
    return ;
}

int main()
{
    MemManagerInit(100);
    putchar('\n');
    BigIntergeDiv(BigIntergeInit("114514121857865745231233456789"), BigIntergeInit("12345123125654564231236798"));
    putchar('\n');
    char a[100], b[100];
    // 原版使用 gets(a); gets(b); —— gets 已被 C11 移除，这里用等价的 fgets 并去掉末尾换行
    fgets(a, sizeof(a), stdin); a[strcspn(a, "\n")] = '\0';
    fgets(b, sizeof(b), stdin); b[strcspn(b, "\n")] = '\0';
    P_BigInterge P1 = BigIntergeInit(a);
    P_BigInterge P2 = BigIntergeInit(b);

    BigIntergePrint(P1);
    printf(" + ");
    BigIntergePrint(P2);
    printf(" = ");
    BigIntergePrint(BigIntergeAdd(P1, P2));
    putchar('\n');

    BigIntergePrint(P1);
    printf(" - ");
    BigIntergePrint(P2);
    printf(" = ");
    BigIntergePrint(BigIntergeSub(P1, P2));  
    putchar('\n');

    BigIntergePrint(P1);
    printf(" * ");
    BigIntergePrint(P2);
    printf(" = ");
    BigIntergePrint(BigIntergeMul(P1, P2));
    putchar('\n');    
    
    BigIntergePrint(P1);
    printf(" / ");
    BigIntergePrint(P2);
    printf(" = ");
    BigIntergePrint(BigIntergeDiv(P1, P2));
    putchar('\n');

    BigIntergePrint(BigIntergeOpposite(P1));

    MemManagerDestory();
    return 0;
}
