#include <string.h>
#include <stdlib.h>
#include "my_string.h"
#include "string_math.h"

String Int_to_String(long long num)
{
    int temp = num;
	int count = 1;
	while(temp)
	{
		temp /= 10;
		count++;
	}
    String str = (String)malloc(sizeof(char) * count);
    itoa(num,str,10);
	return str;
}

BI_CmpResult String_Cmp(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    if(len1 > len2)
    {
        return big;
    }
    else if(len2 > len1)
    {
        return small;
    }
    else
    {
        return (BI_CmpResult)strcmp(num1, num2);
    }
}

__Bool String_IsZero(String num)
{
    if(num[0] == '0' && strlen(num) == 1)
    {
        return True;
    }
    return False;
}

__Bool String_IsOne(String num)
{
    if(num[0] == '1' && strlen(num) == 1)
    {
        return True;
    }
    return False;
}

String add(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    char num1str[len1 + 1 + 1];//一个1是最前面加多一个0 还有一个1是储存最后的'\0'
    char num2str[len2 + 1 + 1];
    for(int i = len1 - 1; i >= 0; i--)
    {
        num1str[len1 - i - 1] = num1[i];
    }
    num1str[len1] = '0';
    num1str[len1 + 1] = '\0';

    for(int i = len2 - 1; i >= 0; i--)
    {
        num2str[len2 - i - 1] = num2[i];
    }
    num2str[len2] = '0';
    num2str[len2 + 1] = '\0';

    //printf("%s-%s\n",num1str, num2str);
    int min_size = len1 > len2 ? len2 : len1;
    int max_size = len1 > len2 ? len1 : len2;
    String result = (String)malloc(sizeof(char) * (max_size + 1 + 1));
    int tempnum = 0, carry_bit = 0;
    for(int ix = 0; ix < min_size; ix++)
    {
        tempnum = (num1str[ix] - '0') + (num2str[ix] - '0') + carry_bit;
        if(tempnum >= 10)
        {
            tempnum = tempnum - 10;
            carry_bit = 1;
        }
        else
        {
            carry_bit = 0;
        }
        
        result[ix] = tempnum + '0';
    }
    if(len1 >= len2)
    {
        for(int ix = min_size; ix < max_size; ix++)
        {
            if(num1str[ix] + carry_bit <= '9')
            {
                result[ix] = num1str[ix] + carry_bit;
                carry_bit = 0;
            }
            else
            {
                result[ix] = num1str[ix] + carry_bit - 10;
                carry_bit = 1;
            }
        }
    }
    else
    {
        for(int ix = min_size; ix < max_size; ix++)
        {
            // result[ix] = num2str[ix] + carry_bit;
            // carry_bit = 0;
            if(num2str[ix] + carry_bit <= '9')
            {
                result[ix] = num2str[ix] + carry_bit;
                carry_bit = 0;
            }
            else
            {
                result[ix] = num2str[ix] + carry_bit - 10;
                carry_bit = 1;
            }
        }
    }

    if(carry_bit == 1)
    {
        result[max_size] = carry_bit + '0';
        result[max_size + 1] = '\0';
        //翻转数组
        for(int i = 0; i <= max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i];
            result[max_size - i] = tempnum;
        }
    }
    else
    {
        result[max_size] = '\0';
        //翻转数组
        for(int i = 0; i < max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i - 1];
            result[max_size - i - 1] = tempnum;
        }
    }

    return result;
}

