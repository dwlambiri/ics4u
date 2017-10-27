
#include "FloatCalculator.hpp"


Calculator::Calculator(){
	expression = "";
}

Calculator::~Calculator(){
	delete expression;
}

Calculator::Calculator(std::string& userExpression){
	expression = userExpression;
}

float Calculator::add(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    push(value2 + value1);
    return *top();
}

float Calculator::subtract(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    push(value2 - value1);
    return *top();
}

float Calculator::multiply(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    push(value2 * value1);
    return *top();
}

float Calculator::divide(){
    float value1 = *top();
    pop();
    float value2 = *top();
    pop();
    push(value2 / value1);
    return *top();
}

/**
  ---------------------------------------------------------------------------
   @author  dwlambiri
   @date    Oct 26, 2017
   @mname   Calculator::Commands
   @details
	  \n
  --------------------------------------------------------------------------
 */
bool
Calculator::Commands() {


} // end-of-method Calculator::Commands


