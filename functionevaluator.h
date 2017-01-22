#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H
#include <QPair>
#include <QList>

class FunctionEvaluator
{
private:
    QString _input_string = "";
    QList<QPair<QString,double>> values;

    bool isUnknownVariable(QString variable_name);
    double getVariableValue(QString variable_name);
public:
    FunctionEvaluator();
    FunctionEvaluator(QString input_string,
                      const QList<QPair<QString,double>>& varibales_list);

    double evaluate();
    double evaluate(QString input_string);

    bool updateVariableValue(QString variable_name,
                             double value);
};

#endif // FUNCTIONEVALUATOR_H
