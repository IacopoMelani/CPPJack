#include "color.h"

namespace color
{
    Modifier::Modifier(Code pCode) : code(pCode) {}

    std::ostream &operator<<(std::ostream &os, const Modifier &mod)
    {
        return os << "\033[" << mod.code << "m";
    }
};