#include <stdio.h>

#define true 1
#define false 0
typedef long int ll;
void float_to_Fractional(double data_float, ll circle_body);

int main()
{
    float_to_Fractional(0.123123123,123);
    return 0;
}

void float_to_Fractional(double data_float, ll circle_body)
{
    const static int pow_ten[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000, 1000000000};
    //0.123,123 => 123/(1000 - 1);
    //0.228,8   => 228.8 - 22.8   (1000x - 100x)  鐩鐨勬槸涓轰簡娑堥櫎鏃犻檺寰鐜灏忔暟
    //寰鐜浣撶殑鏁板瓧涓鏁
    int circle_body_count = 0;
    //寰鐜灏忔暟鍓嶉潰涓嶅惊鐜鐨勬暟瀛楃殑涓鏁
    int float_front;
    ll circle_body_temp = circle_body;

    ll temp = data_float * 1000000000;
    printf("%ld\n",temp);

    while(circle_body_temp)
    {
        
        circle_body_temp /= 10;
        circle_body_count++;
    }

    char float_num[10] = {0};
    char circle_num[10] = {0};
    int i = 0;
    printf("num : %ld  count : %d\n",circle_body, circle_body_count);
    for(int j = circle_body_count - 1; j >= 0; j--)
    {
        circle_num[i++] = (circle_body / pow_ten[j]) % 10;
    }
    i = 0;
    for(int j = 8; j >= 0; j--)
    {
        float_num[i++] = (temp / pow_ten[j]) % 10;
    }

    i = 0;
    while(i < 10)
    {
        printf("%d ",float_num[i++]);
    }        
    printf("\n");
    i = 0;
    while(i < 10)
    {
        printf("%d ",circle_num[i++]);
    }
    printf("\n");

    char flag = false;
    float_front = 0;
    for(int j = 0; j < 10; ++j)
    {
        //绗涓娆＄浉绛夋垜浠灏卞紑濮嬭板綍闀垮害
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
    printf("data_float: %f ciclr_count: %d\n", data_float, circle_body_count);
    printf("float_front : %d\n", float_front);

    int temp1 = data_float * pow_ten[float_front + circle_body_count];
    int temp2 = data_float * pow_ten[float_front];
    printf("%d - %d\n",temp1, temp2);

    printf("%d/%d\n", temp1-temp2 ,pow_ten[float_front + circle_body_count] - pow_ten[float_front]);
}
