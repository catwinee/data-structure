#include <iostream>
#include <cstring>
using namespace std;

typedef struct
{
    char *idx;
    int len;
} str;

//初始化字符串
void initStr(str &s)
{
    s.idx = nullptr;
    s.len = 0;
}
//用字符数组给字符串赋值
void assignStr(str &s, const char *chars)
{
    initStr(s);
    s.len = strlen(chars);
    s.idx = new char[s.len + 1];
    strcpy(s.idx, chars);
}
//从键盘输入给字符串赋值
void inputStr(str &s)
{
    printf("请输入字符串(不支持空格):\n");
    char chars[100];
    scanf("%s", chars);
    assignStr(s, chars);
}
//从pos起删除s中len个字符
void trimStr(str &s, int pos, int len)
{
    if (pos < 0)
    {
        printf("pos can't be nagetive!\n");
        exit(-1);
    }
    if (pos + len > s.len)
    {
        printf("Downflow!\n");
        exit(-1);
    }
    char *tmp = s.idx;
    s.idx = new char[s.len - len + 1];
    for (int i = 0; i < pos; ++i)
        s.idx[i] = tmp[i];
    for (int i = pos; i < s.len - len; ++i)
        s.idx[i] = tmp[i + len];
    s.len -= len;
    delete[] tmp;
    tmp = nullptr;
}
//在s的pos处插入t1
void insertStr(str &s, int pos, const str &t)
{
    if (pos < 0)
    {
        printf("pos can't be nagetive!\n");
        exit(-1);
    }
    char *tmp = s.idx;
    s.idx = new char[s.len + t.len + 1];
    for (int i = 0; i < pos; ++i)
        s.idx[i] = tmp[i];
    for (int i = pos; i < pos + t.len; ++i)
        s.idx[i] = t.idx[i - pos];
    for (int i = pos + t.len; i < s.len + t.len; ++i)
        s.idx[i] = tmp[i - t.len];
    s.len += t.len;
    delete[] tmp;
    tmp = nullptr;
}
//遍历字符串
void traverseStr(const str &s)
{
    printf("Traverse Str:\n");
    if (!s.len)
        return (void)printf("The str is empty.\n");
    for (int i = 0; i < s.len; ++i)
        printf("%c", s.idx[i]);
    printf("\n");
}
//获取nextval数组
void getNext(const str &s, int nextval[])
{
    int j = 0, k = -1;
    nextval[0] = -1;
    while (s.idx[j])
    {
        if (k == -1 || s.idx[j] == s.idx[k])
        {
            ++j, ++k;
            if (s.idx[j] != s.idx[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        }
        else
            k = nextval[k];
    }
}
//KMP算法匹配字符串
int kmp(str &s, const str &t1, const str &t2)
{
    int n = s.len, nextval[t1.len], i = 0, j = 0, cnt = 0;
    getNext(t1, nextval); //获取nextval数组
    while (i < s.len)
    {
        if (j == -1 || s.idx[i] == t1.idx[j])
            ++i, ++j;
        else
            j = nextval[j];
        if (j == t1.len)
        {
            j = 0, ++cnt;
            i -= t1.len;
            trimStr(s, i, t1.len); //删除t1
            insertStr(s, i, t2);   //插入t2, 完成替换
            i += t2.len;
        }
    }
    return cnt;
}

int main()
{
    str s, t1, t2;
    inputStr(s), inputStr(t1), inputStr(t2);

    traverseStr(s);
    printf("本次kmp一共进行了%d次匹配\n", kmp(s, t1, t2));
    printf("匹配替换后的主串为:\n");
    traverseStr(s);
     printf("\n");
    return 0;
}