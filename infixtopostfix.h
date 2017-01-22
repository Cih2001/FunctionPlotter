#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H
#include <QString>
#include <QList>
#include "operators.h"
#include <memory>

typedef QList<std::shared_ptr<Token>> Tokens;

class InfixToPostfix
{
private:
    QString _input_string = "";

public:
    InfixToPostfix() = delete;
    InfixToPostfix(const QString& input_string)
        : _input_string(input_string) {}

    Tokens convert();

    QString toString();
};

#endif // INFIXTOPOSTFIX_H
