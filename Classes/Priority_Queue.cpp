#include <iostream>
#include <queue>
#include "Priority_Queue.h"
using namespace std;

template<class T>
void PQueue<T>::Push(int priority, T element)
{
    PQ.push(make_pair(priority, element));
}

//�������������ȼ�����Ԫ��
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

//����������ȼ�Ԫ�أ���������
template<class T>
T PQueue<T>::GetMaxPriority() const
{
    if (!pq.empty())
    {
        return pq.top().second;
    }
}

