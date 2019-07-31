#include "iostream"
#include "stdio.h"
#include "string.h"
#include "time.h"

#include <stdlib.h>

int NUM=5;//总数
int COUNT=0;//重复数个数初始值，不含原数

int main()
{
    int array[NUM] = {0};
    for (int i = 0; i < NUM; i++)
    {
        int temp=5;
        if ((NUM - i) > 1)
            printf("Input %dth number!\n", (NUM - i));
        else
            printf("Input %d more number!\n", (NUM - i));
        scanf("%d", &temp);
        array[i] = temp;
    }

    // int target=9;
    // for (int i = 0; i < NUM - 1; i++)
    // {
    //     for (int j = i + 1; j < NUM; j++)
    //     {
    //         if (target == array[i] + array[j])
    //         {
    //             printf("[%d,%d]\t", i, j);
    //         }
    //     }
    // }

    for (int j = 0; j < NUM - COUNT; j++)
    {
        for (int k = j + 1; k < NUM - COUNT; k++)
        {
            if (array[j] == array[k])
            {
                for (int l = k + 1; l < NUM - COUNT; l++)
                {
                    array[l-1] = array[l];
                    //array[l]=0;
                }
                k--;
                COUNT += 1;
            }
        }
    }
    int *p = (int *)malloc((NUM - COUNT) * sizeof(int));
    memcpy(p, array, (NUM - COUNT) * sizeof(int));
    if (1<COUNT)
        printf("When the %d duplicate numbers are removed:\n",COUNT);
    else if(1==COUNT)
        printf("When the duplicate number is removed:\n");
    else
        printf("There is no duplicate number:\n");
    for (int i = 0; i < NUM - COUNT; i++)
    {
        //*(p+i)=array[i];
        printf("-> %d", *(p + i));
    }
    printf("\n");
    free(p);
    p = NULL;
    system("pause");
    return 0;
}