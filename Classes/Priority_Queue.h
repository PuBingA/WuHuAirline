#include <iostream>
#include <queue>
using namespace std;

template <class T>
class PQueue
{
    friend class Map_One;
private:
    priority_queue<pair<int, T>> PQ;
public:
    void Push(int priority, T element);
    T Pop();
    bool IsEmpty() const;
    T GetMaxPriority()const;
};