#include <iostream>
#include <cmath>
using namespace std;
int cal(int n, int x, int a[]);
const int N = 1e2;
int n, x, a[N];
int main()
{
	cin >> n >> x;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	cout << cal(n, x, a) << '\n';
	return 0;
}
int cal(int n, int x, int a[])
{
	int res = 0;
	for (int i = 0; i < n; ++i)
		res += pow(x, i) * a[i];
	return res;
}
