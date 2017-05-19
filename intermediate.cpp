#include "intermediate.hpp"
#include "symbols.hpp"

using namespace std;

namespace Miyuki {

    std::deque<Quad> quads;
    map<int, int> labels;

    void EmitQuad(int o, Factor *o1, Factor *o2, Factor * re) {
        quads.push_back(Quad(o, o1,o2, re));
    }

    void emitLabel(int n) {
        labels.insert({ n, quads.size() });
        //cout << "L" << n << ":";
    }

    void replace() {
        for (auto it=quads.begin(); it!=quads.end(); ++it) {
            Quad& t = *it;
            if (t.opcode <= Quad::Opcode::J && t.opcode >= Quad::Opcode::JEQ) {
                //result国定作为Lable的标签
                printf("Label %d -> %d\n", ((Label*)t.result)->id, (*labels.find(((Label*)t.result)->id)).second);
                ((Label*)t.result)->id = (*labels.find(((Label*)t.result)->id)).second;

            }
        }
    }

    void print() {
        int i = 0;
        for (auto it=quads.begin(); it!=quads.end(); ++it) {
            cout << "(" << (i++) << ")  ";
            Quad& t = *it;
            cout << "( ";
            cout << t.OpcodeName[t.opcode] << ",  ";
            if (t.op1) t.op1->pAddr();
            cout << ",  ";
            if (t.op2) t.op2->pAddr();
            cout << ",  ";
            if (t.result) t.result->pAddr();
            cout << ")\n";
        }
        cout << "(" << (i++) << ")  ";
    }
}
