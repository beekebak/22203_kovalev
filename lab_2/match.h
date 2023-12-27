#include "player.h"
#include "dealer.h"
#include "logger.h"

#ifndef MATCH_H
#define MATCH_H

enum class MatchResult{
    kP1Win,
    kP2Win,
    kDraw
};

enum class MatchType{
    kAutomatic,
    kManual
};

template<typename CardType, typename DeckType>
class Match
{
  public:
    Match(Player<CardType, DeckType> f,
          Player<CardType, DeckType> s,
          Dealer<CardType> d,
          std::unique_ptr<Logger<CardType, DeckType>> l,
          MatchType type, int first_number, int second_number);
    MatchResult DetermineWinner(State first_state, State second_state, int first_score, int second_score);
    MatchResult play();
  private:
    class BadStateException{};
    class GameQuitException{};
    MatchType match_type_;
    Player<CardType, DeckType> first_;
    int first_player_number_;
    Player<CardType, DeckType> second_;
    int second_player_number_;
    Dealer<CardType> dealer_;
    std::unique_ptr<Logger<CardType, DeckType>> logger_;
};

#endif // MATCH_H
