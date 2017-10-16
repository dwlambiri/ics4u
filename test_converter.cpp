#include <iostream>
#include <apstring.h>
#include <apstring.cpp>
#include <stdlib.h>     /* atoi */

int main(){
    std::cout << "Enter your expression, make sure to put spaces between terms and operators" << std::endl
        << "Ex: 253 * 12" << std::endl;
    apstring superstring;
    getline(std::cin, superstring);

    int spacePlace = superstring.find(' ');
    if (spacePlace <= 0){
        std::cout << "INVALID INPUT" << spacePlace << std::endl;
        return 1;
    }
    //std::cout << "spacePlace ==" << spacePlace<< std::endl;
    apstring tempNumber1 = superstring.substr(0, spacePlace);
    //std::cout << "error1 ";
    int num1 = atoi(tempNumber1.c_str());
    //std::cout << "error2 ";
    char operation = superstring[spacePlace + 1];
    //std::cout << "error3 ";
    apstring tempNumber2;
    //std::cout << "error4 ";
    for (int i = spacePlace + 3; i < superstring.length() ; i++){
        tempNumber2 += superstring[i];
    }
    //std::cout << "error5 ";
    int num2 = atoi(tempNumber2.c_str());
    //std::cout << "error6 ";
    switch (operation){
    case '+':
        std::cout << num1 + num2 << std::endl;
        break;
    case '-':
        std::cout << num1 - num2 << std::endl;
        break;
    case '*':
        std::cout << num1 * num2 << std::endl;
        break;
    case '/':
        std::cout << num1 / num2 << std::endl;
        break;
    default:
        std:: cout << "ERROR YOU'RE GAY ";
        break;
    }
    return 0;
}
