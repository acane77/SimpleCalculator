#ifndef _MIYUKI_TOKEN_HPP
#define _MIYUKI_TOKEN_HPP

#include "include.h"
#include "tags.h"
#include "define.hpp"

namespace Miyuki {
    using namespace std;

    class token {
    public:
        int  tag;

        token(int _tag):tag(_tag) {}
    };

    class number :public token {
    public:
        int val;

        number(int _v) : val(_v), token(tags::NUMBER) { }
    };

    class word :public token {
    public:
        std::string lexeme;

        word(std::string _lexeme, int tag):lexeme(_lexeme), token(tag) {}

        static word Main, Int, Char, If, Else, For, While, Assign, Add, Sub, Mul, Div, Lb, Rb, Llb, Rlb, Fh,
            Lt, Gt, Lte, Gte, Eq, Neq;
    };
}

#endif
