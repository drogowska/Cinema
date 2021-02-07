//
// Created by student on 04.06.2020.
//

#ifndef CINEMAPROJECT_VISITORSREPOSITORY_H
#define CINEMAPROJECT_VISITORSREPOSITORY_H

#include "VectorRepository.h"
#include "model/typedefs.h"

class VisitorsRepository :public VectorRepository<VisitorPtr>{
public:
    std::string report() const override;
};

#endif //CINEMAPROJECT_VISITORSREPOSITORY_H
