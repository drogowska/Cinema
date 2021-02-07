#ifndef CINEMAPROJECT_TYPEDEFS_H
#define CINEMAPROJECT_TYPEDEFS_H

#include "memory"
#include <functional>
#include <boost/date_time/posix_time/ptime.hpp>

class Movie;
class Reservation;
class Movie;
class Visitor;
class Hall;
class Seance;
class Arguments;
class Cinema;

typedef std::shared_ptr<Movie> MoviePtr;
typedef std::shared_ptr<Reservation> ReservationPtr;
typedef std::shared_ptr<Visitor> VisitorPtr;
typedef std::shared_ptr<Seance> SeancePtr;
typedef std::shared_ptr<Hall> HallPtr;
typedef std::shared_ptr<Arguments> ArgumentsPtr;
typedef std::shared_ptr<Cinema> CinemaPtr;

typedef std::function<bool(SeancePtr)>SeancePredicate;
typedef std::function<bool(HallPtr)>HallPredicate;
typedef std::function<bool(MoviePtr)>MoviePredicate;
typedef std::function<bool(VisitorPtr)>VisitorPredicate;
typedef std::function<bool(ReservationPtr)>ReservationPredicate;


#endif //CINEMAPROJECT_TYPEDEFS_H
