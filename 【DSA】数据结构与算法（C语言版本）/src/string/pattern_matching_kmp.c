#include <stdio.h>
#include <string.h>

int next[8] = {0};

void GetNext(char *pattern, int *next)
{
    next[0] = -1;
    int i = 0, j = -1;

    while (i < (int)strlen(pattern))
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }    
        else
            j = next[j];
    }
}

int Index_KMP(char *main, int mainLen, char *pattern, int patLen)
{
    int pStr = 0, pPat = 0;
    int matchCnt = 0;
    
    // 必须满足指针小于字符串长度，否则比较无意义。
    while (pStr < mainLen && pPat < patLen) {
        // 如果有字符相等，继续比较后续字符串
        if (pPat == -1 ||main[pStr] == pattern[pPat]) {
            ++pStr;
            ++pPat;  
        } else {
            pPat = next[pPat];
        }
        matchCnt++;       
    }

    printf("matching counts = %d\n", matchCnt);         // 11次

    // 匹配时，满足等于strlen
    if (pPat >= patLen) {
        return pStr - patLen;
    } else {
        return 0;
    }
}


int main()
{
    char mainStr[] = "ababababca";
    char patternStr[] = "abababca";

    printf("str length of main Str [%s] = %d\n",mainStr, strlen(mainStr));
    printf("str length of patten Str [%s] = %d\n",patternStr, strlen(patternStr));
    GetNext(patternStr, next);
    for (size_t i = 0; i < 8; i++)
    {
        printf("next[%d] = %d\n", i, next[i]);
    }
    
    int index = Index_KMP(mainStr,strlen(mainStr), patternStr,strlen(patternStr));
    
    /* 预期匹配位置：2 
    index      0   1   2   3   4   5   6   7   8   9
    main       a - b - a - b - a - b - a - b - c - a
    pattern            a - b - a - b - a - b - c - a   */
    printf("Locate pattern matching :index [%d].\n", index);
}