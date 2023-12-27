#include "controller.h"
#include "factories_initialization.h"

template<typename CardType, typename DeckType>
Controller<CardType, DeckType>::Controller(std::vector<std::string> strategy_names, GameConfig config):
    strategy_names_{strategy_names}, config_{config} {}

template<typename CardType, typename DeckType>
void InitializeLoggerFactory(Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>>& logger_factory);

template<typename CardType, typename DeckType>
void Controller<CardType, DeckType>::Start(){
    Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory;
    if constexpr (std::is_same_v<CardType, int> && std::is_same_v<DeckType, int>) InitializeIntStrategyFactory(strategy_factory);
    if constexpr (std::is_same_v<CardType, Card> && std::is_same_v<DeckType, Deck>) InitializeCardStrategyFactory(strategy_factory);
    Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>> logger_factory;
    InitializeLoggerFactory<CardType, DeckType>(logger_factory);
    std::vector<Player<CardType, DeckType>> players_set;
    GetPlayers(players_set, strategy_factory);
    Game<CardType, DeckType> game(players_set, logger_factory.CreateObject(config_.logger_type_),
                                  config_.logger_type_ == "verbose" ?
                                      MatchType::kManual : MatchType::kAutomatic,
                                  config_);
    game.OrganizeTournament();
}

template<typename CardType, typename DeckType>
void Controller<CardType, DeckType>::GetPlayers(std::vector<Player<CardType, DeckType>>& players_set,
                Factory<Strategy<CardType, DeckType>, std::string, std::function<Strategy<CardType, DeckType>*()>> strategy_factory){
    for(std::string &str:strategy_names_){
        players_set.emplace_back(Player<CardType, DeckType>(strategy_factory.CreateObject(str)));
    }
}

template class Controller<int,int>;
template class Controller<Card, Deck>;