String add_change(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    char num1str[len1 + 1 + 1];//一个1是最前面加多一个0 还有一个1是储存最后的'\0'
    char num2str[len2 + 1 + 1];
    for(int i = len1 - 1; i >= 0; i--)
    {
        num1str[len1 - i - 1] = num1[i];
    }
    num1str[len1] = '0';
    num1str[len1 + 1] = '\0';

    for(int i = len2 - 1; i >= 0; i--)
    {
        num2str[len2 - i - 1] = num2[i];
    }
    num2str[len2] = '0';
    num2str[len2 + 1] = '\0';

    //printf("%s-%s\n",num1str, num2str);
    int min_size = len1 > len2 ? len2 : len1;
    int max_size = len1 > len2 ? len1 : len2;
    char result[max_size + 1 + 1];
    int tempnum = 0, carry_bit = 0;
    for(int ix = 0; ix < min_size; ix++)
    {
        tempnum = (num1str[ix] - '0') + (num2str[ix] - '0') + carry_bit;
        if(tempnum >= 10)
        {
            tempnum = tempnum - 10;
            carry_bit = 1;
        }
        else
        {
            carry_bit = 0;
        }
        
        result[ix] = tempnum + '0';
    }
    if(len1 >= len2)
    {
        for(int ix = min_size; ix < max_size; ix++)
        {
            if(num1str[ix] + carry_bit <= '9')
            {
                result[ix] = num1str[ix] + carry_bit;
                carry_bit = 0;
            }
            else
            {
                result[ix] = num1str[ix] + carry_bit - 10;
                carry_bit = 1;
            }
        }
    }
    else
    {
        for(int ix = min_size; ix < max_size; ix++)
        {
            // result[ix] = num2str[ix] + carry_bit;
            // carry_bit = 0;
            if(num2str[ix] + carry_bit <= '9')
            {
                result[ix] = num2str[ix] + carry_bit;
                carry_bit = 0;
            }
            else
            {
                result[ix] = num2str[ix] + carry_bit - 10;
                carry_bit = 1;
            }
        }
    }

    if(carry_bit == 1)
    {
        result[max_size] = carry_bit + '0';
        result[max_size + 1] = '\0';
        //翻转数组
        for(int i = 0; i <= max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i];
            result[max_size - i] = tempnum;
        }
    }
    else
    {
        result[max_size] = '\0';
        //翻转数组
        for(int i = 0; i < max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i - 1];
            result[max_size - i - 1] = tempnum;
        }
    }
    strcpy(num1, result);
    return num1;
}

String sub(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    if(len1 == len2)
    {
        if(strcmp(num1, num2) == 0)
        {
            String result = (String)malloc(2 * sizeof(char));
            strcpy(result, "0");
            return result;
        }
    }    
    if( len1 >= len2)
    {
        char num1str[len1 + 1];
        char num2str[len2 + 1];
        for(int i = len1 - 1; i >= 0; i--)
        {
            num1str[len1 - i - 1] = num1[i];
        }
        num1str[len1] = '\0';

        for(int i = len2 - 1; i >= 0; i--)
        {
            num2str[len2 - i - 1] = num2[i];
        }
        num2str[len2] = '\0';

        int min_size = len1 > len2 ? len2 : len1;
        int max_size = len1 > len2 ? len1 : len2;
        String result = (String)malloc(sizeof(char) * (max_size + 1));
        int tempnum = 0, carry_bit = 0;
        for(int ix = 0; ix < min_size; ix++)
        {
            tempnum = (num1str[ix] - '0') - (num2str[ix] - '0') + carry_bit;
            if(tempnum < 0)
            {
                tempnum = tempnum + 10;
                carry_bit = -1;
            }
            else
            {
                carry_bit = 0;
            }
            
            result[ix] = tempnum + '0';
        }

        for(int ix = min_size; ix <= max_size; ix++)
        {
            result[ix] = num1str[ix] + carry_bit;
            if(result[ix] < '0')
            {
                carry_bit = -1;
                result[ix] += 10;
            }
            else
            {
                carry_bit = 0;
            }
        }
        
        //判断最后一位是0
        if(result[max_size - 1] == '0')
        {
            result[max_size - 1] = '\0';
            max_size--;
        }

        //翻转数组
        for(int i = 0; i < max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i - 1];
            result[max_size - i - 1] = tempnum;
        }
        result[max_size] = '\0';
        return result;
    }
    return "";
}

String sub_change(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    if(len1 == len2)
    {
        if(strcmp(num1, num2) == 0)
        {
            strcpy(num1, "0");
            return num1;
        }
    }    
    if( len1 >= len2)
    {
        char num1str[len1 + 1];
        char num2str[len2 + 1];
        for(int i = len1 - 1; i >= 0; i--)
        {
            num1str[len1 - i - 1] = num1[i];
        }
        num1str[len1] = '\0';

        for(int i = len2 - 1; i >= 0; i--)
        {
            num2str[len2 - i - 1] = num2[i];
        }
        num2str[len2] = '\0';

        int min_size = len1 > len2 ? len2 : len1;
        int max_size = len1 > len2 ? len1 : len2;
        char result[max_size + 1];
        int tempnum = 0, carry_bit = 0;
        for(int ix = 0; ix < min_size; ix++)
        {
            tempnum = (num1str[ix] - '0') - (num2str[ix] - '0') + carry_bit;
            if(tempnum < 0)
            {
                tempnum = tempnum + 10;
                carry_bit = -1;
            }
            else
            {
                carry_bit = 0;
            }
            
            result[ix] = tempnum + '0';
        }

        for(int ix = min_size; ix <= max_size; ix++)
        {
            result[ix] = num1str[ix] + carry_bit;
            if(result[ix] < '0')
            {
                carry_bit = -1;
                result[ix] += 10;
            }
            else
            {
                carry_bit = 0;
            }
        }
        
        //判断最后一位是0
        if(result[max_size - 1] == '0')
        {
            result[max_size - 1] = '\0';
            max_size--;
        }

        //翻转数组
        for(int i = 0; i < max_size / 2; ++i)
        {
            tempnum = result[i];
            result[i] = result[max_size - i - 1];
            result[max_size - i - 1] = tempnum;
        }
        result[max_size] = '\0';
        return strcpy(num1, result);
    }
    return "";
}

