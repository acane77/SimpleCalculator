#include "interpreter.hpp"
#include "symbols.hpp"
#include "exceptions.hpp"
/*
        enum Opcode {
            MOV, ADD, SUB, MUL, DIV, JEQ, JNEQ, JGT, JGTE, JLT, JLTE, J
        };
*/

namespace Miyuki {

    double interpreter::ret_val(Factor * f) {
        switch (f->ftype) {
        case tags::ID:
            return vars[((ID*)f)->id->lexeme];
        case tags::TEMP:
            return tempvars[((Temp*)f)->id];
        case tags::NUMBER:
            return ((Number*)f)->num->val;
        }
        return 0;
    }

    double interpreter::str_val(Factor * f, double val) {
        switch (f->ftype) {
        case tags::ID:
            vars[((ID*)f)->id->lexeme] = val;
            break;
        case tags::TEMP:
            tempvars[((Temp*)f)->id] = val;
            break;
        case tags::NUMBER:
            throw SyntaxError("invaild assign for a rvalue.");
        }
        return 0;
    }


    void interpreter::interprete() {
        deque<Quad>& codes = *pcodes;
        int N = codes.size();

        while (PC < N) {
            //printf("Current PC=%d\n", PC);
            Quad& ins = codes[PC];
            if (ins.opcode <= Quad::Opcode::DIV && ins.opcode >= Quad::Opcode::ADD ) {
                double op1 = ret_val(ins.op1);
                double op2 = ret_val(ins.op2);
                double result;
                switch (ins.opcode) {
                case Quad::Opcode::ADD: result = op1+op2; break;
                case Quad::Opcode::SUB: result = op1-op2; break;
                case Quad::Opcode::MUL: result = op1*op2; break;
                case Quad::Opcode::DIV: result = op1/op2; break;
                }
                str_val(ins.result, result);
                PC++;
            }
            else if (ins.opcode == Quad::Opcode::MOV) {
                double op1 = ret_val(ins.op1);
                str_val(ins.result, op1);
                PC++;
            }
            else {
                int label = ((Label*)ins.result)->id;
                if (ins.opcode == Quad::Opcode::J) {
                    PC = label;
                }
                else {
                    double op1 = ret_val(ins.op1);
                    double op2 = ret_val(ins.op2);
                    bool result;
                    switch (ins.opcode) {
                    case Quad::Opcode::JGT: result = op1>op2; break;
                    case Quad::Opcode::JGTE: result = op1>=op2; break;
                    case Quad::Opcode::JLT: result = op1<op2; break;
                    case Quad::Opcode::JLTE: result = op1<=op2; break;
                    case Quad::Opcode::JEQ: result = op1==op2; break;
                    case Quad::Opcode::JNEQ: result = op1!=op2; break;
                    }
                    if (result)
                        PC = label;
                    else
                        PC++;
                }
            }
        }
        puts("\n\nresults: ");
        printvars();
    }
}
