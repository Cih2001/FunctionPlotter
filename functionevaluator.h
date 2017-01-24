#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H
#include <QPair>
#include <QList>
#include <memory>
#include <token.h>

typedef QList<std::shared_ptr<Token>> Tokens;

class FunctionEvaluator
{
private:
    Tokens& _postfix_tokens;
    QList<QPair<QString,double>> values;

    bool isUnknownVariable(QString variable_name);
    double getVariableValue(QString variable_name);
    void updateVariables(const QList<QPair<QString,double>>& variables_list);

public:
    FunctionEvaluator(Tokens& postfix_tokens) : _postfix_tokens(postfix_tokens){}

    double evaluate(const QList<QPair<QString,double>>& variables_list);


};

#endif // FUNCTIONEVALUATOR_H
