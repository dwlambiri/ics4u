
#include "FloatStack.hpp"
#include "FloatStack.cpp"
#include <iostream>
#include <string>

class Calculator : FloatStack{
public:
    Calculator(std::string&);

    float add();

    float subtract();

    float multiply();

    float divide();

private:
    std::string expression;
};
