#ifndef _MIYUKI_TAGS_H
#define _MIYUKI_TAGS_H

namespace Miyuki {
    namespace tags {
        enum {
            // 被词法分析器识别的非终结符号
            __FLAG_START_TERMINAL = 511,
            MAIN, INT, CHAR, IF, ELSE, FOR, WHILE, ASSIGN, ADD, SUB, MUL, DIV, LB, RB, LLB, RLB, FH,
            LT, LTE, GT, GTE, EQ, NEQ, T_EOF,

            NUMBER, ID, TEMP
        };
    }
}

#endif
