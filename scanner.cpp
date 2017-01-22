#include "scanner.h"
#include <QMessageBox>
#include "token.h"
#include "compilesettings.h"

Scanner::~Scanner()
{
    //QMessageBox::warning(nullptr,"Scanner","Deconstructor called");
}

const QString GENERAL_CHARS = " .ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

bool isNumber(QString str)
{
    bool ok;
    str.toDouble(&ok);
    return ok;
}

Tokens Scanner::scan()
{
    Tokens _tokens;

    if (_input_string == "") return _tokens;

    QString remaining_string = _input_string;
    QString token_string = "";
    QString next_char = "";

    while (remaining_string.size() > 0 || token_string != "")
    {
        next_char = remaining_string[0];

        if (next_char != " ") token_string += next_char;

        remaining_string = remaining_string.right(remaining_string.size()-1);

        if (GENERAL_CHARS.contains(next_char) && GENERAL_CHARS.contains(remaining_string[0])) continue;

        if (isNumber(token_string))
        {
            _tokens.append(std::make_shared<Literal<double>>(token_string.toDouble()));
            #if (DEBUG_ENABLED <= 0)
            QMessageBox::warning(nullptr,"Literal",token_string);
            #endif
        }
        else
        {
            /*
             * If it's not a number, we should try to recognize it,
             * it might be either a variable or an operator.
             *
             *
             * First we check to see if it is an Operator.
             * If we see a "-" sign at the start of the experission or
             * right after "(", it should be interpreted as an unary operator,
             * so we make OperatorFactory aware of this.
             */
            bool canBeUnarySub = _tokens.isEmpty() || (_tokens.last()->getType() == TokenType::LeftParenthesis);

            //Checking for any defined operators:
            OperatorFactory::create(token_string, canBeUnarySub);
            std::shared_ptr<Operator> op (OperatorFactory::create(token_string, canBeUnarySub));
            if (op != nullptr) //An operator is recognized
            {
                _tokens.append(std::dynamic_pointer_cast<Operator>(op));
            }
            else
            {
                //If it's not an operator, it should be considerd a variable
                _tokens.append(std::make_shared<Variable<double>>(token_string));
                #if (DEBUG_ENABLED <= 0)
                QMessageBox::warning(nullptr,"Variable",token_string);
                #endif
            }
        }

        token_string = "";
    }

    return _tokens;
}
