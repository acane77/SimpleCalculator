#include "parser.hpp"

namespace Miyuki {
    parser::parser(const char *file) {
        lex = new lexer(file);

        if (lex == nullptr) {
            //release();
            throw runtime_error("Cannot create lexer.");
        }
    }

    parser::~parser() {
        //释放语法树空间
        if (lex)
            delete lex;
    }

    bool parser::move() {
        look = lex->scan();
        DEBUG(printf("   Fetching from lexer: look=%d\n", look->tag);)
        return true;
    }

    void parser::match(int t, const char *ex) {
        if (look->tag == t)
            move();
        else if (look->tag == tags::T_EOF)
            initial_exception("unexpected end-of-file");
        else
            initial_exception(ex);
    }

    void parser::parse() {
        move();
        puts("Generating syntax analyse tree...");
        root = parse_program();
        puts("Generating intermediate code...");
        root->gen();
    }

    Program * parser::parse_program() {
        FUNC_ENTER
        Block * blk = nullptr;
        if (look->tag == tags::MAIN) {
            move();
            match(tags::LB, "expected '(' token");
            match(tags::RB, "expected ')' token");
            blk = parse_block();
        }
        else
            initial_exception("expected 'main' token.");


        return new Program(blk);
    }

    Block * parser::parse_block() {
        FUNC_ENTER
        if (look->tag == tags::LLB) {
            move();
            Stmts * s = parse_stmts();
            match(tags::RLB, "excepted '}' token");

            return new BlockStmts(s);
        }
        else if (BELONGS_TO_FIRST_STMT(look->tag)) {
            Stmt * s = parse_stmt();

            return new BlockStmt(s);
        }
        initial_exception("invaild block");
    }

    Stmts * parser::parse_stmts() {
        FUNC_ENTER
        if (BELONGS_TO_FIRST_STMT(look->tag)) {
                Stmt * s = parse_stmt();
                Stmts * ss = parse_stmts();
                return new Stmts(ss, s);
        }

        return nullptr;
    }

    Stmt * parser::parse_stmt() {
        FUNC_ENTER
        if (look->tag == tags::IF) {
            move();
            match(tags::LB, "expected '(' token after 'if' token");
            auto cond = parse_boolean();
            match(tags::RB, "expected ')' token");
            auto blk = parse_block();
            Else * els = nullptr;
            if (look->tag == tags::ELSE) {
                move();
                els = new Else(parse_block());
            }
            return new If(cond, blk, els);
        }
        else if (look->tag == tags::WHILE) {
            move();
            match(tags::LB, "expected '(' token after 'while' token");
            auto cond = parse_boolean();
            match(tags::RB, "expected ')' token");
            auto blk = parse_block();

            return new While(cond, blk);
        }
        else if (look->tag == tags::ID) {
            word * wid = (word *)look;
            move();
            match(tags::ASSIGN, "expected '=' token in an assign stmt");
            auto e = parse_expr();
            match(tags::FH, "expected ';' token");

            return new Assign(wid, e);
        }
        initial_exception("invaild statement");

    }

    Boolean * parser::parse_boolean() {
        FUNC_ENTER
        auto e1 = parse_expr();
        word * op;
        if (look->tag >= tags::LT && look->tag <= tags::NEQ) {
            op = (word *)look;
            move();
        }
        else initial_exception("invaild condition expression");
        auto e2 = parse_expr();
        return new Boolean(e1, e2, op, 0, 0);
    }

    Arith * parser::parse_expr() {
        if (BELONGS_TO_FIRST_TERM(look->tag)) {
            Arith * t = parse_term();
            while (look->tag == tags::ADD || look->tag == tags::SUB) {
                word * wop = (word*)look;
                move();
                t = new Arith(t, parse_term(), wop);
            }
            return t;
        }
        else initial_exception("Invaild expression");

    }

    Arith * parser::parse_term() {
        FUNC_ENTER
        if (BELONGS_TO_FIRST_FACTOR(look->tag)) {
            Arith * t = parse_factor();
            while (look->tag == tags::MUL || look->tag == tags::DIV) {
                word * wop = (word*)look;
                move();
                t = new Arith(t, parse_factor(), wop);
            }
            return t;
        }
        else initial_exception("Invaild expression");

    }

    Factor * parser::parse_factor() {
        FUNC_ENTER
        if (look->tag == tags::ID) {
            word * wid=(word*)look;
            move();
            return new ID(wid);
        }
        else if (look->tag == tags::NUMBER) {
            number * num = (number*)look;
            move();
            return new Number(num);
        }
        else if (look->tag == tags::LB) {
            move();
            auto e = parse_expr();
            match(tags::RB, "expected ')' in expression");
            return (Factor*)e;
        }
        else
            initial_exception("invaild expression");

    }
}
