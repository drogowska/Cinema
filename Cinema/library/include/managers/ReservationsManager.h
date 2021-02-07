//
// Created by student on 11.06.2020.
//

#ifndef CINEMAPROJECT_RESERVATIONSMANAGER_H
#define CINEMAPROJECT_RESERVATIONSMANAGER_H

#include "repositories/ReservationsRepository.h"
#include <boost/uuid/uuid_io.hpp>
#include <vector>

class Seance;
class Visitor;

class ReservationsManager {
private:
    ReservationsRepository reservationsRepository;
public:
    ReservationsManager();

    virtual ~ReservationsManager();

    ReservationPtr addReservation(VisitorPtr visitor, SeancePtr seance,unsigned int row,unsigned int seat);
   bool removeReservation(ReservationPtr &ptr);
    ReservationPtr find(const ReservationPredicate &predicate);
    std::vector<ReservationPtr> findAll(const ReservationPredicate &predicate);
    ReservationPtr getReservation(boost::uuids::uuid &reservationNumber);
    ReservationPtr getReservation(int index);
    int size();
    int getIndex(const ReservationPtr &ptr);
};


#endif //CINEMAPROJECT_RESERVATIONSMANAGER_H
