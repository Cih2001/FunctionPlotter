# FunctionPlotter

Function Plotter is a simple C++ (Qt) program which takes a mathematical function definition "f(x)" as it's input and illustrates it on a two-dimensional graph (x-y). The figure in below, show the program in runtime.

![Fig.1](/linux_64bit-Release/Screenshot from 2017-01-23 17-37-24.png?raw=true "Screenshot 1")

## Purpose of the project

Imagine that you're writing an industrial program to control a universal testing machine, which one of it's functions is to compress metals and measure the force throughout the experiment. Let's assume that a client comes to you and asks for computing the pressure from the formula 'P=F/A'. Easy peasy! We can implement this equation in our program in the blink of an eye. but what if other customers require different formulas? What happens if someone asks you to allow him to enter his formula dynamically into the application in runtime, while there can be countless equations defined? Well, to cope with situations like these (when you don't know the mathematical function definition at compile time), you will need a Function Evaluation Algorithm.

There exist a vast collection of function assessment algorithms. The most simple and trivial one which is also the basis of our program is explained expressively in [here](http://interactivepython.org/runestone/static/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html). We will also explain it in a quick way.

The evaluation algorithm is obvious and easy to implement, but the main issue is to find a practical way to implement enormous operators that can be used to form an equation. Beside elementary and basic arithmetic operators like ( +, *, ^ and etc), functions like 'sin' and 'log' can be constituted mathematical operations. This is why the primary focus of this project is on design patterns rather than the algorithm itself.
