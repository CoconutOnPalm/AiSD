#pragma once

#include <iostream>
#include <format>

// Ubuntu is still in a stone age when it comes to gcc version...

namespace std
{
    template <typename... Args>
    void print(std::string_view fmt, Args&&... args)
    {
        std::cout << std::vformat(fmt, std::make_format_args(args...));
    }

    template <typename... Args>
    void println(std::string_view fmt, Args&&... args)
    {
        std::cout << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
    }

    void println()
    {
        std::cout << std::endl;
    }
}