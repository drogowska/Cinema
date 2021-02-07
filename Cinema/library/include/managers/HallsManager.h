//
// Created by student on 11.06.2020.
//

#ifndef CINEMAPROJECT_HALLSMANAGER_H
#define CINEMAPROJECT_HALLSMANAGER_H

#include "repositories/HallsRepository.h"
#include <vector>

class HallsManager {
private:
    HallsRepository hallsRepository;
public:
    HallsManager();
    virtual ~HallsManager();

    HallPtr addHall(std::string hallNumber, unsigned int numberOfRows, unsigned int numberOfSeatsInRow);
    bool removeHall(HallPtr &ptr);
    HallPtr find(const HallPredicate &predicate);
    std::vector<HallPtr> findAll(const HallPredicate &predicate);
    HallPtr getHall(std::string hallNumber);
    HallPtr getHall(int index);
    int size();
    int getIndex(const HallPtr &ptr);
};


#endif //CINEMAPROJECT_HALLSMANAGER_H
