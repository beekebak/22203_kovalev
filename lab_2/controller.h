#include <functional>
#include "card.h"
#include "strategy.h"
#include "factory.h"
#include "factories_initialization.h"
#include "game.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

template<typename CardType, typename DeckType>
struct Controller{
    void Start(){
        Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory;
        InitializeIntStrategyFactory(strategy_factory);
        Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>> logger_factory;
        InitializeLoggerFactory<CardType, DeckType>(logger_factory);
        std::vector<players::Player<CardType, DeckType>> players__;
        GetPlayers(players__, strategy_factory);
        Game<CardType, DeckType> game(players__, logger_factory.CreateObject("verbose"), MatchType::kManual);
        game.OrganizeTournament();
    }

    void GetPlayers(std::vector<players::Player<CardType, DeckType>>& players__,
                    Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory){
        players__.emplace_back(players::Player<CardType, DeckType>(strategy_factory.CreateObject(">=16")));
        players__.emplace_back(players::Player<CardType, DeckType>(strategy_factory.CreateObject(">=18")));
    }
};

#endif // CONTROLLER_H
