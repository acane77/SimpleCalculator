#ifndef _MIYUKI_SYMBOL_HPP
#define _MIYUKI_SYMBOL_HPP

#include "include.h"
#include "define.hpp"
#include "token.hpp"

namespace Miyuki {
    class Block;
    class Stmts;
    class Stmt;
    class Boolean;
    class Arith;
    class Term;
    class Factor;
    class Temp;

    class node {
    public:
       node() {}
       //virtual void gen() { THROW_NOT_IMPLEMENTED_EXCEPTION(); }
    };

    class Program : public node {
    public:
        Block * blk;

        Program(Block * b): blk(b) {}
        void gen();
    };

    class Block : public node {
    public:
        virtual void gen(int next) = 0;
    };

    class BlockStmts : public Block {
    public:
        Stmts * stmts;

        BlockStmts(Stmts * s):stmts(s) { }
        void gen(int next);
    };

    class BlockStmt : public Block {
    public:
        Stmt * stmt;

        BlockStmt(Stmt * s): stmt(s) {}
        void gen(int next);
    };

    class Stmts : public node {
    public:
        int lbl_next;
        Stmts* stmts1;
        Stmt*  stmt;

        void gen(int next);

        Stmts(Stmts *s1, Stmt* s): stmts1(s1), stmt(s) { }
    };

    class Stmt : public node {
    public:
        static int s_label;

        enum StmtType{IF, WHILE, ASSIGN};
        StmtType stmttype;

        virtual void gen(int next) = 0;
    };

    class Else : public node {
    public:
        Block * blk;

        void gen(int next);
        Else(Block * b):blk(b) {}
    };

    class If : public Stmt {
    public:
        Boolean * cond;
        Block * blk;
        Else * els;

        If(Boolean* c, Block* b, Else* e): cond(c), blk(b), els(e) {
            stmttype = StmtType::IF;
        }

        void gen(int next);
    };

    class While : public Stmt {
    public:
        Boolean * cond;
        Block * blk;

        While(Boolean* c, Block* b): cond(c), blk(b) {
            stmttype = StmtType::WHILE;
        }

        void gen(int next);
    };

    class Assign: public Stmt {
    public:
        word * wid;
        Arith * expr;

        Assign(word * w, Arith * e):wid(w), expr(e) {
            stmttype = StmtType::ASSIGN;
        }

        void gen(int next);
    };

    class Arith : public node {
    public:
        Arith * arith1;
        Arith * arith2;
        word * op;
        Factor * addr;

        Arith(Arith* a1, Arith* a2, word * o);

        virtual void gen();
        virtual bool isFactor() { return false; }
    };

    class Factor: public Arith {
    public:
        int ftype;

        Factor():Arith(nullptr, nullptr,nullptr) {}
        bool isFactor() { return true; }

        void gen();
        void pAddr();
    };

    class Number : public Factor {
    public:
        number * num;

        Number(number * n): num(n) { ftype=tags::NUMBER; }

    };

    class ID : public Factor {
    public:
        word * id;

        ID(word * i): id(i) { ftype=tags::ID; }
    };

    class Boolean : public node {
    public:
        Arith * expr1, * expr2;
        word * op;
        int ltrue, lfalse;

        Boolean(Arith* e1, Arith* e2, word * o, int t, int f) : expr1(e1), expr2(e2), ltrue(t), lfalse(f), op(o) {}

        void gen(int t, int f);
    };

    class Temp : public Factor {
    public:
        static int s_tempid;
        int id;
        Temp() { id = s_tempid++; ftype=tags::TEMP; addr=this; }
    };

    class Label: public Factor {
    public:
        int id;
        Label(int i):id(i) { ftype=tags::LABEL; addr=this; }
    };
}

#endif
