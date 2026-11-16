#include <stdio.h>

/* 划分非空闭区间 [low, high]，返回枢轴的最终下标。 */
int Partition(int array[], int low, int high)
{
    int pivot = array[low];

    while (low < high) {
        while (low < high && array[high] >= pivot) {
            --high;
        }
        array[low] = array[high];

        while (low < high && array[low] <= pivot) {
            ++low;
        }
        array[high] = array[low];
    }
    array[low] = pivot;
    return low;
}

void QuickSort(int array[], int low, int high)
{
    if (low < high) {
        int pivotPos = Partition(array, low, high);
        QuickSort(array, low, pivotPos - 1);
        QuickSort(array, pivotPos + 1, high);
    }
}

int main(void)
{
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = (int)(sizeof array / sizeof array[0]);

    QuickSort(array, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%s%d", i == 0 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
