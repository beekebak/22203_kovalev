#include <iostream>
#include "actors.h"
#include "strategy.h"
#include "card.h"

#ifndef LOGGER_H
#define LOGGER_H

const int kNoWinner = -1;

template<typename CardType, typename DeckType>
struct Logger{
    virtual void PrintGameResult(int winner_number,
                                 std::string table_string_representation) = 0;
    virtual void PrintMoveLog(players::Player<CardType,DeckType> player,
                              State move_result) = 0;
    virtual void PrintMatchStartMessage(players::Player<CardType,DeckType> first,
                                   players::Player<CardType,DeckType> second) = 0;
    virtual void PrintMatchResult(int player_number) = 0;
};

template<typename CardType, typename DeckType>
struct VerboseLogger: public Logger<CardType, DeckType>{
    void PrintMoveLog(players::Player<CardType, DeckType> player,
                      State move_result) override{
        if(move_result == State::kTakeMore)
            std::cout << player.ShowScore() << " последняя "
            << player.GetLastCardScore() << std::endl;
        else std::cout << "не брал карт" << std::endl;
    }
    void PrintMatchStartMessage(players::Player<CardType,DeckType> first,
                                players::Player<CardType,DeckType> second) override{
        std::cout << "start" << std::endl;
    }
    void PrintMatchResult(int player_number) override{
        if(player_number == kNoWinner){
            std:: cout << "Ничья." << std::endl;
        }
        else{
            std::cout << "Игрок " << player_number << " победил." << std::endl;
        }
    }
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{
        std::cout << "Победил игрок " << winner_number << std::endl;
        std::cout << table_string_representation;
    }
};

template<typename CardType, typename DeckType>
struct TournamentLogger: public Logger<CardType, DeckType>{};

#endif // LOGGER_H
