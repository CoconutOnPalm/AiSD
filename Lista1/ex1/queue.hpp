#pragma once

#include <initializer_list>
#include <array>
#include <stdexcept>


// cyckled queue implementation based on Cormen's "Introduction to algorithms" implementation
template <typename T, size_t max_size>
class Queue
{
public:

    Queue() : m_size(0), m_head(0), m_tail(0)
    {

    }

    Queue(std::initializer_list<T> elements)
    {
        m_size = elements.size();

        for (const auto& e : elements)
            this->push_impl(e);
    }

    ~Queue()
    {

    }

    void push(const T& elem)
    {
        if (m_size + 1 > max_size)
            throw std::out_of_range("queue overflow");

        push_impl(elem);
    }

    void pop()
    {
        if (m_size == 0)
            throw std::out_of_range("cannot invoke pop() on empty queue");

        pop_impl();
    }

    T first()
    {
        return m_elements[m_head];
    }


    size_t size() const 
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0;
    }


private:

    inline void push_impl(const T& elem)
    {
        m_size++;
        m_elements[m_tail] = elem;
        
        m_tail++;
        if (m_tail >= max_size)
            m_tail = 0;
    }

    inline void pop_impl()
    {
        m_size--;
        m_head++;
        if (m_head >= max_size)
            m_head = 0;
    }

    std::array<T, max_size> m_elements;
    size_t m_head;
    size_t m_tail;
    size_t m_size;
};