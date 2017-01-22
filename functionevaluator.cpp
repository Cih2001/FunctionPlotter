#include "compilesettings.h"
#include "functionevaluator.h"
#include "infixtopostfix.h"
#include "token.h"
#include "operators.h"
#include <QMessageBox>
#include <QStack>
bool FunctionEvaluator::isUnknownVariable(QString variable_name)
{
    for (auto variable : values)
    {
        if (variable.first == variable_name) return false;
    }
    return true;
}

double FunctionEvaluator::getVariableValue(QString variable_name)
{
    for (auto variable : values)
    {
        if (variable.first == variable_name)
            return variable.second;
    }

    //TODO: if we reach here we should raise an error signal
#if DEBUG_ENABLED <= 2
    QMessageBox::critical(nullptr,variable_name,"Value cannot be found");
#endif
    return 0;
}

FunctionEvaluator::FunctionEvaluator()
{
    _input_string = "";
    values.clear();
}

FunctionEvaluator::FunctionEvaluator(QString input_string,
                                     const QList<QPair<QString, double> > &varibales_list)
{
    values.clear();
    _input_string = input_string;

    if (varibales_list.empty()) return;

    for (auto pair : varibales_list)
    {
        values.append(pair);
    }
}

double FunctionEvaluator::evaluate()
{
    if (_input_string == "")
    {
        //TODO: we need to raise an error
        return 0;
    }

    InfixToPostfix infix_to_postfix(_input_string);
    QStack<double> evaluation_stack;
    auto post_fix_expression = infix_to_postfix.convert();
    for (auto token : post_fix_expression)
    {
        if (token->getType() == TokenType::Literal)
        {
            std::shared_ptr<Literal<double>> literal_token= std::dynamic_pointer_cast<Literal<double>>(token);
            evaluation_stack.push(literal_token->getValue());
        }
        else if (token->getType() == TokenType::Varibale)
        {
            std::shared_ptr<Variable<double>> variable_token = std::dynamic_pointer_cast<Variable<double>>(token);
            if (isUnknownVariable(variable_token->toString()))
            {
                #if DEBUG_ENABLED <= 2
                QMessageBox::critical(nullptr,variable_token.toString(),"Value cannot be found");
                #endif
                //TODO: we need to raise an error event
                return 0;
            }
            else
            {
                evaluation_stack.push(getVariableValue(variable_token->toString()));
            }
        }
        else if (token->getType() == TokenType::BinaryOperator)
        {
            if (evaluation_stack.size() < 2)
            {
                //TODO: there should be an error with the input_string
                //If the input_string was correct, this situation couldn't have happened.
                #if DEBUG_ENABLED <= 2
                QMessageBox::critical(nullptr,"Function Evaluator","Not enough values in the stack");
                #endif
                return 0;
            }

            double v1 = evaluation_stack.pop();
            double v2 = evaluation_stack.pop();

            std::shared_ptr<BinaryOperator> binary_op_token = std::dynamic_pointer_cast<BinaryOperator>(token);
            evaluation_stack.push(binary_op_token->evaluate(v2,v1));
        }
        else if (token->getType() == TokenType::UnaryOperator)
        {
            if (evaluation_stack.isEmpty())
            {
                //TODO: there should be an error with the input_string
                //If the input_string was correct, this situation couldn't have happened.
                #if DEBUG_ENABLED <= 2
                QMessageBox::critical(nullptr,"Function Evaluator","Not enough values in the stack");
                #endif
                return 0;
            }

            double v1 = evaluation_stack.pop();

            std::shared_ptr<UnaryOperator> binary_op_token = std::dynamic_pointer_cast<UnaryOperator>(token);
            evaluation_stack.push(binary_op_token->evaluate(v1));
        }
    }

    /* If all tokens have parsed successfully
     * and the is no syntactical error in input string
     * there should be only one value in the evaluation stack,
     * which is our result.
     */

    if (evaluation_stack.size() == 1) return evaluation_stack.top();
    else
    {
        //TODO: there should be an error with the input_string
        //If the input_string was correct, this situation couldn't have happened.
        #if DEBUG_ENABLED <= 2
        QMessageBox::critical(nullptr,"Function Evaluator","Some error happend");
        #endif
        return 0;
    }
}

double FunctionEvaluator::evaluate(QString input_string)
{
    _input_string = input_string;
    return evaluate();
}

bool FunctionEvaluator::updateVariableValue(QString variable_name, double value)
{
    if (isUnknownVariable(variable_name)) return false;

    QListIterator<QPair<QString,double>> i(values);

    for (int i = 0; i < values.size(); i++)
        if (values[i].first == variable_name)
        {
            values[i].second = value;
            return true;
        }

    return false;
}
