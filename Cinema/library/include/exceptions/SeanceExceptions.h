//
// Created by student on 10.06.2020.
//

#ifndef CINEMAPROJECT_SEANCEEXCEPTIONS_H
#define CINEMAPROJECT_SEANCEEXCEPTIONS_H


#include <stdexcept>

class SeanceExceptions : public std::logic_error {
public:
    explicit SeanceExceptions( std::string arg);

};

#endif //CINEMAPROJECT_SEANCEEXCEPTIONS_H
