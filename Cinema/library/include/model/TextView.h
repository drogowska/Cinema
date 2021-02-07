//
// Created by student on 16.06.2020.
//

#ifndef CINEMAPROJECT_TEXTVIEW_H
#define CINEMAPROJECT_TEXTVIEW_H

#include "model/typedefs.h"


class TextView {
    CinemaPtr cinema;
    VisitorPtr user;

public:
    TextView(const CinemaPtr &cinema);

    virtual ~TextView();

    void clearScreen();

    void clearScreenWithoutLogo();

    int choose(int howManyOptions);

    std::string convertDateAndTime(boost::posix_time::ptime dateAndTime);

    void mainPage();

    void signIn();

    void signUp();

    void showMovies();

    void showSeances(const MoviePtr &movie);

    void makeReservation(const SeancePtr &seance);

    void accountSettings();

    void showReservations();

    void manageVisitors();

    void manageMovies();

    void manageSeances();

    void manageHalls();
};


#endif //CINEMAPROJECT_TEXTVIEW_H
