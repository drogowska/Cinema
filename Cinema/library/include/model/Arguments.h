//
// Created by student on 12.06.2020.
//

#ifndef CINEMAPROJECT_ARGUMENTS_H
#define CINEMAPROJECT_ARGUMENTS_H
#include <string>
#include <memory>
#include "model/typedefs.h"

struct Arguments
{
    std::string input;
    std::string output;
};

typedef std::shared_ptr<Arguments> ArgumentsPtr;

ArgumentsPtr parse(int argc, char *argv[]) noexcept;
CinemaPtr initialize(const ArgumentsPtr &args) noexcept(false);
void finalize(CinemaPtr cinema, const ArgumentsPtr &args) noexcept(false);

#endif //CINEMAPROJECT_ARGUMENTS_H
