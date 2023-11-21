#include <iostream>
#include "actors.h"
#include "strategy.h"
#include "card.h"

#ifndef LOGGER_H
#define LOGGER_H


struct logger{
    void print_result();
};

template<typename T, typename V>
struct verbose_logger: public logger{
    void print_move_log(players::player<T,V>){
        std::cout <<
    }
    void match_start_message(strategy<T,V> first, strategy<T,V> second){

    }
    void match_end_message(std::string msg){

    }
};

template<typename T, typename V>
struct tournament_logger: public verbose_logger<T,V>{

};

struct silent_logger: public logger{};

#endif // LOGGER_H
