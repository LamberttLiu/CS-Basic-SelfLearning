#include <stdio.h>

int Partition(int array[], int low, int high)
{
    // 把第一个元素当作枢轴
    int pivot = array[low];

    // 用low、high搜索枢轴的最终位置，
    // 当low 与 high 相碰的时候和或者 low 溢出 high 的时候结束
    while (low < high)
    {
        // 比枢轴小的元素移动到左端
        while (low < high && array[high] >= pivot)
        {
            high--;
        }
        array[low] = array[high];
        
        // 比枢轴大的元素移动到右端
        while (low < high && array[low] <= pivot)
        {
            low++;
        }
        array[high] = array[low];
    }
    array[low] = pivot;
    return low;
}

// 快速排序
void QuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(array, low, high);
        QuickSort(array, low, pivot - 1);
        QuickSort(array, pivot + 1, high);
    }
}

/**************************************************
 *函数名：display
 *作用：打印数组元素
 *参数：array - 打印的数组，maxlen - 数组元素个数
 *返回值：无
 **************************************************/
void display(int array[], int maxlen)
{
    int i;

    for (i = 0; i < maxlen; i++)
    {
        printf("%-3d", array[i]);
    }
    printf("\n");

    return;
}


int main()
{
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int low = 0, high = 7;

    QuickSort(array, low, high);
    display(array, sizeof(array) / sizeof(array[0]));
}