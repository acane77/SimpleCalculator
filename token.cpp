#include "token.hpp"

namespace Miyuki {
	word
		word::Main("main", tags::MAIN),
		word::Int("int", tags::INT),
		word::Char("char", tags::CHAR),
		word::If("if", tags::IF),
		word::Else("else", tags::ELSE),
		word::For("for", tags::FOR),
		word::While("while", tags::WHILE),

		word::Assign("=", tags::ASSIGN),
		word::Add("+", tags::ADD),
		word::Sub("-", tags::SUB),
		word::Mul("*", tags::MUL),
		word::Div("/", tags::DIV),
                word::Lb("(", tags::LB),
                word::Rb(")", tags::RB),
                word::Llb("{", tags::LLB),
                word::Rlb("}", tags::RLB),
                word::Fh(";", tags::FH),

                word::Lt("<", tags::LT),
                word::Lte("<=", tags::LTE),
                word::Gt(">", tags::GT),
                word::Gte(">=", tags::GTE),
                word::Eq("==", tags::EQ),
                word::Neq("!=", tags::NEQ);
}
