//
// Created by student on 16.06.2020.
//

#ifndef CINEMAPROJECT_CINEMAEXCEPTIONS_H
#define CINEMAPROJECT_CINEMAEXCEPTIONS_H

#include <stdexcept>

class CinemaExceptions : public std::logic_error{
public:
    explicit CinemaExceptions( std::string arg);
};


#endif //CINEMAPROJECT_CINEMAEXCEPTIONS_H
