#include <stddef.h>
#include <stdio.h>

/* n >= 0；普通数组元素位于 array[0..n-1]。 */
void InsertSort(int array[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = array[i];
        int j = i;
        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = key;
    }
}

/* 实际元素位于 array[1..n]，至少分配 n+1 个位置。 */
void InsertSortSentinel(int array[], int n)
{
    for (int i = 2; i <= n; ++i) {
        if (array[i] < array[i - 1]) {
            array[0] = array[i];
            int j = i - 1;
            while (array[j] > array[0]) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = array[0];
        }
    }
}

void BinaryInsertSort(int array[], int n)
{
    for (int i = 1; i < n; ++i) {
        if (array[i] >= array[i - 1]) {
            continue;
        }
        int key = array[i];
        int low = 0, high = i;
        /* 在 [0, i) 中找第一个严格大于 key 的位置。 */
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (array[mid] <= key) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        /* [low, i) 整体右移，包括原来位于 low 的元素。 */
        for (int j = i; j > low; --j) {
            array[j] = array[j - 1];
        }
        array[low] = key;
    }
}

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *InsertionSortList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct ListNode dummy = {0, head};
    struct ListNode *last = head;
    struct ListNode *cur = head->next;

    while (cur != NULL) {
        if (last->val <= cur->val) {
            last = cur;
        } else {
            struct ListNode *prev = &dummy;
            /* 插在已有相同值结点之后，保持稳定。 */
            while (prev->next != NULL && prev->next->val <= cur->val) {
                prev = prev->next;
            }
            last->next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
        }
        cur = last->next;
    }
    return dummy.next;
}

static void PrintArray(const int array[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%s%d", i == 0 ? "" : " ", array[i]);
    }
    putchar('\n');
}

int main(void)
{
    int a[] = {5, 2, 4, 2, 1};
    int b[] = {0, 5, 2, 4, 2, 1}; /* b[0] 留给哨兵 */
    int c[] = {5, 2, 4, 2, 1};
    InsertSort(a, 5);
    InsertSortSentinel(b, 5);
    BinaryInsertSort(c, 5);
    PrintArray(a, 5);
    PrintArray(b + 1, 5);
    PrintArray(c, 5);

    struct ListNode nodes[] = {
        {5, NULL}, {2, NULL}, {4, NULL}, {2, NULL}, {1, NULL}
    };
    for (int i = 0; i < 4; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    struct ListNode *head = InsertionSortList(nodes);
    for (struct ListNode *p = head; p != NULL; p = p->next) {
        printf("%d%s", p->val, p->next == NULL ? "\n" : " ");
    }
    return 0;
}
