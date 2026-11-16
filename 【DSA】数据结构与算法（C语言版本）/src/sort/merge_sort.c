#include <stdio.h>

/* 合并两个已经有序的闭区间 [low, mid] 和 [mid+1, high]。 */
void Merge(int array[], int buffer[], int low, int mid, int high)
{
    for (int k = low; k <= high; ++k) {
        buffer[k] = array[k];
    }

    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (buffer[i] <= buffer[j]) {
            array[k++] = buffer[i++];
        } else {
            array[k++] = buffer[j++];
        }
    }
    while (i <= mid) {
        array[k++] = buffer[i++];
    }
    while (j <= high) {
        array[k++] = buffer[j++];
    }
}

void MergeSort(int array[], int buffer[], int low, int high)
{
    if (low < high) {
        int mid = low + (high - low) / 2;
        MergeSort(array, buffer, low, mid);
        MergeSort(array, buffer, mid + 1, high);
        Merge(array, buffer, low, mid, high);
    }
}

int main(void)
{
    int array[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int buffer[sizeof array / sizeof array[0]];
    int n = (int)(sizeof array / sizeof array[0]);

    MergeSort(array, buffer, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%s%d", i == 0 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
