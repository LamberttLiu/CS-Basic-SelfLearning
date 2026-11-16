#include <stdio.h>

/* 实际元素位于 array[1..n]，array[0] 仅作暂存。 */
void shellSort(int array[], int n)
{
    if (n < 2) {
        return;
    }
    for (int d = n / 2; d >= 1; d /= 2) {
        for (int i = d + 1; i <= n; ++i) {
            if (array[i] < array[i - d]) {
                array[0] = array[i];
                int j = i - d;
                while (j > 0 && array[j] > array[0]) {
                    array[j + d] = array[j];
                    j -= d;
                }
                array[j + d] = array[0];
            }
        }
    }
}

int main(void)
{
    int array[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
    int n = (int)(sizeof array / sizeof array[0]) - 1;

    shellSort(array, n);
    for (int i = 1; i <= n; ++i) {
        printf("%s%d", i == 1 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
