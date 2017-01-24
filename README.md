# FunctionPlotter

Function Plotter is a simple C++ (Qt) program which takes a mathematical function definition "f(x)" as it's input and illustrates it on a two-dimensional graph (x-y). The figure in below, shows the program in runtime.

![Fig.1](/linux_64bit-Release/Screenshot from 2017-01-23 17-37-24.png?raw=true "Screenshot 1")

## Purpose of the project

Imagine that you're developing an industrial program to control a universal testing machine, which one of it's functions is to compress metals and measure the force throughout the experiment. Let's assume that a client comes to you and asks for computing the pressure from the formula 'P=F/A'. Easy peasy! We can implement this equation in our program in the blink of an eye. but what if other customers require different formulas? What happens if someone asks you to allow him to enter his formula dynamically into the application in runtime, while there can be countless equations defined? Well, to cope with situations like these (when you don't know the mathematical function definition at compile time), you will need a Function Evaluation Algorithm.

There exist a vast collection of function assessment algorithms. The most simple and trivial one which is also the basis of our program is explained expressively in [here](http://interactivepython.org/runestone/static/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html). We will also explain it in a quick way.

The evaluation algorithm is obvious and easy to implement, but the main issue is to find a practical way to implement enormous operators that can be used to form an equation. Beside elementary and basic arithmetic operators like ( +, *, ^ and etc), functions like 'sin' and 'log' can be constituted mathematical operations. This is why the primary focus of this project is on design patterns rather than the algorithm itself.

## Designing the application

### Quick review of the function evaluation alghorithm

Ordinary logical formulae are represented in Infix notation that is characterized by the placement of operators between operands (like 2 + 3). This notation is human readable but since it can be ambitious, it necessitates the usage of parenthesis. It's also more difficult to parse by computers compared to Postfix notation (like 2 3 +). Therefore the overall steps is to:

1. Scan the input formula (Tokenizing the Infix notation)
2. Convert an Infix notation of the formula  into Postfix notation.
3. Evaluate the Postfix notation.

#### Scanning the input formula

Different operators have different behaviors but all of them are presented to us as an input string, this is why being able to differentiate them is utterly essential. For example "x\*sin(x)" is split into 6 **Tokens** :

- x
- \*
- sin
- (
- x
- )

Fortunately, the algorithm is quite simple. we can parse the input string from left to right and match any recognized operator by its mathematical symbol.

#### Infix to Postfix

The extensive explanation can be found [here](http://interactivepython.org/runestone/static/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html#conversion-of-infix-expressions-to-prefix-and-postfix). A quick ad hoc method for this conversion consists of these steps:

1. Fully parenthesize the expression
2. (Start from the most inner expression and) move the operator between each pair of parentheses right before enclosing parenthesis.
3. Remove all parenthesis.

For example, The converted version of A + B \* C (as it is illustrated below) is A B C \* +
![Fig.2](http://interactivepython.org/runestone/static/pythonds/_images/moveright.png?raw=true "Infix to Postfix ad hoc method")

But the algorithmic way to perform the conversion using the operators stack includes these steps:
(Parsing tokens from start to end)

1. If current token is an Operand -> add it to output
2. If current token is Left Parenthesis -> push it into the stack
3. If current token is Right Parenthesis -> pop the stack until corresponding Left Parenthesis, add each token to output
4. If current token is an Operator ->
  - if it has less or equal precedence compared to the operator on the top of the stack  -> pop the token from the stack and add it to output, then push the current privileged one into stack.
   - if it has higher precedence compared to the operator on the top of the stack or the stack is empty -> push it into the stack
5. Do above steps for all tokens (from left to right) until it finishes
6. If the input string is finished (all tokens are parsed) -> pop the remaining operators in the stack and add them to output.

The figure below shows the steps of converting A \* B + C \* D into A B \* C D \* +
![Fig.2](http://interactivepython.org/runestone/static/pythonds/_images/intopost.png?raw=true "Infix to Postfix using stack")

#### Postfix Evaluation

A stack is again the data structure of choice. However, as you scan the postfix expression, it is the operands that must wait, not the operators as in the conversion algorithm above. The algorithm is simple (parsing the Postfix expression from left to right):

1. whenever an operand is seen on the input -> push it into stack
2. whenever an operator is seen on the input ->
  - if it's a binary operator -> pop the stack two times and apply the operator on them, push the result back into the stack 
  - if it's an unary operator -> pop the stack, apply the operator on it and push the result back into the stack.
3. Do above steps for all tokens (from left to right) until it finishes
4. The should be a sole result of the evaluation remained in the stack.

The figure below shows the steps of evaluating 4 5 6 \* + ( which is  4 + 5 \* 6 = 34)
![Fig.2](http://interactivepython.org/runestone/static/pythonds/_images/evalpostfix1.png?raw=true "Postfix Evaluation")

### The Design Patterns

As it is explained, this application is composed of three major parts. Scanner, Infix to Postfix Converter and Postfix Evaluator. In regards to SRP (Single Responsibility Pattern) we implement each part into a separate class. For the sake of OCP (Open Closed Principle), we design the program in a way that adding new operators doesn't force any change or modification in these classes.

#### SRP
For each phase of the algorithm, a separated class is defined like below and each class has a sole unique responsibility.
```c++
typedef QList<std::shared_ptr<Token>> Tokens;
class Scanner
{
  ...
public:
    Scanner(QString input_string);
    Tokens scan();
};
class InfixToPostfix
{
  ...
public:
    InfixToPostfix(Tokens& infix_tokens);
    Tokens convert();
};
class FunctionEvaluator
{
...
public:
    FunctionEvaluator(Tokens& postfix_tokens)
    double evaluate(const QList<QPair<QString,double>>& variables_list);
};
```
#### OCP

The reaffirmation of extending operands and respecting OCP is the tricky part. Defining new operators is simply manageable. however, the scanner class should know about newly defined operators, same as postfix evaluator and convertor classes. So they should be modified each time we wanted to add a new operator. This fact leaves our design Open to Modifications, which is terrible! OCP says that software entities should be open for extension but closed for modification.

#### How to extend program by adding a custom operator

## Source code explanation

## Improvements

### Improve the quality of the code

### Implement an interface for Scanner

### Add a syntax checker to scanner

## Future plan
