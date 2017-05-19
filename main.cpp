#include "parser.hpp"
#include <string>

using namespace Miyuki;

int main(){
    parser p("test.txt");
    lexer& lex=*p.lex;
    try {
        p.parse();
        cout << "\n\nPrase done.";
    }
    catch (SyntaxError e) {
        cout << "Error: (at line " << lex.getRow() << ", col " << lex.getColumn() << "): " << e.what() << endl;
    }
    return 0;
}
