#ifndef CINEMAPROJECT_RESERVATIONSREPOSITORY_H
#define CINEMAPROJECT_RESERVATIONSREPOSITORY_H

#include "model/typedefs.h"
#include "repositories/VectorRepository.h"



class ReservationsRepository : public VectorRepository<ReservationPtr> {
public:

    std::string report() const override;
};


#endif //CINEMAPROJECT_RESERVATIONSREPOSITORY_H