String mul(String num1, String num2)
{
    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    int temp[len1 + len2];
    String result = (String)calloc(len1 + len2 + 1, sizeof(char));
    for(int i = 0; i < len1 + len2; ++i)
    {
        temp[i] = 0;
    }

    for(int i = 0; i < len1; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    
    for (int i = len1 + len2 - 1; i >= 0; --i)
    {
        //printf("%d ", temp[i]);
        if((temp[i]) >= 10)
        {
            temp[i - 1] += (temp[i]) / 10;
            temp[i] %= 10;
        }
        result[i] = temp[i] + '0';
    }

    //如果最前面还有0的话得去掉
    if(result[0] == '0')
    {
        for(int i = 0; i < len1 + len2; ++i)
        {
            result[i] = result[i + 1];
        }
    }
    //最后结尾加上结束符
    result[len1 + len2] = '\0';
    return result;
}

String mul_change(String num1, String num2)
{
    if(String_IsZero(num1) == True || String_IsZero(num2) == True)
    {
        strcpy(num1, "0");
        return num1;
    }

    if(String_IsOne(num1) == True)
    {
        strcpy(num1, num2);
        return num2;
    }
    else if(String_IsOne(num2) == True)
    {
        return num1;
    }

    long long len1 = strlen(num1);
    long long len2 = strlen(num2);
    int temp[len1 + len2];
    char result[len1 + len2 + 1];
    for(int i = 0; i < len1 + len2; ++i)
    {
        temp[i] = 0;
    }

    for(int i = 0; i < len1; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    
    for (int i = len1 + len2 - 1; i >= 0; --i)
    {
        //printf("%d ", temp[i]);
        if((temp[i]) >= 10)
        {
            temp[i - 1] += (temp[i]) / 10;
            temp[i] %= 10;
        }
        result[i] = temp[i] + '0';
    }

    //如果最前面还有0的话得去掉
    if(result[0] == '0')
    {
        for(int i = 0; i < len1 + len2; ++i)
        {
            result[i] = result[i + 1];
        }
    }
    //最后结尾加上结束符
    result[len1 + len2] = '\0';
    strcpy(num1, result);
    return num1;
}

__Bool String_Math_div(String num1, String num2, String result, String remainder) //余数
{
    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);
    long long max_move = len1 - len2;
    size_t times = 0;
    char num1str[len1];
    char num2str[len2];
    strcpy(num1str, num1);
    strcpy(num2str, num2);
    
    //printf("%s\n", num1str);
    //判断能不能第一位就对齐，不行的话max_move最大移动位数就要-1
    // if(num1str[0] < num2str[0])
    // {
    //     max_move--;
    //     putchar(' ');
    // }
    //printf("%s\n", num2str);
    //printf("max_move:%d\n", max_move);

    String result_ = (String)calloc(len1, sizeof(char));
    result_[0] = '0';
    String temp = (String)calloc(len1, sizeof(char));
    temp[0] = '1';
    for(; max_move>=0; max_move--)
    {
        if(String_Cmp(num1str, num2str) >= 0)
        {
            //除数num2左移counts位时,num1最多能减去num2的次数times
            String now_num2str = String_Addxchar_temp(num2str, max_move, '0');
            for(times = 0; times < 1000 && ( String_Cmp(num1str, now_num2str) >= 0 ); times++)
            {
                sub_change(num1str, now_num2str);
            }
            for(int i = 1; i <= max_move; i++)
            {
                String_AddChar(temp, '0');
            }
            strcpy(temp, mul(Int_to_String(times), temp));
            add_change(result_, temp);
            for(int i = 0; i < len1; ++i)
            {
                temp[i] = 0;
            }
            temp[0] = '1';
        //除数num2左移counts位时,被除数最多能减去除数t=times*(10^counts)次：
        }
    }
    strcpy(result, result_);
    strcpy(remainder, num1str);
    return True;
}
