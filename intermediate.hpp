#ifndef _MIYUKI_INTERMEDIATE_HPP
#define _MIYUKI_INTERMEDIATE_HPP

#include "include.h"

namespace Miyuki {
    class Factor;

    class Quad {
    public:
        enum Opcode {
            MOV, ADD, SUB, MUL, DIV, JEQ, JNEQ, JGT, JGTE, JLT, JLTE, J
        };

        const char * OpcodeName[12] = { "=", "+", "-", "*", "/", "j=", "j!=", "j>", "j>=", "j<", "j<=", "j" };

        int opcode;
        Factor * op1; //addr
        Factor * op2; //addr
        Factor * result;

        Quad(int o, Factor * o1, Factor * o2, Factor * re)
            :op1(o1), op2(o2), opcode(o), result(re) {

        }
    };

    extern std::deque<Quad> quads;

    void EmitQuad(int o, Factor * o1, Factor * o2, Factor * re);
    void replace();
    void emitLabel(int n);
    void print();
}

#endif
