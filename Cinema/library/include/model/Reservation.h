#ifndef CINEMAPROJECT_RESERVATION_H
#define CINEMAPROJECT_RESERVATION_H
#include <boost/uuid/uuid_generators.hpp> //generator
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include "model/typedefs.h"


class Reservation {
private:
    unsigned int row;
    unsigned int seat;
    boost::uuids::uuid reservationNumber;
    SeancePtr seance;
    VisitorPtr visitor;

public:
    Reservation(VisitorPtr visitor, SeancePtr seance,unsigned int row,unsigned int seat);
    virtual ~Reservation();

    unsigned int getRow() const;
    unsigned int getSeat() const;
    const boost::uuids::uuid &getReservationNumber() const;
    SeancePtr getSeance() const;
    VisitorPtr getVisitor() const;
    std::string getReservationInfo() const;
    float getActualPrice() const;
};
void print(const Reservation &reservation, std::ostream &out);

#endif //CINEMAPROJECT_RESERVATION_H
