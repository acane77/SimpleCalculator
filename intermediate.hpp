#ifndef _MIYUKI_INTERMEDIATE_HPP
#define _MIYUKI_INTERMEDIATE_HPP

#include "symbols.hpp"

namespace Miyuki {
    class quad {
    public:
        int label = -1;
        int opcode;
        Factor * op1;
        Factor * op2;
    };
}

#endif
