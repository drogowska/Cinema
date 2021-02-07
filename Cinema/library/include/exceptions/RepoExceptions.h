//
// Created by student on 06.06.2020.
//

#ifndef CINEMAPROJECT_REPOEXCEPTIONS_H
#define CINEMAPROJECT_REPOEXCEPTIONS_H

#include <stdexcept>

class RepoExceptions : public std::logic_error {
public:
    explicit RepoExceptions( std::string arg);
};


#endif //CINEMAPROJECT_REPOEXCEPTIONS_H
