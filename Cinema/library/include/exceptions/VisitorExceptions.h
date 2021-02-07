#ifndef CINEMA_PROJECT_VISITOREXCEPTIONS_H
#define CINEMA_PROJECT_VISITOREXCEPTIONS_H
#include <iostream>
#include <stdexcept>

class VisitorExceptions : public std::logic_error {
public:
    explicit VisitorExceptions( std::string arg);

};


#endif //CINEMA_PROJECT_VISITOREXCEPTIONS_H
