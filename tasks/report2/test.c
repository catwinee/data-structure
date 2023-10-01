#include <stdio.h>
int year, month, day;
int isLeap(int y)
{
    if (y % 400 == 0 || y % 4 == 0 && y % 100 != 0)
        return 1;
    else
        return 0;
}
int main()
{
    return 0;
}