#ifndef _MIYUKI_DEFINE_HPP
#define _MIYUKI_DEFINE_HPP

#define THROW_NOT_IMPLEMENTED_EXCEPTION() throw std::runtime_error(std::string(__FUNCTION__) + " is not implemented.");

#define BELONGS_TO_FIRST_FACTOR(x) \
    (x == tags::ID || x == tags::NUMBER || x == tags::LB)

#define BELONGS_TO_FIRST_TERM(x) BELONGS_TO_FIRST_FACTOR(x)

#define BELONGS_TO_FIRST_EXPR(x) BELONGS_TO_FIRST_FACTOR(x)

#define BELONGS_TO_FIRST_STMT(x) \
    (x == tags::IF || x == tags::WHILE || BELONGS_TO_FIRST_EXPR(x) || x == tags::ID )

#define __DEBUG_MODE 0
#if __DEBUG_MODE == 1
#define DEBUG(s) { s }
#else
#define DEBUG(s)
#endif

#define FUNC_ENTER DEBUG(printf("Entering function: %s, look=%d\n", __func__, look->tag);)
#define FUNC_EXIT  DEBUG(printf("Leaving function: %s\n", __func__);)

#endif
