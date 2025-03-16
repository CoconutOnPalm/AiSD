#include "../print.h"
#include "queue.hpp"
#include "stack.hpp"




int main()
{
    Queue<int, 50> queue;
    for (int i = 0; i < 50; i++)
    {
        queue.push(i);
        std::println("[QUEUE] added: \t{}", i);
    }

    while (!queue.empty())
    {
        int var = queue.first();
        queue.pop();
        std::println("[QUEUE] removed: \t{}", var);
    }
    
    Stack<int> stack;
    for (int i = 0; i < 50; i++)
    {
        stack.push(i);
        std::println("[STACK] added: \t{}", i);
    }

    while (!stack.empty())
    {
        int var = stack.pop();
        std::println("[STACK] removed: \t{}", var);
    }
}