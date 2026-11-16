#include <stddef.h>
#include <stdio.h>

/* 非负整数升序；array 与 buffer 不重叠，均可容纳 n 个元素。 */
void RadixSort(unsigned int array[], unsigned int buffer[], size_t n)
{
    if (n < 2) {
        return;
    }

    unsigned int max = array[0];
    for (size_t i = 1; i < n; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    unsigned int exp = 1;
    for (;;) {
        size_t count[10] = {0};

        /* 统计当前位的数字出现次数。 */
        for (size_t i = 0; i < n; ++i) {
            unsigned int digit = (array[i] / exp) % 10U;
            ++count[digit];
        }
        /* 前缀和：count[d] 表示数字不大于 d 的元素总数。 */
        for (size_t d = 1; d < 10; ++d) {
            count[d] += count[d - 1];
        }
        /* 从后向前放置，保持相同数字元素的原相对顺序。 */
        for (size_t i = n; i > 0; --i) {
            unsigned int digit = (array[i - 1] / exp) % 10U;
            buffer[--count[digit]] = array[i - 1];
        }
        for (size_t i = 0; i < n; ++i) {
            array[i] = buffer[i];
        }

        /* 先判断是否还有更高位，再乘 10，避免位权溢出。 */
        if (max / exp < 10U) {
            break;
        }
        exp *= 10U;
    }
}

int main(void)
{
    unsigned int array[] = {53, 7, 105, 23, 7, 80, 12};
    unsigned int buffer[sizeof array / sizeof array[0]];
    size_t n = sizeof array / sizeof array[0];

    RadixSort(array, buffer, n);
    for (size_t i = 0; i < n; ++i) {
        printf("%s%u", i == 0 ? "" : " ", array[i]);
    }
    putchar('\n');
    return 0;
}
