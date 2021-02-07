#ifndef CINEMAPROJECT_MOVIEEXCEPTIONS_H
#define CINEMAPROJECT_MOVIEEXCEPTIONS_H

#include <stdexcept>

class MovieExceptions : public std::logic_error {
public:
    explicit MovieExceptions( std::string arg);
};


#endif //CINEMAPROJECT_MOVIEEXCEPTIONS_H
