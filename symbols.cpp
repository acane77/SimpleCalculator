#include "symbols.hpp"

namespace Miyuki {
    int new_label_id = 0;

    inline int newlabel() {
        return ++new_label_id;
    }

    inline void emitLabel(int n) {
        cout << "L" << n << ":";
    }

    Arith::Arith(Arith* a1, Arith* a2, word * o):arith1(a1), arith2(a2), op(o) {

    }

    void Program::gen() {
        blk->gen(newlabel());
    }

    void BlockStmts::gen(int next) {
        stmts->gen(next);
    }

    void BlockStmt::gen(int next) {
        stmt->gen(next);
    }

    void If::gen(int next) {
        if (els == nullptr) {
            int btrue = newlabel();
            int bfalse = next;
            cond->gen(btrue, bfalse);
            emitLabel(btrue);
            blk->gen(next);
            //emitLabel(bfalse);
        }
        else {
            int btrue = newlabel();
            int bfalse = newlabel();
            cond->gen(btrue, bfalse);
            emitLabel(btrue);
            blk->gen(next);
            emitLabel(bfalse);
            els->gen(next);
            //emitLabel(next);
        }
    }

    void Else::gen(int next) {
        blk->gen(next);
    }

    void Boolean::gen(int t, int f) {
        expr1->gen();
        expr2->gen();
        cout << "\tif ";

        expr1->addr->pAddr();
        cout << " " << op->lexeme << " ";
        expr2->addr->pAddr();

        cout << " goto L" << t << endl;
        cout << "\tgoto L" << f << endl;
    }

    void Stmts::gen(int next) {
        int lbl = newlabel();
        stmt->gen(lbl);
        emitLabel(lbl);
        if (stmts1)
            stmts1->gen(next);
    }

    void Arith::gen() {

        arith1->gen();
        arith2->gen();
        cout << "\t";

        addr = new Temp();
        addr->gen();

        addr->pAddr();
        cout << " = ";

        arith1->addr->pAddr();
        cout << " " << op->lexeme << " ";
        arith2->addr->pAddr();

        cout << endl;
    }

    void Factor::pAddr() {
        switch (ftype) {
        case tags::NUMBER:
            cout << ((Number*)this)->num->val;
            break;
        case tags::TEMP:
            cout << "t" << ((Temp*)this)->id;
            break;
        case tags::ID:
            cout << ((ID*)this)->id->lexeme;
            break;
        }
    }

    void Factor::gen() {
        addr = this;
    }

    void Assign::gen(int next) {
        expr->gen();
        cout << "\t" << this->wid->lexeme << " = "; expr->addr->pAddr();; cout << endl;
    }

    void While::gen(int next) {
        int cstart = newlabel();
        int btrue = newlabel();
        int bfalse = next;

        emitLabel(cstart);
        cond->gen(btrue, bfalse);
        emitLabel(btrue);
        blk->gen(next);
        cout << "\tgoto L" << cstart << endl;
    }

    int Temp::s_tempid = 1;
    int Stmt::s_label = 1;
}
