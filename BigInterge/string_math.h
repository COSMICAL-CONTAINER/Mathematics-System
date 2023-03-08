#ifndef _String_Math_H
#define _String_Math_H

typedef enum __BigInterge_Cmp
{
    small = -1,
    equ,
    big
}BI_CmpResult;

typedef enum _bool
{
    False,
    True
} __Bool;


String Int_to_String(long long num);
BI_CmpResult String_Cmp(String num1, String num2);

__Bool String_IsZero(String num);
__Bool String_IsOne(String num);

String add(String num1, String num2);
String add_change(String num1, String num2);

String sub(String num1, String num2);
String sub_change(String num1, String num2);


String mul(String num1, String num2);
String mul_change(String num1, String num2);

__Bool String_Math_div(String num1, String num2, String result, String remainder); //余数
#endif // _String_Math_H
