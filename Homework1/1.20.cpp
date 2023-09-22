#include <iostream>
#include <cmath>
using namespace std;
typedef struct Polyn
{
    int a;
    struct Polyn *next;
} PolynTerm, *PolynPtr;
int n, x, res;
int main()
{
    PolynPtr head = new PolynTerm, p = head; // 1次
    cin >> n;                                // 1次
    for (int i = 0; i <= n; ++i)             // n + 2次
    {
        PolynPtr tmp = new PolynTerm; // n + 1次
        cin >> tmp->a;                // n + 1次
        p->next = tmp, p = p->next;   // n + 1次
    }
    p->next = nullptr, p = head; // 1次
    cin >> x;                    // 1次
    for (int i = 0; i <= n; ++i) // n + 2次
    {
        p = p->next;             // n + 1次
        res += p->a * pow(x, i); // n + 1次
    }
    cout << res << '\n'; // 1次
    return 0;
}