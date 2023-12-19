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
    virtual void PrintMoveLog(int number, players::Player<CardType,DeckType>& player,
                              State move_result) = 0;
    virtual void PrintMatchStartMessage(players::Player<CardType,DeckType>& first,
                                   players::Player<CardType,DeckType>& second) = 0;
    void PrintMatchResult(int player_number){
        if(player_number == kNoWinner){
            std::cout << "Ничья." << std::endl;
        }
        else{
            std::cout << "Игрок " << player_number << " победил." << std::endl;
        }
    }
    virtual ~Logger() {}
    auto Clone() const {
        return std::unique_ptr<Logger>(CloneImpl());
    }
  protected:
    virtual Logger* CloneImpl() const = 0;
};

template<typename CardType, typename DeckType>
struct VerboseLogger: public Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{}
    void PrintMoveLog(int number, players::Player<CardType, DeckType>& player,
                      State move_result) override{
        if(move_result == State::kTakeMore)
            std::cout << "Игрок " << number << " " << player.ShowScore() << " последняя "
            << player.GetLastCardScore() << std::endl;
        else std::cout << "Игрок " << number << " " << "не брал карт" << std::endl;
    }
    void PrintMatchStartMessage(players::Player<CardType,DeckType>& first,
                                players::Player<CardType,DeckType>& second) override{
        std::cout << "Стратегия первого игрока " << first.GetStrategyName() << std::endl;
        std::cout << "Стратегия второго игрока " << second.GetStrategyName() << std::endl;
    }
    virtual VerboseLogger* CloneImpl() const override{
        return new VerboseLogger(*this);
    }
};

template<typename CardType, typename DeckType>
struct SilentLogger: Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{}
    void PrintMoveLog(int number, players::Player<CardType, DeckType>& player,
                      State move_result) override{}
    void PrintMatchStartMessage(players::Player<CardType,DeckType>& first,
                                players::Player<CardType,DeckType>& second) override{}
    virtual SilentLogger* CloneImpl() const override{
        return new SilentLogger(*this);
    }
};

template<typename CardType, typename DeckType>
struct TournamentLogger: public Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{
        if(winner_number == kNoWinner){
            std::cout << "Ничья в игре." << std::endl;
        }
        else{
            std::cout << "Игрок " << winner_number+1 << " выиграл игру." << std::endl;
        }
        std::cout << table_string_representation << std::endl;
    }
    void PrintMoveLog(int number, players::Player<CardType, DeckType>& player,
                      State move_result) override{}
    void PrintMatchStartMessage(players::Player<CardType,DeckType>& first,
                                players::Player<CardType,DeckType>& second) override{}
    virtual TournamentLogger* CloneImpl() const override{
        return new TournamentLogger(*this);
    }
};

#endif // LOGGER_H
