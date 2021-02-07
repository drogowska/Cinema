#include "exceptions/ReservationExceptions.h"

ReservationExceptions::ReservationExceptions(std::string arg) : std::logic_error(arg) {

}
