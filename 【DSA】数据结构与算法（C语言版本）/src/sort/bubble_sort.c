#include <stdbool.h>
#include <stdio.h>

/* 升序排序；n >= 0，n >= 2 时 array 指向至少 n 个可写元素。 */
void BubbleSort(int array[], int n)
{
    if (n < 2) {
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        bool exchanged = false;

        /* 从右向左比较，将未排序区间的最小值移到 array[i]。 */
        for (int j = n - 1; j > i; --j) {
            if (array[j - 1] > array[j]) {
                int temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
                exchanged = true;
            }
        }

        if (!exchanged) {
            break;
        }
    }
}

int main(void)
{
    int array[] = {5, 1, 4, 2, 8};
    int n = (int)(sizeof array / sizeof array[0]);

    BubbleSort(array, n);
    for (int i = 0; i < n; ++i) {
        printf("%s%d", i == 0 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
