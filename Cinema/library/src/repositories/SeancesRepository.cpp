//
// Created by student on 08.06.2020.
//

#include "repositories/SeancesRepository.h"
#include <sstream>
#include "model/Seance.h"

std::string SeancesRepository::report() const{
    std::ostringstream out;
    for(int i=0; i<size(); i++)
    {
        out<<data[i]->getSeanceInfo();
    }
    return out.str();
}
