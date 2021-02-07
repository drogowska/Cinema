//
// Created by student on 08.06.2020.
//

#ifndef CINEMAPROJECT_SEANCESREPOSITORY_H
#define CINEMAPROJECT_SEANCESREPOSITORY_H


#include "repositories/VectorRepository.h"
#include "model/typedefs.h"


class SeancesRepository : public VectorRepository<SeancePtr> {
public:

    std::string report() const override;
};


#endif //CINEMAPROJECT_SEANCESREPOSITORY_H
