#include <iostream>
#include "player.h"
#include "strategy.h"
#include "card.h"

#ifndef LOGGER_H
#define LOGGER_H

const int kNoWinner = -1;

template<typename CardType, typename DeckType>
struct Logger{
    virtual void PrintGameResult(int winner_number,
                                 std::string table_string_representation) = 0;
    virtual void PrintMoveLog(int number, Player<CardType,DeckType>& player,
                              State move_result) = 0;
    virtual void PrintMatchStartMessage(Player<CardType,DeckType>& first,
                                   Player<CardType,DeckType>& second) = 0;
    void PrintMatchResult(int player_number);
    virtual ~Logger() {}
    std::unique_ptr<Logger> Clone() const;
  protected:
    virtual Logger* CloneImpl() const = 0;
};

template<typename CardType, typename DeckType>
struct VerboseLogger: public Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{}
    void PrintMoveLog(int number, Player<CardType, DeckType>& player,
                      State move_result) override;
    void PrintMatchStartMessage(Player<CardType,DeckType>& first,
                                Player<CardType,DeckType>& second) override;
    VerboseLogger* CloneImpl() const override;
};

template<typename CardType, typename DeckType>
struct SilentLogger: public Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override{}
    void PrintMoveLog(int number, Player<CardType, DeckType>& player,
                      State move_result) override{}
    void PrintMatchStartMessage(Player<CardType,DeckType>& first,
                                Player<CardType,DeckType>& second) override{}
    SilentLogger* CloneImpl() const override;
};

template<typename CardType, typename DeckType>
struct TournamentLogger: public Logger<CardType, DeckType>{
    void PrintGameResult(int winner_number,
                         std::string table_string_representation) override;
    void PrintMoveLog(int number, Player<CardType, DeckType>& player,
                      State move_result) override{}
    void PrintMatchStartMessage(Player<CardType,DeckType>& first,
                                Player<CardType,DeckType>& second) override{}
    TournamentLogger* CloneImpl() const override;
};

#endif // LOGGER_H