#ifndef _MIYUKI_INTERPRETER_HPP
#define _MIYUKI_INTERPRETER_HPP

#include "include.h"
#include "intermediate.hpp"
#include <cstring>
#include <functional>
#include <string>

namespace Miyuki {
    using namespace std;

    class interpreter {
        deque<Quad>* pcodes;

        map<string, double> vars;
        double tempvars[1000];
        uint32_t PC = 0;

        double ret_val(Factor * f);
        double str_val(Factor * f, double val);
    public:
        interpreter(deque<Quad>* c): pcodes(c) { }
        void printvars() {
            for (auto it = vars.begin(); it != vars.end(); ++it)
                cout << (*it).first << " = " << (*it).second << endl;
        }

        void interprete();
    };
}

#endif
