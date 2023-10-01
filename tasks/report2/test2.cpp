#include <iostream>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ofstream fout("b.txt");
    stack<int> Sta;
    vector<int> num(40, -1);

    num[0] = 0;
    num[1] = 1;
    Sta.push(39);
    while (!Sta.empty())
    {
        int i = Sta.top();
        if (i % 2 == 0)
        {
            if (num[i / 2] == -1)
            {
                Sta.push(i / 2);
            }
            else
            {
                Sta.pop();
                num[i] = num[i / 2];
            }
        }
        else
        {
            if (num[i / 2] == -1 || num[i - 2] == -1)
            {
                Sta.push(i - 2);
                Sta.push(i / 2);
            }
            else
            {
                Sta.pop();
                num[i] = num[i / 2] + num[i - 2];
            }
            if (num[i - 1] == -1)
            {
                Sta.push(i - 1);
            }
        }
    }
    int j = 1;
    for (int i = 0; i < 40; i++)
    {
        fout << "f(" << i << ") = " << num[i] << "\t";
        if (j == 8)
        {
            j = 0;
            fout << endl;
        }
        j++;
    }
    return 0;
}
