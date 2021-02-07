//
// Created by student on 06.06.2020.
//

#include "repositories/HallsRepository.h"
#include <sstream>
#include "model/Hall.h"

using namespace std;

string HallsRepository::report() const {
    std::ostringstream out;
    for(int i=0; i<size(); i++)
    {
        out<<data[i]->getHallInfo();
    }
    return out.str();
}




