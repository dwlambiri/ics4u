#include <iostream>
#include <ctime>
#include <cstdlib>
#include <apvector.h>

bool randomDates(apvector<int> &daysOfYear, int &day){
    for (int i = 0; i < 20; i++){
        int temp = rand()% 365;
        daysOfYear[temp]++;
    }
    for (int i = 0; i < 365; i++){
        if (daysOfYear[i] >= 2){
            day = i;
            return true;
        }
    }
    return false;
}

int main(){
    srand(time(0));
    apvector<int> daysOfYear(365, 0);
    int counter = 0;
    apvector<int> reset(365, 0);

    for (int i = 0; i < 10000; i++){
    daysOfYear = reset;
    int day = -1;
    if (randomDates(daysOfYear, day)){
        std::cout << "2 Birthdays are the same!! Day #: "<< day<< std::endl;
        counter++;
    }
    //else std::cout << "No similar Birthdays" << std::endl;
    }
    std::cout << "Number of times 2 birthdays were the same was " << counter<< "/10000" << std::endl;
    return 0;
}
