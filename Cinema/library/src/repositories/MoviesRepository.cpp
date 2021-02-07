//
// Created by student on 04.06.2020.
//

#include "repositories/MoviesRepository.h"
#include "model/Movie.h"
#include <sstream>

std::string MoviesRepository::report() const{
    std::ostringstream out;
    for(int i=0; i<size(); i++)
    {
        out<<data[i]->getMovieInfo();
    }
    return out.str();
}
