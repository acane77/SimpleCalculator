#include "symbols.hpp"
#include "intermediate.hpp"

namespace Miyuki {
    int new_label_id = 0;

    inline int newlabel() {
        return ++new_label_id;
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

        int opcode =-1;
        switch(op->tag) {
        case tags::GT:  opcode=Quad::Opcode::JGT; break;
        case tags::GTE:  opcode=Quad::Opcode::JGTE; break;
        case tags::LT:  opcode=Quad::Opcode::JLT; break;
        case tags::LTE:  opcode=Quad::Opcode::JLTE; break;
        case tags::EQ:  opcode=Quad::Opcode::JEQ; break;
        case tags::NEQ:  opcode=Quad::Opcode::JNEQ; break;
        }

        EmitQuad(opcode, expr1->addr, expr2->addr, new Label(t));
        EmitQuad(Quad::Opcode::J, nullptr, nullptr, new Label(f));
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

        addr = new Temp();
        addr->gen();

        int opcode = -1;
        if (op->tag == tags::ADD)   opcode = Quad::Opcode::ADD;
        else if (op->tag == tags::SUB) opcode = Quad::Opcode::SUB;
        else if (op->tag == tags::MUL) opcode = Quad::Opcode::MUL;
        else if (op->tag == tags::DIV) opcode = Quad::Opcode::DIV;

        EmitQuad(opcode, arith1->addr, arith2->addr, addr);
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
        case tags::LABEL:
            cout << "" << ((Label*)this)->id;
            break;
        }
    }

    void Factor::gen() {
        addr = this;
    }

    void Assign::gen(int next) {
        expr->gen();
        //cout << "\t" << this->wid->lexeme << " = "; expr->addr->pAddr();; cout << endl;

        EmitQuad(Quad::Opcode::MOV, expr->addr, nullptr, new ID(wid));
    }

    void While::gen(int next) {
        int cstart = newlabel();
        int btrue = newlabel();
        int bfalse = next;

        emitLabel(cstart);
        cond->gen(btrue, bfalse);
        emitLabel(btrue);
        blk->gen(next);
        //cout << "\tgoto L" << cstart << endl;
        EmitQuad(Quad::Opcode::J, nullptr, nullptr, new Label(cstart));
    }

    int Temp::s_tempid = 1;
    int Stmt::s_label = 1;
}
