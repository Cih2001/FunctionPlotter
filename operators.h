#ifndef OPERATORS_H
#define OPERATORS_H

#include "token.h"
#include <math.h>
#include <memory>

/************************* How to create a new operator *************************
 *
 * To create a unary operator, we need to extend this file
 * with a new class respected to the new operator.
 *
 **** Phase.1 : Definition of the operator
 *
 * The class signature for unary operators is like:
 *
 * class OperatorName final : public UnaryOperator
 * {
 * public:
 *     static std::shared_ptr<OperatorName> checkAndCreate (QString& str)
 *     {
 *         return (str == "OperatorSymbol") ? std::make_shared<OperatorName>() : nullptr;
 *     }
 *     Sgn()
 *     {
 *         _lexical_form = "OperatorSymbol";
 *         _precedence = OperatorPrecedence::One_Type_Of_Defined_Precedences;
 *     }
 *     double evaluate(double operand) override
 *     {
 *         double result;
 *
 *         //Implement operator's mathematical logic here,
 *         //the way it affects the operand
 *
 *         return result;
 *     }
 * };
 *
 * Extending operators collection for BinaryOperators is
 * almost the same, The only difference is that it
 * inherits from BinaryOperator base class and also
 * 'evaluate' function signature is:
 *
 * double evaluate(double left_operand, double right_operand) override
 *
 **** Phase.2 :
 *
 * we need to extend OperatorFactory class, so our newly built
 * operator can be recognized and used in scanner. to do this,
 * we need to append this line of code into 'create' function
 * of the OperatorFactory class
 *
 * operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&OperatorName::checkAndCreate));
 */

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
    double evaluate(double operand) override
    {
        return (operand == 0 ) ? 0 : (operand > 0) ? 1 : -1;
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
    double evaluate(double operand) override
    {
        return std::cos(operand);
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
    double evaluate(double operand) override
    {
        return std::sin(operand);
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

    double evaluate(double operand) override
    {
        return -operand;
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
    ///
    /// \brief
    /// This function takes a signature of a possible mathematical operator.
    /// If the symbol is recognize, respected Operator is created and will be returned.
    /// \param sign
    /// The symbol of the mathematical operator, like "*"
    /// \param unary_sub
    /// If true, indicates that "-" represent an unary operator not a binary operator
    /// \return
    /// Pointer to the recognized operator. If nothing is recognized, nullptr will be returned.
    static std::shared_ptr<Operator> create(const QString& sign, bool unary_sub = false)
    {
        OperatorsConstructors operators_constructors;
        /*
         * Append constructors of the other operators here.
         */
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Addition::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Subtraction::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Multipication::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Power::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Division::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Sin::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Cos::checkAndCreate));
        operators_constructors.append((std::shared_ptr<Operator> (*)(const QString&)) (&Sgn::checkAndCreate));

        /*
         * Left parenthesis and Right parenthesis are special.
         * They  exist only in infix notation. so we will treat them
         * differently.
         */
        if (sign == "(") return std::make_shared<LeftParenthesis>();
        if (sign == ")") return std::make_shared<RightParenthesis>();

        if (unary_sub && sign == "-") return std::make_shared<UnarySubtraction>();

        /*
         * Check each defined operator. If any of their mathemathical symbol
         * matches current sign, we will create this operator and return.
         */
        for (auto operator_constructor : operators_constructors)
        {
            std::shared_ptr<Operator> op (operator_constructor(sign));
            if (op != nullptr) return op;
        }

        /*
         * The current sign is not symbol of any recognized operator.
         * so it should be a variable.
         */
        return nullptr;
    }
};
#endif // OPERATORS_H
