//
// Created by student on 09.06.2020.
//

#include "managers/SeancesManager.h"
#include "model/typedefs.h"
#include "exceptions/ManagersExceptions.h"
#include <memory>
#include <boost/date_time/special_defs.hpp>
namespace pt = boost::posix_time;

SeancePtr SeancesManager::addSeance(const boost::posix_time::ptime &dateAndTime, SeanceType seanceType, MoviePtr movie, HallPtr hall) {
    if(movie == nullptr) throw ManagersExceptions("This movie doesn't exist!");
    if(hall == nullptr) throw ManagersExceptions("This hall doesn't exist!");
    if(dateAndTime == pt::not_a_date_time) throw ManagersExceptions("The date and the time need to be specified!");
    SeancePtr ptr = std::make_shared<Seance>(dateAndTime, seanceType, movie, hall);
    seancesRepository.add(ptr);
    return ptr;
}

bool SeancesManager::removeSeance(SeancePtr &ptr) {
    if(ptr == nullptr) throw ManagersExceptions("Cannot remove this object!");
    seancesRepository.remove(ptr);
    return true;
}

SeancePtr SeancesManager::find(const SeancePredicate &predicate) {
    for(int i=0; i<seancesRepository.size(); i++)
    {
        SeancePtr ptr = seancesRepository.get(i);
        if(predicate(ptr)) return ptr;
    }
    throw ManagersExceptions("Seance was not found in the repository!");
}

std::vector<SeancePtr> SeancesManager::findAll(const SeancePredicate &predicate) {
    std::vector<SeancePtr> result;
    for(int i=0; i<seancesRepository.size(); i++)
    {
        SeancePtr ptr = seancesRepository.get(i);
        if(predicate(ptr)) result.push_back(ptr);
    }
    return result;
}

SeancePtr SeancesManager::getSeance(boost::uuids::uuid &id) {
    SeancePredicate p=[id](SeancePtr ptr)->bool
    {
        return (id==ptr->getId());
    };
    return find(p);
}

SeancesManager::SeancesManager() {}

SeancesManager::~SeancesManager() {

}

SeancePtr SeancesManager::getSeance(int index) {
    if(index <0) throw ManagersExceptions("This index must be positive!");
    return seancesRepository.get(index);
}

int SeancesManager::size() {
    return seancesRepository.size();
}

int SeancesManager::getIndex(const SeancePtr &ptr){
    if(ptr == nullptr) throw ManagersExceptions("This object doesn't exist!");
    return seancesRepository.getIndex(ptr);
}

