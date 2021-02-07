#include "model/Reservation.h"
#include "model/Seance.h"
#include "model/Movie.h"
#include "model/Hall.h"
#include "model/Visitor.h"
#include "exceptions/ReservationExceptions.h"
#include <sstream>
using namespace std;
Reservation::Reservation(VisitorPtr visitor, SeancePtr seance,unsigned int row,unsigned int seat) : visitor(visitor),seance(seance),
                                                            row(row), seat(seat){
    boost :: uuids :: random_generator gen;
    reservationNumber = gen();
    if(visitor == nullptr) throw ReservationExceptions("Cannot create reservation without a visitor!");
    if(seance == nullptr) throw ReservationExceptions("Cannot create reservation without a seance!");
    if(row <= 0 || row > seance->getHall()->getNumberOfRows()) throw ReservationExceptions("Wrong row!");
    if(seat <= 0 || seat > seance->getHall()->getNumberOfSeatInRow()) throw ReservationExceptions("Wrong seat!");
}

Reservation::~Reservation() {}

unsigned int Reservation::getRow() const {
    return row;
}

unsigned int Reservation::getSeat() const {
    return seat;
}

const boost::uuids::uuid &Reservation::getReservationNumber() const {
    return reservationNumber;
}

SeancePtr Reservation::getSeance() const {
    return seance;
}

VisitorPtr Reservation::getVisitor() const {
    return visitor;
}

float Reservation::getActualPrice() const {
    float price = seance->getMovie()->getBasePrice()+seance->getExtraPayment();
    return price+(price*visitor->getDiscountType()/100);
}

std::string Reservation::getReservationInfo() const {
    ostringstream sout;
    int margin = 30;
    sout << "_________________________________________________" <<endl;
    sout << "Reservation Info:"<<endl;
    sout.width(margin); sout << left << "Reservation number: ";
    sout<< to_string(getReservationNumber())<<endl;
    sout<< getVisitor()->getVisitorInfo();
    sout<< getSeance()->getSeanceInfo();
    sout.width(margin); sout << left << "Seat: ";
    sout << getSeat() <<endl;
    sout.width(margin); sout << left << "Row: ";
    sout<< getRow()<<endl;
    return sout.str();
}
void print(const Reservation &reservation, ostream &out) {
    out << reservation.getReservationInfo() << endl;
}