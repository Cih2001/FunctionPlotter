#include "token.h"

Token::Token() {}
Token::~Token() {}

QString Token::toString()
{
    return QString(this->_lexical_form);
}

bool Token::isOperand()
{
    return (uint)this->_type & ((uint)TokenType::Varibale | (uint)TokenType::Literal);
}

Operator::Operator() {}
Operator::~Operator() {}


BinaryOperator::BinaryOperator()
{
    this->_type = TokenType::BinaryOperator;
}
UnaryOperator::UnaryOperator()
{
    this->_type = TokenType::UnaryOperator;
}

LeftParenthesis::LeftParenthesis()
{
    this->_lexical_form = "(";
    this->_type = TokenType::LeftParenthesis;
}

RightParenthesis::RightParenthesis()
{
    this->_lexical_form = ")";
    this->_type = TokenType::RightParenthesis;
}

//template <typename T> Literal<T>::Literal (){}
//template <class T> Literal<T>::Literal (T value)
//{
//    this->_value = value;
//    this->_lexical_form = QString::number(value);
//
//}

template<class T>
T Variable<T>::getValue()
{
    return this->_value;
}

template<class T>
void Variable<T>::setValue(T value)
{
    this->_value = value;
}
