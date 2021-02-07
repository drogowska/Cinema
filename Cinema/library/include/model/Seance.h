#ifndef CINEMAPROJECT_SEANCE_H
#define CINEMAPROJECT_SEANCE_H
#include <boost/uuid/uuid_generators.hpp> //generator
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include<string>
#include "model/typedefs.h"

enum SeanceType{
    threeD = 0,
    twoD = 1,
    //3D, 2D,
};

SeanceType convertSeanceTypeFromString(const std::string &str);

class Seance {
private:
    boost::uuids::uuid id;
    boost::posix_time::ptime dateAndTime;
    SeanceType seanceType;
    MoviePtr movie;
    HallPtr hall;
public:

    Seance(const boost::posix_time::ptime &dateAndTime, SeanceType seanceType, MoviePtr movie, HallPtr hall);
    virtual ~Seance();

    const boost::uuids::uuid &getId() const;
    const boost::posix_time::ptime &getDateAndTime() const;
    SeanceType getSeanceType() const;
    MoviePtr getMovie() const;
    HallPtr getHall() const;

    float getExtraPayment() const;
    std::string getSeanceInfo() const;
    std::string getSeanceTypeName() const;
};

void print(const Seance &seance, std::ostream &out);
SeanceType convertSeanceTypeFromString(const std::string &str);
#endif //CINEMAPROJECT_SEANCE_H
