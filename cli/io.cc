#include "io.h"

#include <iostream>

template <typename Min, typename Max>
static void validate_min_max(Min *min_value, Min min_limit, Max *max_value, Max max_limit);

bool IO::ask_bool(const std::string &q)
{
    std::string new_q = q;

    new_q.append(" [Y/n] ");

    std::string res = ask_string(new_q);

    return res.empty() || res == "y" || res == "Y" || res == "1";
}

double IO::ask_double(const std::string &q, double min, double max)
{
    validate_min_max<double, double>(&min, __DBL_MIN__, &max, __DBL_MAX__);

    double res;

    std::cout << q;

    while (!(std::cin >> res) || res < min || res > max)
    {
        out_on_invalid_value_passed(q);
    }

    return res;
}

uint IO::ask_uint(const std::string &q, uint min, uint max)
{
    validate_min_max<uint, uint>(&min, 0, &max, UINT32_MAX);

    int res;

    std::cout << q;
    while (!(std::cin >> res) || res < min || res > max)
    {
        out_on_invalid_value_passed(q);
    }

    return (uint)res;
}

std::string IO::ask_string(const std::string &q)
{
    std::cout << q;

    std::string res;

    std::cin >> res;

    if (std::cin.fail())
    {
        throw InvalidValuePassedException();
    }

    return res;
}

void IO::wait_action(const std::string &q)
{
    std::cout << q << std::endl
              << "Press any key to continue.";

    std::string res;

    std::cin >> res;
}

template <typename Min, typename Max>
static void validate_min_max(Min *min_value, Min min_limit, Max *max_value, Max max_limit)
{
    if (*min_value < min_limit)
    {
        *min_value = 0;
    }
    if (*max_value > max_limit)
    {
        *max_value = max_limit;
    }
}