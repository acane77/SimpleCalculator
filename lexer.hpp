#ifndef _MIYUKI_LEXER_HPP
#define _MIYUKI_LEXER_HPP

#include "include.h"
#include "token.hpp"
#include "exceptions.hpp"

namespace Miyuki {
	class lexer {
            char peak=' ';
            int row=0;
            int column=0;
            fstream file;

            void readch();
            void retract();
	public:
            lexer(const char* file_path);
            ~lexer();
            token * scan();
            int getRow();
            int getColumn();
	};
}

#endif
