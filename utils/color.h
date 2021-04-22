#ifndef _COLOR_H
#define _COLOR_H

#include <ostream>

// refs https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

namespace color
{
    enum Code
    {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    class Modifier
    {
    protected:
        Code code;

    public:
        Modifier(Code pCode);
        friend std::ostream &operator<<(std::ostream &os, const Modifier &mod);
    };
}

#endif // _COLOR_H