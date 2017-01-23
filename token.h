#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

enum OperatorPrecedence {
    Functions = 0 ,
    UnaryOperations = 1,
    Power = 2,
    Multipications = 3,
    Additions = 4,
};
enum class TokenType {
    Literal = 0x1,
    LeftParenthesis = 0x2,
    RightParenthesis = 0x4,
    UnaryOperator = 0x8,
    BinaryOperator = 0x10,
    Varibale = 0x20
};


class Token
{
public:
    Token();
    virtual ~Token() = 0;

    QString toString();
    bool isOperand();
    TokenType getType() {return _type;}
protected:
    QString _lexical_form = "";
    TokenType _type;
};

class Operator : public Token
{
public:
    Operator();
    virtual ~Operator() = 0;

    OperatorPrecedence getPrecedence();
protected:
    OperatorPrecedence _precedence;
};

class UnaryOperator : public Operator
{
public:
    UnaryOperator();
    virtual double evaluate(double operand) = 0;
};


class BinaryOperator : public Operator
{
public:
    BinaryOperator();
    virtual double evaluate(double left_operand, double right_operand) = 0;
};

class LeftParenthesis final : public Operator
{
public:
    LeftParenthesis ();
};


class RightParenthesis final : public Operator
{
public:
    RightParenthesis ();
};

template <class T> class Literal : public Token
{
public:
    Literal ()
    {
        this->_type = TokenType::Literal;
    }
    Literal (T value)
    {
        this->_value = value;
        this->_lexical_form = QString::number(value);
        this->_type = TokenType::Literal;
    }

    T getValue() {return _value;}
protected:
    T _value;
};

template <class T> class Variable : public Token
{
public:
    Variable ()
    {
        this->_type = TokenType::Varibale;
    }
    Variable (const QString& name)
    {
        this->_lexical_form = name;
        this->_type = TokenType::Varibale;
    }

    T getValue();
    void setValue(T value);
protected:
    T _value;
};


#endif // TOKEN_H
