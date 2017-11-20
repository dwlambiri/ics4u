/*****************************************************************************
 *	Name:   Darius W Lambiri (dwlambiri)
 *	File:   test_converter.cpp
 *	Course: ICS4U
 *	Date:   Oct 16, 2017
 *
 *	Purpose: Reads in a numerical expression into a string
            then it calculates and prints the result.
 *
 *	Usage:   The user must write a numerical expression with spaces separating
                the numbers and operators.
 *
 *	Revision History:
 *
 *	Known Issues: If the user improperly formats their expression then the program
                    will not be able to read it and produce the error that it
                    cannot read the operator.
 *
 *****************************************************************************/
#include <iostream>
#include <apstring.h>
#include <apstring.cpp>
#include <stdlib.h>     /* atoi */

int main(){
    //Prompts user for input
    std::cout << "Enter your expression, make sure to put spaces between terms and operators" << std::endl
        << "Ex: 253 * 12" << std::endl;
    apstring superstring;
    //Reads the user input
    getline(std::cin, superstring);

    //Finds the first available space
    int spacePlace = superstring.find(' ');
    if (spacePlace <= 0){
        std::cout << "INVALID INPUT" << spacePlace << std::endl;
        return 1;
    }
    //reads the input into another string and converts it to an int
    apstring tempNumber1 = superstring.substr(0, spacePlace);
    int num1 = atoi(tempNumber1.c_str());
    //finds the operator
    char operation = superstring[spacePlace + 1];
    //string used to encapsulate the second number
    apstring tempNumber2;
    for (int i = spacePlace + 3; i < superstring.length() ; i++){
        tempNumber2 += superstring[i];
    }

    int num2 = atoi(tempNumber2.c_str());
    //preforms an operation based on the user entered operator
    switch (operation){
    case '+':
        std::cout << "=" << num1 + num2 << std::endl;
        break;
    case '-':
        std::cout << "=" << num1 - num2 << std::endl;
        break;
    case '*':
        std::cout << "=" << num1 * num2 << std::endl;
        break;
    case '/':
        std::cout << "=" << num1 / num2 << std::endl;
        break;
    default:
        std:: cout << "ERROR INVALID OPERATOR";
        break;
    }
    return 0;
}
