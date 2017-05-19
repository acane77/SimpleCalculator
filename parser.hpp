#ifndef _MIYUKI_PARSER_HPP
#define _MIYUKI_PARSER_HPP

#include "lexer.hpp"
#include "symbols.hpp"

namespace Miyuki {
    class parser {
        token * look;

        Program * root;

        void match(int t, const char * ex);
        bool move();

        void initial_exception(const char * ex) { throw SyntaxError(ex); }

        // 以下是产生式的Parse
        Program * parse_program();
        Block * parse_block();
        Stmts * parse_stmts();
        Stmt * parse_stmt();
        Arith * parse_expr();
        Arith * parse_term();
        Factor * parse_factor();
        Boolean * parse_boolean();
    public:
        parser(const char * file);
        ~parser();

        lexer * lex = nullptr;

        void parse();
    };
}

#endif
