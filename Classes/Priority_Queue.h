#include <iostream>
#include <queue>
using namespace std;

template <class T>
class PQueue
{
private:
    priority_queue<pair<int, T>> PQ;
public:
    void Push(int element, int priority);
    T Pop();
    bool IsEmpty() const;
};

template<class T>
inline void PQueue<T>::Push(int element, int priority)
{
    PQ.push(std::make_pair(priority, element));
}

template<class T>
inline T PQueue<T>::Pop()
{
    if (!PQ.empty())
    {
        T element = PQ.top().second;
        PQ.pop();
        return element;
    }
    return T();
}

template<class T>
inline bool PQueue<T>::IsEmpty() const
{
    return PQ.empty();
}
