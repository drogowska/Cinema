//
// Created by student on 04.06.2020.
//

#ifndef CINEMAPROJECT_MOVIESREPOSITORY_H
#define CINEMAPROJECT_MOVIESREPOSITORY_H

#include "repositories/VectorRepository.h"
#include "model/typedefs.h"


class MoviesRepository : public VectorRepository<MoviePtr> {
public:
    std::string report() const override;
};

#endif //CINEMAPROJECT_MOVIESREPOSITORY_H
