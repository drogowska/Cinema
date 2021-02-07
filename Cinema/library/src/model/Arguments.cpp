//
// Created by student on 12.06.2020.
//

#include "model/Arguments.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "model/Cinema.h"

using namespace std;

ArgumentsPtr parse(int argc, char *argv[]) noexcept {
    ArgumentsPtr args = make_shared<Arguments>();
    boost::program_options::options_description description("Options");
    description.add_options()
            ("help,h", "Help screen")
            ("input,i", boost::program_options::value<string>(&args->input), "Input file")
            ("output,o", boost::program_options::value<string>(&args->output), "Output file");
    try{
        boost::program_options::variables_map vm;
        boost::program_options::store(
                boost::program_options::parse_command_line(argc, argv, description),
                vm);
        if(vm.count("help")){
            cout<<description<<endl;
            return nullptr;
        }
        if(vm.empty()) {
            cout<<description<<endl;
            return nullptr;
        }
        boost::program_options::notify(vm);
        return args;
    }
    catch(exception &e){
        cout<<description<<endl;
        return nullptr;
    }
}

CinemaPtr initialize(const ArgumentsPtr &args) noexcept(false) {
    shared_ptr<Cinema> cinema;
    cinema = make_shared<Cinema>();
    if(!args->input.empty()){
        if(!boost::filesystem::exists(args->input)){
            throw runtime_error("Input file does not exists!");
        }
        ifstream fin(args->input);
        if(!fin.is_open()){
            throw runtime_error("Cannot open input file");
        }
        fromStream(fin, cinema);
        fin.close();
    }
    return cinema;
}

void finalize(CinemaPtr cinema, const ArgumentsPtr &args) noexcept(false) {
    if(!args->output.empty()) {
        ofstream fout(args->output);
        if(!fout.is_open()){
            throw runtime_error("Cannot open output file");
        }
        toStream(fout, cinema);
        fout.close();
    }
}
