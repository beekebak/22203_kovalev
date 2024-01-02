#include "controller.h"

template<typename CardType, typename DeckType>
Controller<CardType, DeckType>::Controller(std::vector<std::string> strategy_names, GameConfig config):
    strategy_names_{strategy_names}, config_{config} {}

template<typename CardType, typename DeckType>
void InitializeLoggerFactory(Factory<Logger<CardType, DeckType>, std::string,
                                     std::function<Logger<CardType, DeckType>*()>>& logger_factory);

template<typename CardType, typename DeckType>
void Controller<CardType, DeckType>::Start(){
    std::vector<Player<CardType, DeckType>> players_set;
    GetPlayers(players_set);
    Game<CardType, DeckType> game(players_set, Factory<Logger<CardType, DeckType>, std::string,
                                  std::function<Logger<CardType, DeckType>*()>>::GetInstance()->
                                  CreateObject(std::string(config_.logger_type_)),
                                  config_.logger_type_ == "verbose" ?
                                  MatchType::kManual : MatchType::kAutomatic,
                                  config_);
    game.OrganizeTournament();
}

template<typename CardType, typename DeckType>
void Controller<CardType, DeckType>::GetPlayers(std::vector<Player<CardType, DeckType>>& players_set){
    for(std::string &str:strategy_names_){
        players_set.emplace_back(Player<CardType, DeckType>
        (Factory<Strategy<CardType, DeckType>, std::string,
        std::function<Strategy<CardType, DeckType>*()>>::GetInstance()->CreateObject(str)));
    }
}

template class Controller<int,int>;
template class Controller<Card, Deck>;

