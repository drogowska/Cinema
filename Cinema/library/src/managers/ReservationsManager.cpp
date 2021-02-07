//
// Created by student on 11.06.2020.
//

#include "managers/ReservationsManager.h"
#include "model/typedefs.h"
#include "model/Reservation.h"
#include "exceptions/ManagersExceptions.h"
#include <memory>

ReservationPtr ReservationsManager::addReservation(VisitorPtr visitor, SeancePtr seance, unsigned int row, unsigned int seat) {
    if(visitor == nullptr) throw ManagersExceptions("This visitor doesn't exist!");
    if(seance == nullptr) throw ManagersExceptions("This seance doesn't exist!");

    ReservationPredicate p=[seance, row, seat](ReservationPtr ptr)->bool
    {
        return (seance==ptr->getSeance() && row==ptr->getRow() && seat==ptr->getSeat());
    };
    std::vector<ReservationPtr> reservations = findAll(p);
    if(!reservations.empty()) {
        throw ManagersExceptions("This place is already reserved!");
    }

    ReservationPtr ptr = std::make_shared<Reservation>(visitor, seance, row, seat);
    reservationsRepository.add(ptr);
    return ptr;
}

bool ReservationsManager::removeReservation(ReservationPtr &ptr) {
    if(ptr == nullptr) throw ManagersExceptions("Cannot remove this object!");
    reservationsRepository.remove(ptr);
    return true;
}

ReservationPtr ReservationsManager::find(const ReservationPredicate &predicate) {
    for(int i=0; i<reservationsRepository.size(); i++)
    {
        ReservationPtr ptr = reservationsRepository.get(i);
        if(predicate(ptr)) return ptr;
    }
    throw ManagersExceptions("Reservation was not found in the repository!");
}

std::vector<ReservationPtr> ReservationsManager::findAll(const ReservationPredicate &predicate) {
    std::vector<ReservationPtr> result;
    for(int i=0; i<reservationsRepository.size(); i++)
    {
        ReservationPtr ptr = reservationsRepository.get(i);
        if(predicate(ptr)) result.push_back(ptr);
    }
    return result;
}

ReservationPtr ReservationsManager::getReservation(boost::uuids::uuid &reservationNumber) {
    ReservationPredicate p=[reservationNumber](ReservationPtr ptr)->bool
    {
        return (reservationNumber==ptr->getReservationNumber());
    };
    return find(p);
}

ReservationsManager::ReservationsManager() {}

ReservationsManager::~ReservationsManager() {

}

ReservationPtr ReservationsManager::getReservation(int index) {
    if(index <0) throw ManagersExceptions("This index must be positive!");
    return reservationsRepository.get(index);
}

int ReservationsManager::size() {
    return reservationsRepository.size();
}

int ReservationsManager::getIndex(const ReservationPtr &ptr){
    if(ptr == nullptr) throw ManagersExceptions("This object doesn't exist!");
    return reservationsRepository.getIndex(ptr);
}
