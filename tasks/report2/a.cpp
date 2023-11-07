#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
ofstream outputFile;
int f(int x) //递归没什么好说的
{
    if (!x)
        return 0;
    else if (x == 1)
        return 1;
    else if (x % 2)
        return f(x / 2) + f(x - 2);
    else
        return f(x / 2);
}
int main()
{
    outputFile.open("a.txt");
    for (int i = 0; i <= 39; ++i)
    {
        outputFile << setw(6) << f(i);
        if (i % 5 == 4)
            outputFile << '\n';
    }
    outputFile.close();
    return 0;
}