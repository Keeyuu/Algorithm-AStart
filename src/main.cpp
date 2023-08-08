#include <iostream>
#include "grid.hpp"
using namespace std;

class testNode : public INoder
{
};

void testque()
{
    auto a = std::make_shared<testNode>();
    a->G = 1;

    auto c = std::make_shared<testNode>();
    c->G = 1000;

    auto b = std::make_shared<testNode>();
    b->G = 2;

    INoderQue que;
    que.push(a);
    que.push(b);
    que.push(c);
    while (!que.empty())
    {
        auto &x = que.top();
        cout << x->G << endl;
        que.pop();
    }
}

int main(int argc, char **argv)
{
    auto area = std::make_shared<Area>(10, 10);

    area->LockGrid(0, 3);
    area->LockGrid(1, 3);
    area->LockGrid(2, 3);
    area->LockGrid(3, 3);
    area->LockGrid(4, 3);
    area->LockGrid(5, 3);
    //
    area->LockGrid(2, 5);
    area->LockGrid(3, 5);
    area->LockGrid(4, 5);
    area->LockGrid(5, 5);
    area->LockGrid(6, 5);
    area->LockGrid(7, 5);
    area->LockGrid(8, 5);
    area->LockGrid(9, 5);
    //
    area->LockGrid(0, 7);
    area->LockGrid(1, 7);
    area->LockGrid(2, 7);
    area->LockGrid(3, 7);
    area->LockGrid(4, 7);
    area->LockGrid(5, 7);
    auto start = area->GetGrid(0, 0);
    auto end = area->GetGrid(9, 9);
    area->PrintMap(start, end);
    return 0;
}
