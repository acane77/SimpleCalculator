#ifndef _MIYUKI_EXCEPTIONS_HPP
#define _MIYUKI_EXCEPTIONS_HPP

#include "include.h"

namespace Miyuki {
	class IOException : public std::exception {
	public:
		const char * what() { return "I/O Exception"; }
	};

	class SyntaxError : public std::exception {
	public:
		std::string err_msg;
		SyntaxError(const char * msg):err_msg(msg) {}
		const char * what() { return err_msg.c_str(); }
	};
}

#endif
