#include "infixtopostfix.h"
#include <QStack>
#include <QMessageBox>

Tokens InfixToPostfix::convert()
{
    Tokens result;
    QStack<std::shared_ptr<Operator>> operators_stack;

    auto tokens = this->_input_tokens;

    for (auto token : tokens)
    {
        if (token->isOperand())
        {
            result.append(token);
        }
        else if (token->getType() == TokenType::LeftParenthesis)
        {
            operators_stack.push(std::dynamic_pointer_cast<Operator>(token));
        }
        else if (token->getType() == TokenType::RightParenthesis)
        {
            while (operators_stack.top()->getType() != TokenType::LeftParenthesis) {
                result.append(operators_stack.pop());
            }
            //now we should pop the left parenthesis
            operators_stack.pop();
        }
        else if (token->getType() == TokenType::UnaryOperator ||
                 token->getType() == TokenType::BinaryOperator)
        {
            if (operators_stack.isEmpty())
            {
                operators_stack.push(std::dynamic_pointer_cast<Operator>(token));
            }
            else
            {
                /* Now we should compare the precedence of current token
                 * with the one on top of stack, if it has less
                 * or equal precedence, we need to pop the operator
                 * from the stack and apply it first, otherwise
                 * we will push the current token onto stack.
                 */

                while (operators_stack.top()->getType() != TokenType::LeftParenthesis &&
                       (uint)operators_stack.top()->getPrecedence() <= (uint)std::dynamic_pointer_cast<Operator>(token)->getPrecedence())
                {
                    result.append(operators_stack.pop());
                    if (operators_stack.isEmpty()) break;
                }

                operators_stack.push(std::dynamic_pointer_cast<Operator>(token));
            }
        }
    }

    //Now we should pop the stack until it goes empty
    while (!operators_stack.isEmpty())
    {
        result.append(operators_stack.pop());
    }
    return result;
}
