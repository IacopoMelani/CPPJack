#ifndef _IO_H
#define _IO_H

#include <exception>
#include <iostream>
#include <limits>
#include <string>

#include <vector>

#include "classes/exceptions/invalid_value_passed_except.h"

static void out_on_invalid_value_passed(const std::string &q);

namespace IO
{
    bool ask_bool(const std::string &q);

    double ask_double(const std::string &q, double min = __DBL_MIN__, double max = __DBL_MAX__);

    std::string ask_string(const std::string &q);

    template <typename T>
    T ask_from_options(const std::string &q)
    {
        T res;

        std::cout << q;
        while (!(std::cin >> res))
        {
            out_on_invalid_value_passed(q);
        }

        return res;
    }

    uint ask_uint(const std::string &q, uint min = 0, uint max = UINT32_MAX);
};

static void out_on_invalid_value_passed(const std::string &q)
{
    std::cerr << "Invalid input given" << std::endl;
    std::cin.clear();
    std::cin.ignore(512, '\n');
    std::cout << q;
}

#endif // _IO_H