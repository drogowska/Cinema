//
// Created by student on 04.06.2020.
//

#include "repositories/VisitorsRepository.h"
#include <sstream>
#include "model/Visitor.h"

std::string VisitorsRepository::report() const{
    std::ostringstream out;
    for(int i=0; i<size(); i++)
    {
        out<<data[i]->getVisitorInfo();
    }
    return out.str();
}
