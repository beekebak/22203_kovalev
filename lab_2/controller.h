#include <functional>
#include <type_traits>
#include "card.h"
#include "strategy.h"
#include "factory.h"
#include "factories_initialization.h"
#include "game.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

template<typename CardType, typename DeckType>
struct Controller{
    Controller(std::vector<std::string> strategy_names): strategy_names_{strategy_names} {}
    void Start(){
        Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory;
        if constexpr (std::is_same_v<CardType, int> && std::is_same_v<DeckType, int>) InitializeIntStrategyFactory(strategy_factory);
        if constexpr (std::is_same_v<CardType, Card> && std::is_same_v<DeckType, Deck>) InitializeCardStrategyFactory(strategy_factory);
        Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>> logger_factory;
        InitializeLoggerFactory<CardType, DeckType>(logger_factory);
        std::vector<players::Player<CardType, DeckType>> players_set;
        GetPlayers(players_set, strategy_factory);
        Game<CardType, DeckType> game(players_set, logger_factory.CreateObject(Config::GetInstance().logger_type_),
                                      Config::GetInstance().logger_type_ == "verbose" ?
                                      MatchType::kManual : MatchType::kAutomatic);
        game.OrganizeTournament();
    }

    void GetPlayers(std::vector<players::Player<CardType, DeckType>>& players_set,
                   Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory){
        for(std::string &str:strategy_names_){
            players_set.emplace_back(players::Player<CardType, DeckType>(strategy_factory.CreateObject(str)));
        }
    }
    std::vector<std::string> strategy_names_;
};

#endif // CONTROLLER_H
