#ifndef CINEMAPROJECT_RESERVATIONEXCEPTIONS_H
#define CINEMAPROJECT_RESERVATIONEXCEPTIONS_H

#include <stdexcept>

class ReservationExceptions : public std::logic_error {
public:
    explicit ReservationExceptions( std::string arg);
};


#endif //CINEMAPROJECT_RESERVATIONEXCEPTIONS_H
