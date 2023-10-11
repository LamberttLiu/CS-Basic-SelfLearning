#include <stdio.h>

int Insert_sort(int s[], int n) /* 自定义函数 Insert_sort()*/
{
    int i, j;
    for (i = 2; i <= n; i++) // 数组下标从2开始，s[0]做监视哨，s[1]一个数据无可比性
    {
        s[0] = s[i]; // 给监视哨赋值
        j = i - 1;   // 确定要比较元素的最右边位

        while (s[0] < s[j])
        {
            s[j + 1] = s[j]; // 数据右移
            j--;             // 产移向左边一个未比较的数
        }

        s[j + 1] = s[0]; // 在确定的位置插入s[i]
    }
    return 0;
}

int main()
{
    int a[11], i;                   // 定义数组及变量为基木整甩
    printf("input 10 nums:\n");
    for (i = 1; i <= 10; i++)
    {
        scanf("%d", &a[i]);         // 接收从键盘输入的10个数据到数组a中
    }

    printf("original order\n");

    for (i = 1; i < 11; i++) {
        printf("%5d", a[i]);        // 将未排序前的顺序输出
    }

    Insert_sort(a, 10);                  // 调用自定义函数 Insert_sort()
    printf("\n after sort:\n");

    for (i = 1; i < 11; i++) {
        printf("%5d", a[i]);        // 将排序后的数组输出
    }
    printf("\n");
    return 0;
}