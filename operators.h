#ifndef OPERATORS_H
#define OPERATORS_H

#include "token.h"
#include <math.h>
#include <memory>

class Sgn final : public UnaryOperator
{
public:
    static std::shared_ptr<Sgn> checkAndCreate (QString& str)
    {
        return (str == "sgn") ? std::make_shared<Sgn>() : nullptr;
    }
    Sgn()
    {
        _lexical_form = "sgn";
        _precedence = OperatorPrecedence::Functions;
    }
    double evaluate(double left_operand) override
    {
        return (left_operand == 0 ) ? 0 : (left_operand > 0) ? 1 : -1;
    }
};

class Cos final : public UnaryOperator
{
public:
    static std::shared_ptr<Cos> checkAndCreate (QString& str)
    {
        return (str == "cos") ? std::make_shared<Cos>() : nullptr;
    }
    Cos()
    {
        _lexical_form = "cos";
        _precedence = OperatorPrecedence::Functions;
    }
    double evaluate(double left_operand) override
    {
        return std::cos(left_operand);
    }
};

class Sin final : public UnaryOperator
{
public:
    static std::shared_ptr<Sin> checkAndCreate (QString& str)
    {
        return (str == "sin") ? std::make_shared<Sin>() : nullptr;
    }
    Sin()
    {
        _lexical_form = "sin";
        _precedence = OperatorPrecedence::Functions;
    }
    double evaluate(double left_operand) override
    {
        return std::sin(left_operand);
    }
};

class Division final : public BinaryOperator
{
public:
    static std::shared_ptr<Division> checkAndCreate (QString& str)
    {
        return (str == "/") ? std::make_shared<Division>() : nullptr;
    }
    Division()
    {
        _lexical_form = "/";
        _precedence = OperatorPrecedence::Multipications;
    }
    double evaluate(double left_operand, double right_operand) override
    {
        if (right_operand == 0)
        {
            //TODO: devision by zero
            return 0;
        }
        return left_operand / right_operand;
    }
};

class Power final : public BinaryOperator
{
public:
    static std::shared_ptr<Power> checkAndCreate (QString& str)
    {
        return (str == "^") ? std::make_shared<Power>() : nullptr;
    }
    Power()
    {
        _lexical_form = "^";
        _precedence = OperatorPrecedence::Power;
    }
    double evaluate(double left_operand, double right_operand) override
    {
        return std::pow(left_operand,right_operand);
    }
};

class UnarySubtraction final : public UnaryOperator
{
public:
    static std::shared_ptr<UnarySubtraction> checkAndCreate (QString& str)
    {
        return (str == "-") ? std::make_shared<UnarySubtraction>() : nullptr;
    }

    UnarySubtraction()
    {
        _lexical_form = "-";
        _precedence = OperatorPrecedence::UnaryOperations;
    }

    double evaluate(double left_operand) override
    {
        return -left_operand;
    }
};

class Addition final : public BinaryOperator
{
public:
    static std::shared_ptr<Addition> checkAndCreate (QString& str)
    {
        return (str == "+") ? std::make_shared<Addition>() : nullptr;
    }

    Addition()
    {
        _lexical_form = "+";
        _precedence = OperatorPrecedence::Additions;
    }

    double evaluate(double left_operand, double right_operand) override
    {
        return left_operand + right_operand;
    }
};

class Subtraction final : public BinaryOperator
{
public:
    static std::shared_ptr<Subtraction> checkAndCreate (QString& str)
    {
        return (str == "-") ? std::make_shared<Subtraction>() : nullptr;
    }

    Subtraction()
    {
        _lexical_form = "-";
        _precedence = OperatorPrecedence::Additions;
    }

    double evaluate(double left_operand, double right_operand) override
    {
        return left_operand - right_operand;
    }
};

class Multipication final : public BinaryOperator
{
public:
    static std::shared_ptr<Multipication> checkAndCreate (QString& str)
    {
        return (str == "*") ? std::make_shared<Multipication>() : nullptr;
    }

    Multipication()
    {
        _lexical_form = "*";
        _precedence = OperatorPrecedence::Multipications;
    }

    double evaluate(double left_operand, double right_operand) override
    {
        return left_operand * right_operand;
    }
};

class OperatorFactory
{
    typedef QList<std::shared_ptr<Operator> (*)(const QString&)> OperatorsConstructors;
public:
    static std::shared_ptr<Operator> create(const QString& sign, bool unary_sub = false)
    {
        OperatorsConstructors operators_constructors;
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Addition::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Subtraction::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Multipication::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Power::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Division::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Sin::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Cos::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Sgn::checkAndCreate));
        /*
         * Append other operators here.
         */

        if (sign == "(") return std::make_shared<LeftParenthesis>();
        if (sign == ")") return std::make_shared<RightParenthesis>();
        if (unary_sub && sign == "-") return std::make_shared<UnarySubtraction>();
        for (auto operator_constructor : operators_constructors)
        {
            std::shared_ptr<Operator> op (operator_constructor(sign));
            if (op != nullptr) return op;
        }

        return nullptr;
    }
};
#endif // OPERATORS_H
