//
// Created by student on 11.06.2020.
//

#include "managers/HallsManager.h"
#include "model/typedefs.h"
#include "model/Hall.h"
#include "exceptions/ManagersExceptions.h"
#include <memory>
#include <algorithm>

HallPtr HallsManager::addHall(std::string hallNumber, unsigned int numberOfRows, unsigned int numberOfSeatsInRow) {
    if(hallNumber.empty()) throw ManagersExceptions("The hall number cannot be empty");
    HallPtr ptr = std::make_shared<Hall>(hallNumber, numberOfRows, numberOfSeatsInRow);
    hallsRepository.add(ptr);
    return ptr;
}

bool HallsManager::removeHall(HallPtr &ptr) {
    if(ptr == nullptr) throw ManagersExceptions("Cannot remove this object!");
    hallsRepository.remove(ptr);
    return true;
}

HallPtr HallsManager::find(const HallPredicate &predicate) {
    for(int i=0; i<hallsRepository.size(); i++)
    {
        HallPtr ptr = hallsRepository.get(i);
        if(predicate(ptr)) return ptr;
    }
    throw ManagersExceptions("Hall was not found in the repository!");
}

std::vector<HallPtr> HallsManager::findAll(const HallPredicate &predicate) {
    std::vector<HallPtr> result;
    for(int i=0; i<hallsRepository.size(); i++)
    {
        HallPtr ptr = hallsRepository.get(i);
        if(predicate(ptr)) result.push_back(ptr);
    }
    return result;
}

HallPtr HallsManager::getHall(std::string hallNumber) {
    if(hallNumber.empty()) throw ManagersExceptions("The hall number cannot be empty.");
    HallPredicate p=[hallNumber](HallPtr ptr)->bool
    {
        return (hallNumber==ptr->getHallNumber());
    };
    return find(p);

}

HallsManager::HallsManager() {}

HallsManager::~HallsManager() {}

int HallsManager::size() {
    return hallsRepository.size();
}

HallPtr HallsManager::getHall(int index) {
    if(index <0) throw ManagersExceptions("This index must be positive!");
    return hallsRepository.get(index);
}

int HallsManager::getIndex(const HallPtr &ptr){
    if(ptr == nullptr) throw ManagersExceptions("This object doesn't exist!");
    return hallsRepository.getIndex(ptr);
}
