#ifndef CINEMAPROJECT_HALLSREPOSITORY_H
#define CINEMAPROJECT_HALLSREPOSITORY_H

#include "model/typedefs.h"
#include "repositories/VectorRepository.h"

class HallsRepository : public VectorRepository<HallPtr> {
public:
    std::string report() const override;

};


#endif //CINEMAPROJECT_HALLSREPOSITORY_H
