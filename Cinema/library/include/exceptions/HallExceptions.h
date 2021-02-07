//
// Created by student on 10.06.2020.
//

#ifndef CINEMAPROJECT_HALLEXCEPTIONS_H
#define CINEMAPROJECT_HALLEXCEPTIONS_H

#include <stdexcept>

class HallExceptions : public std::logic_error {
public:
    explicit HallExceptions( std::string arg);

};


#endif //CINEMAPROJECT_HALLEXCEPTIONS_H
