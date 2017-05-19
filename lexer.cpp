#include "lexer.hpp"

namespace Miyuki {
    lexer::lexer(const char * file_path) {
        file.open(file_path, ios_base::in | ios_base::out);
        if (!file)
            throw IOException();
    }

    void lexer::readch() {
        file.get(peak);
        column++;
    }

    void lexer::retract() {
        file.unget().unget();
        file.get(peak);
        column--;
    }

    token * lexer::scan() {
        readch();
        // Process spaces, tabs, newline and comments
        for (; ; readch()) {
            if (file.eof())
                return new word("#", tags::T_EOF);
            if (peak == ' ' || peak == '\t')
                continue;
            else if (peak == '\n') {
                row++;
                column = 0;
            }
            else if (peak == '/') {
                readch();
                if (peak == '/') {
                    for (; ; readch()) {
                        if (peak == '\n') {
                            row++;
                            column = 0;
                            break;
                        }
                        if (file.eof()) {
                            return new word("#", tags::T_EOF);
                        }
                    }
                }
                else if (peak == '*') {
                    readch();
                    for (; ; readch()) {
                        if (file.eof())
                            throw SyntaxError("Comment not closed.");
                        if (peak == '\n') {
                            row++;
                            column = 0;
                        }
                        if (peak == '*') {
                            readch();
                            if (peak == '/') {
                                break;
                            }
                            else retract();
                        }
                    }
                }
                else {
                    retract();
                    break;
                    // if code runs here, it represent that the '/' is as a divide instead of a comment
                    // So break from here
                }
            }
            else
                break;
        }
        //Digits
        if (isdigit(peak)) {
            int ival = 0;
            for (; isdigit(peak); readch()) {
                ival = ival * 10 + peak - '0';
            }
            retract();
            return new number(ival);
        }
        //Indetifers
        bool reach_end = false;
        if (isalpha(peak) || peak == '_') {
            string id = "";
            for (; isalnum(peak) || peak == '_'; readch()) {
                if (file.eof()) {
                    reach_end = true;
                    break;
                }
                id += peak;
            }
            if (!reach_end)
                retract();
            if (id == "main")
                return &word::Main;
            if (id == "int")
                return &word::Int;
            if (id == "char")
                return &word::Char;
            if (id == "else")
                return &word::Else;
            if (id == "for")
                return &word::For;
            if (id == "if")
                return &word::If;
            if (id == "while")
                return &word::While;
            word * t = new word(id, tags::ID);
            return t;
        }
        //Operators
        if (peak == '!') {
            readch();
            if (peak == '=')
                return &word::Neq;
            retract();
            throw SyntaxError((string("unexpected '")+peak+"' in context").c_str());
        }
        if (peak == '=') {
            readch();
            if (peak == '=')
                return &word::Eq;
            retract();
            return &word::Assign;
        }
        if (peak == '<') {
            readch();
            if (peak == '=')
                return &word::Lte;
            retract();
            return &word::Lt;
        }
        if (peak == '>') {
            readch();
            if (peak == '=')
                return &word::Gte;
            retract();
            return &word::Gt;
        }
        if (peak == '+') {
            return &word::Add;
        }
        if (peak == '-') {
            return &word::Sub;
        }
        if (peak == '*') {
            return &word::Mul;
        }
        if (peak == '/') {
            return &word::Div;
        }
        if (peak == '(')
            return &word::Lb;
        if (peak == ')')
            return &word::Rb;
        if (peak == '{')
            return &word::Llb;
        if (peak == '}')
            return &word::Rlb;
        if (peak == ';')
            return &word::Fh;
        throw SyntaxError((string("unexpected '")+peak+"' in context").c_str());
    }

    int lexer::getColumn() {
        return column;
    }

    int lexer::getRow() {
        return row;
    }

    lexer::~lexer() {
        if (file)
            file.close();
    }
}
