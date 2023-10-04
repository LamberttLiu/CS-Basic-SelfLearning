#include <stdio.h>
#include <string.h>


int BinarySearch(int *L, int len, int target)
{
    int low = 0, high = len - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;         // 对序数取半
        if (L[mid] == target){
            return mid;                 // 查找成功直接返回序数
        }
        else if (L[mid] > target){
            high = mid - 1;             // 开始从前半部分查找
        }
        else {
            low = mid + 1;              // 开始从后半部分查找
        }
    }
    return -1;                          // 查找失败，返回-1值
}

int main()
{
    int L[] = {7, 10, 13, 16, 19, 29, 32, 33, 37, 41, 43};
    int target = 33;
    int index = BinarySearch(L, sizeof(L) / sizeof(L[0]), target);

    /* 预期输出： 7
    index  0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
    data    7, 10, 13, 16, 19, 29, 32, 33, 37, 41, 43
    */
    printf("index of target[%d] = %d\n", target, index);
}