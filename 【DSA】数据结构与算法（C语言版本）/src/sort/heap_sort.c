#include <stdio.h>

/* Historical version credited _i_plus_plus_. This version uses the
   1-based, iterative implementation explained in article 30. */
/* 两个孩子子树已是大根堆时，调整以 k 为根的子树。 */
void HeapAdjust(int array[], int k, int n)
{
    int value = array[k];
    while (k <= n / 2) {
        int child = 2 * k;
        if (child < n && array[child] < array[child + 1]) {
            ++child;
        }
        if (value >= array[child]) {
            break;
        }
        array[k] = array[child];
        k = child;
    }
    array[k] = value;
}

void BuildMaxHeap(int array[], int n)
{
    for (int k = n / 2; k >= 1; --k) {
        HeapAdjust(array, k, n);
    }
}

/* 实际元素位于 array[1..n]，array[0] 不参与排序。 */
void HeapSort(int array[], int n)
{
    if (n < 2) {
        return;
    }
    BuildMaxHeap(array, n);
    for (int end = n; end > 1; --end) {
        int temp = array[1];
        array[1] = array[end];
        array[end] = temp;
        HeapAdjust(array, 1, end - 1);
    }
}

int main(void)
{
    int array[] = {0, 87, 53, 65, 45, 17, 32, 9, 1};
    int n = (int)(sizeof array / sizeof array[0]) - 1;

    HeapSort(array, n);
    for (int i = 1; i <= n; ++i) {
        printf("%s%d", i == 1 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
