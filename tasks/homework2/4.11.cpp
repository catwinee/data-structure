#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

typedef struct
{
    char *idx;
    int len;
} StringType;

void StrInit(StringType &s);
void StrAssign(StringType &s, const StringType &t);
void StrAssignwithChars(StringType &s, const char chars[]);
void StrInput(StringType &s);
int StrCompare(const StringType &s, const StringType &t);
int StrLength(const StringType &s);
StringType Concat(const StringType &s, const StringType &t);
StringType SubString(const StringType &s, const int &start, const int &len);
void StrTraverse(const StringType &s);

int main()
{
    StringType s, t, r;
    StrInit(s), StrInit(t), StrInit(r);
    StrInput(s), StrInput(t);
    int alpha[26];
    char tmp[26];
    memset(alpha, -1, sizeof alpha);
    for (int i = 0; i < StrLength(s); ++i)
        if (alpha[s.idx[i] - 'a'] == -1)
            alpha[s.idx[i] - 'a'] = i;
    for (int i = 0; i < StrLength(t); ++i)
        alpha[t.idx[i] - 'a'] = -1;
    for (int i = 0, cnt = 0; i < 26; ++i)
        if (alpha[i] != -1)
            printf("字符%c在s中第一次出现的位置为:%d\n", tmp[cnt++] = i + 'a', alpha[i] + 1);
    StrAssignwithChars(r, tmp);
    StrTraverse(r);
    return 0;
}

void StrInit(StringType &s)
{
    s.idx = nullptr;
    s.len = 0;
}
void StrAssignwithChars(StringType &s, const char chars[])
{
    StrInit(s);
    s.len = strlen(chars);
    s.idx = new char[s.len + 1];
    strcpy(s.idx, chars);
}
void StrInput(StringType &s)
{
    printf("请输入字符串(不支持空格):\n");
    char chars[100];
    scanf("%s", chars);
    StrAssignwithChars(s, chars);
}
void StrAssign(StringType &s, const StringType &t)
{
    StrInit(s);
    int n = t.len;
    s.idx = new char[n + 1];
    for (int i = 0; i < n; ++i)
        s.idx[i] = t.idx[i];
}
int StrCompare(const StringType &s, const StringType &t)
{
    for (int i = 0; i < s.len && i < t.len; ++i)
        if (s.idx[i] != t.idx[i])
            return s.idx[i] - t.idx[i];
    return s.len - t.len;
}
int StrLength(const StringType &s)
{
    return s.len;
}
StringType Concat(const StringType &s, const StringType &t)
{
    StringType res;
    StrInit(res);
    res.len = s.len + t.len;
    res.idx = new char[res.len + 1];
    for (int i = 0; i < s.len; ++i)
        res.idx[i] = s.idx[i];
    for (int i = s.len; i < s.len + t.len; ++i)
        res.idx[i] = t.idx[i - s.len];
    return res;
}
StringType SubString(const StringType &s, int &start, const int &len)
{
    --start;
    StringType res;
    StrInit(res);
    if (start < 0 || start + len > s.len || len <= 0)
        return res;
    res.len = len;
    res.idx = new char[len + 1];
    for (int i = 0; i < len; ++i)
        res.idx[i] = s.idx[start + i];
    return res;
}
void StrTraverse(const StringType &s)
{
    printf("Traverse Str:\n");
    if (!s.len)
        return (void)printf("The str is empty.\n");
    for (int i = 0; i < s.len; ++i)
        printf("%c", s.idx[i]);
    printf("\n");
}