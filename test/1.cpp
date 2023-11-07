#include <iostream>
#include <iomanip>
#include <string>
#include "stack.h"
#include "queue.h"
using namespace std;

int main()
{
    queue<int> q(11);
    for (int i = 0; i < 10; ++i)
    {
        q.enQueue(i);
    }
    while (!q.isEmpty())
        cout << q.deQueue();
    for (int i = 0; i < 10; ++i)
    {
        q.enQueue(i);
    }while (!q.isEmpty())
        cout << q.deQueue();
}