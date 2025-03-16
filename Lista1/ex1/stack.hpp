#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
public:

    Stack() = default;
    Stack(const std::initializer_list<T>& elements) : m_data(elements) {}
    ~Stack() = default;

    void push(const T& elem)
    {
        push_impl(elem);
    }

    T pop()
    {
        if (m_data.size() == 0)
            throw std::out_of_range("cannot invoke pop() on empty stack");

        return pop_impl();
    }

    size_t size() const 
    {
        return m_data.size();
    }

    bool empty() const
    {
        return m_data.empty();
    }


private:

    inline void push_impl(const T& elem)
    {
        m_data.push_back(elem);
    }

    inline T pop_impl()
    {
        T buff = m_data.back();
        m_data.pop_back();
        return buff;
    }

    std::vector<T> m_data;

};