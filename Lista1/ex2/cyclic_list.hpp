#pragma once

#include <memory>
#include <cstdint>
#include <stack>
#include <stdexcept>

#include "../print.h"

template <typename T>
class CyclicList
{
public:


    struct Node
    {
        Node(const T& data) : next(nullptr), data(data) {}

        std::shared_ptr<Node> next;
        T data;
    };



    CyclicList() : m_size(0), m_tail(nullptr)
    {

    }

    ~CyclicList()
    {
        std::stack<Node*> nodes;

        Node* current_node = m_head.get();
        for (size_t i = 0; i < m_size; i++)
        {
            nodes.push(current_node);
            current_node = current_node->next.get();
        }

        while (!nodes.empty())
        {
            Node* node = nodes.top();
            nodes.pop();
            // std::println("deleted child of: {}", node->data);
            node->next = nullptr;
        }

        // std::println("deleted: {}", m_head->data);
        m_head = nullptr;
    }



    T& operator[](const size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("requested index out of range");

        Node* current_node = m_head.get();
        for (size_t i = 0; i < index; i++)
        {
            current_node = current_node->next.get();
        }

        return current_node->data;
    }


    void insert(const T& element)
    {
        if (m_head == nullptr)
        {
            m_head = std::make_shared<Node>(element);
            m_tail = m_head.get();
        }
        else
        {
            m_tail->next = std::make_shared<Node>(element);
            m_tail = m_tail->next.get();
            m_tail->next = m_head;
        }

        m_size++;
    }



    Node* find(const T& element)
    {
        Node* current = m_head.get();
        for (size_t i = 0; i < m_size; i++)
        {
            if (current->data == element)
                return current;
            current = current->next;
        }

        return nullptr;
    }


    std::pair<Node*, size_t> find_with_cost(const T& element)
    {
        Node* current = m_head.get();
        for (size_t i = 0; i < m_size; i++)
        {
            if (current->data == element)
            {
                return std::make_pair(current, i + 1);
            }
            current = current->next.get();
        }

        return std::make_pair(nullptr, m_size);
    }


    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }


    template <typename U>
    static CyclicList merge(const CyclicList<U>& l1, const CyclicList<U>& l2)
    {
        CyclicList outp;
        Node* l1_node = l1.m_head.get();
        Node* l2_node = l2.m_head.get();
        size_t l1_index = 0;
        size_t l2_index = 0 ;

        while(l1_index < l1.size() || l2_index < l2.size())
        {
            if (l1_index >= l1.size())
            {
                outp.insert(l2_node->data);
                l2_node = l2_node->next.get();
                l2_index++;
                continue;
            }
            else if (l2_index >= l2.size())
            {
                outp.insert(l1_node->data);
                l1_node = l1_node->next.get();
                l1_index++;
                continue;
            }

            if (l1_node->data <= l2_node->data)
            {
                outp.insert(l1_node->data);
                l1_node = l1_node->next.get();
                l1_index++;
            }
            else
            {
                outp.insert(l2_node->data);
                l2_node = l2_node->next.get();
                l2_index++;
            }
        }

        return outp;
    }


private:

    size_t m_size;
    std::shared_ptr<Node> m_head;
    Node* m_tail;
};