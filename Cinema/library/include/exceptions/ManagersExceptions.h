//
// Created by student on 12.06.2020.
//

#ifndef CINEMAPROJECT_MANAGERSEXCEPTIONS_H
#define CINEMAPROJECT_MANAGERSEXCEPTIONS_H

#include <stdexcept>

class ManagersExceptions : public std::logic_error {
public:
    explicit ManagersExceptions(std::string arg);
};


#endif //CINEMAPROJECT_MANAGERSEXCEPTIONS_H
