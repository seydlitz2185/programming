#include "queue"

/* 自定义类实现对于 STL 的优先队列的查找方法 */
template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
class My_Priority_Queue : public std::priority_queue<T, Container, Compare>
{
    
public:
    typedef typename std::priority_queue<T, Container, Compare>::container_type::const_iterator const_iterator;
    /* 查找队列中是否存在 t，若存在则返回指向该元素的迭代器，否则返回 std::priority_queue::c.cend() */
    const_iterator find(const T &t) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();

        while (first != last)
        {
            if (*first == t)
                return first;

            ++first;
        }

        return last;
    }
};
