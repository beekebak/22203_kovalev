#include <functional>
#include <type_traits>
#include "card.h"
#include "strategy.h"
#include "factory.h"
#include "game.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

template<typename CardType, typename DeckType>
struct Controller{
    Controller(std::vector<std::string> strategy_names, GameConfig config);
    void Start();
    void GetPlayers(std::vector<Player<CardType, DeckType>>& players_set);
    std::vector<std::string> strategy_names_;
    GameConfig config_;
};

#endif // CONTROLLER_H
