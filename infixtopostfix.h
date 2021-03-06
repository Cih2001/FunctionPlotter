#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include <QList>
#include "operators.h"
#include <memory>

typedef QList<std::shared_ptr<Token>> Tokens;

class InfixToPostfix
{
private:
    Tokens& _input_tokens;
public:
    InfixToPostfix() = delete;
    InfixToPostfix(Tokens& infix_tokens)
        : _input_tokens(infix_tokens) {}

    Tokens convert();
};

#endif // INFIXTOPOSTFIX_H
