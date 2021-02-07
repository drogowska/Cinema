//
// Created by student on 09.06.2020.
//

#ifndef CINEMAPROJECT_SEANCESMANAGER_H
#define CINEMAPROJECT_SEANCESMANAGER_H

#include "repositories/SeancesRepository.h"
#include "model/Seance.h"
#include <boost/uuid/uuid_io.hpp>
#include <vector>

class Movie;
class Hall;

class SeancesManager {
private:
    SeancesRepository seancesRepository;
public:
    SeancesManager();

    virtual ~SeancesManager();

    SeancePtr addSeance(const boost::posix_time::ptime &dateAndTime, SeanceType seanceType, MoviePtr movie, HallPtr hall);
    bool removeSeance(SeancePtr &ptr);
    SeancePtr find(const SeancePredicate &predicate);
    std::vector<SeancePtr> findAll(const SeancePredicate &predicate);
    SeancePtr getSeance(boost::uuids::uuid &id);
    SeancePtr getSeance(int index);
    int size();
    int getIndex(const SeancePtr &ptr);
};


#endif //CINEMAPROJECT_SEANCESMANAGER_H
