
#include "FloatCalculator.hpp"
#include <stdlib.h>
#include <string.h>


Calculator::Calculator(){
	FloatStack();
}

Calculator::~Calculator(){
	~FloatStack();
}

Calculator::Calculator(unsigned int sizeOfStack){
	FloatStack(sizeOfStack);
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
    //This is error checker for divide by zero
    if (value1 == 0){
        return 0;
    }
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
bool Calculator::Commands(char term[]) {

    if (term[0] <= '0' && term[0] >= '9'){
        push(atof(term));
    }
    else if (term[0] != NULL && term[1] == NULL){
        switch(term[0]){
          case '+':
              add();
              break;
          case '-':
              subtract();
              break;
          case '*':
              multiply();
              break;
          case '/':
              divide();
              break;
          default: return false;
        }
    return true;
    }
    return false;
} // end-of-method Calculator::Commands



bool
Calculator::parse(char array[]){

	if (array[0] == NULL){
		return false;
	}
	char * pch = NULL;
	pch = strtok(array," ");

	Commands(pch);

	while (pch != NULL){
		pch = strtok(NULL, " ");
		Commands(pch);
	}

return true;
}

