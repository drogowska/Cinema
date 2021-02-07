#include "repositories/ReservationsRepository.h"
#include <sstream>
#include "model/Reservation.h"

using namespace std;


string ReservationsRepository::report() const {
    std::ostringstream out;
    for(int i=0; i<size(); i++)
    {
        out<<data[i]->getReservationInfo();
    }
    return out.str();
}



