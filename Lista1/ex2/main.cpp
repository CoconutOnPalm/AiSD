#include <random>
#include <array>

#include "../print.h"
#include "cyclic_list.hpp"


int main()
{
    CyclicList<int> mlist1;
    CyclicList<int> mlist2;


    for (int i = 10; i < 30; i += 2)
        mlist1.insert(i);

    
    for (int i = 11; i < 31; i += 2)
        mlist2.insert(i);

    std::print("merged: ");
    auto res = CyclicList<int>::merge(mlist1, mlist2);
    for (size_t i = 0; i < res.size(); i++)
    {
        std::print("{}, ", res[i]);
    }
    std::println();


    std::array<int, 10'000> T;
    CyclicList<int> list;
    uint64_t total_cost_a = 0; // from T
    uint64_t total_cost_b = 0; // random

    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> dist(0, 100'000 + 1);
    std::uniform_int_distribution<size_t> itr_dist(0, T.size());

    for (auto& i : T)
    {
        i = dist(generator);
    }

    for (const auto i : T)
    {
        list.insert(i);
    }


    for (size_t i = 0; i < 1000; i++)
    {
        size_t elem = itr_dist(generator);
        total_cost_a += list.find_with_cost(T[elem]).second;
    }

    std::println("avg cost for (a): {}", static_cast<double>(total_cost_a) / 1000.);


    for (size_t i = 0; i < 1000; i++)
    {
        int elem = dist(generator);
        total_cost_b += list.find_with_cost(i).second;
    }


    std::println("avg cost for (b): {}", static_cast<double>(total_cost_b) / 1000.);
}