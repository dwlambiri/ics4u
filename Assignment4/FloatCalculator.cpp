
#include "FloatCalculator.hpp"

Calculator::Calculator(std::string&);

float Calculator::add(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    return value2 + value1;
}

float Calculator::subtract(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    return value2 - value1;
}

float Calculator::multiply(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    return value2 * value1;
}

float Calculator::divide(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    return value2 / value1;
}
