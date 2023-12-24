#include <iostream>
#include <queue>
#include "Priority_Queue.h"
using namespace std;

template<class T>
void PQueue<T>::Push(int priority, T element)
{
    PQ.push(make_pair(priority, element));
}

//弹出队列中优先级最大的元素
template<class T>
T PQueue<T>::Pop()
{
    if (!PQ.empty())
    {
        T element = PQ.top().second;
        PQ.pop();
        return element;
    }
    return -1;
}

template<class T>
bool PQueue<T>::IsEmpty() const
{
    return PQ.empty();
}

//返回最大优先级元素，但不弹出
template<class T>
T PQueue<T>::GetMaxPriority() const
{
    if (!pq.empty())
    {
        return pq.top().second;
    }
}

