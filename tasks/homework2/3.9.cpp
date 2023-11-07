#include <iostream>
using namespace std;
void digui(int n)
{
    int i;
    i = n;
    if (i > 1)
        return printf("%d", i), digui(n - 1);
}
int main()
{
    int n;
    cin >> n;
    ditui(n);
    printf("\n");
    digui(n);
    return 0;
}