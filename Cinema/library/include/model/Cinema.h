//
// Created by student on 12.06.2020.
//

#ifndef CINEMAPROJECT_CINEMA_H
#define CINEMAPROJECT_CINEMA_H

#include "managers/HallsManager.h"
#include "managers/MoviesManager.h"
#include "managers/ReservationsManager.h"
#include "managers/SeancesManager.h"
#include "managers/VisitorsManager.h"

class Cinema {
public:
HallsManager hallsManager;
MoviesManager moviesManager;
ReservationsManager reservationsManager;
SeancesManager seancesManager;
VisitorsManager visitorsManager;
public:
    Cinema();

    virtual ~Cinema();
    void fullRemoveMovie(MoviePtr &movie);
    void fullRemoveSeance(SeancePtr &seance);
    void fullRemoveVisitor(VisitorPtr &visitor);
    void fullRemoveHall(HallPtr &hall);

    friend std::istream &fromStream(std::istream &in, CinemaPtr &cinema);
    friend std::ostream &toStream(std::ostream &out, CinemaPtr &cinema);
};

std::vector<std::string> split(const std::string &line);
std::istream &fromStream(std::istream &in, CinemaPtr &cinema);
std::ostream &toStream(std::ostream &out, CinemaPtr &cinema);

#endif //CINEMAPROJECT_CINEMA_H
