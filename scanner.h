#ifndef SCANNER_H
#define SCANNER_H
#include <QList>
#include "operators.h"
#include <memory>
#include <vector>

typedef QList<std::shared_ptr<Token>> Tokens;

class Scanner
{
private:

    QString _input_string = "";

public:
    Scanner() = delete;
    ~Scanner();
    Scanner(QString input_string)
    {
        _input_string = input_string;
    }

    Tokens scan();

};

#endif // SCANNER_H
