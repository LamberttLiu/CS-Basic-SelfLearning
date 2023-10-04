#include <stdio.h>
#include <string.h>


int Index_BF(char *main, int mainLen, char *pattern, int patLen)
{
    int pStr = 0, pPat = 0;
    int matchCnt = 0;
    
    // 必须满足指针小于字符串长度，否则比较无意义。
    while (pStr < mainLen && pPat < patLen) {
        // 如果有字符相等，继续比较后续字符串
        if (main[pStr] == pattern[pPat]) {
            ++pStr;
            ++pPat;  
        } else {
            /*  step = pPat - 0 = pPat = pStr - PStrOrigin,
                pStrOrigin = pStr - pPat
                pStrNext = pStr - pPat + 1
            */
            pStr = pStr - pPat + 1;
            pPat = 0;   // 失败从0位置开始
        }
        matchCnt++;       
    }

    printf("matching counts = %d\n", matchCnt);     // 16次

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

    int index = Index_BF(mainStr,strlen(mainStr), patternStr,strlen(patternStr));
    
    /* 预期匹配位置：2 
    index      0   1   2   3   4   5   6   7   8   9
    main       a - b - a - b - a - b - a - b - c - a
    pattern            a - b - a - b - a - b - c - a   */
    printf("Locate pattern matching :index [%d].\n", index);
}
