#include <vector>
#include "player.h"
#include "dealer.h"
#include "card.h"
#include "logger.h"
#include "match.h"
#include "strategy.h"
#include "factory.h"
#include "game_config.h"

#ifndef GAME_H
#define GAME_H

enum class Winner{
    kFirst,
    kSecond
};

template <typename CardType, typename DeckType>
class Game{
  public:
    Game(std::vector<Player<CardType, DeckType>>& players,
           Logger<CardType, DeckType>* logger, MatchType type, GameConfig& config);
    void ProcessEndgame();
    void OrganizeTournament();
  private:
    MatchType game_type_;
    int deck_count_ = 1;
    int deck_size_ = 10;
    std::vector<Player<CardType, DeckType>> players_set_;
    std::unique_ptr<Logger<CardType,DeckType>> logger_;
    GameConfig config_;
    struct ResultTable{
        std::vector<int> table;
        std::string ToString();
    };
    ResultTable result_table_;
    MatchResult StartNewMatch(Player<CardType, DeckType>& first,
                              Player<CardType, DeckType>& second,
                              int first_number, int second_number);
    void InitializeLoadableStrategies();
};

#endif // GAME_H
