#include "model/Seance.h"
#include "model/Movie.h"
#include "model/Hall.h"
#include <sstream>
#include "exceptions/SeanceExceptions.h"
#include <string>

namespace pt = boost::posix_time;
using namespace std;

Seance::Seance(const boost::posix_time::ptime &dateAndTime, SeanceType seanceType, MoviePtr movie, HallPtr hall)
        : dateAndTime(dateAndTime), seanceType(seanceType), movie(movie), hall(hall) {

    boost :: uuids :: random_generator gen;
    id = gen();
    if(dateAndTime == pt::not_a_date_time) throw SeanceExceptions("The date and the time need to be specified!");
    if(movie == nullptr) throw SeanceExceptions("The movie doesn't exist!");
    if(hall == nullptr)  throw SeanceExceptions("The hall doesn't exist!");

}

Seance::~Seance() {

}

const boost::uuids::uuid &Seance::getId() const {
    return id;
}

const boost::posix_time::ptime &Seance::getDateAndTime() const {
    return dateAndTime;
}
SeanceType Seance::getSeanceType() const {
    return seanceType;
}

MoviePtr Seance::getMovie() const {
    return movie;
}

HallPtr Seance::getHall() const {
    return hall;
}

float Seance::getExtraPayment() const {
    if(seanceType == twoD) return 0;
    else return movie->getBasePrice()*0.12;
}

std::string Seance::getSeanceInfo() const {
    ostringstream sout;
    int margin = 30;
    sout << "_________________________________________________" <<endl;
    sout << "Seance Info:"<<endl;
    sout<<movie->getMovieInfo();
    sout.width(margin); sout << left << "Date and Time: ";
    sout<< getDateAndTime()<<endl;
    sout.width(margin); sout << left << "SeanceType ";
    sout << getSeanceTypeName() <<endl;
    sout<< hall->getHallInfo();

    return sout.str();
}

std::string Seance::getSeanceTypeName() const {
    string tmp[] = {"threeD", "twoD"};
    return tmp[seanceType];
}

void print(const Seance &seance, ostream &out) {
    out << seance.getSeanceInfo() << endl;
}

SeanceType convertSeanceTypeFromString(const std::string &str){
    if(str=="threeD") return threeD;
    return twoD;
}

