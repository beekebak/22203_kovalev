#include <functional>
#include "strategy.h"
#include "logger.h"
#include "card.h"
#include "factory.h"

#ifndef FACTORIES_INITIALIZATION_H
#define FACTORIES_INITIALIZATION_H

namespace creator_functions {
template<typename CardType, typename DeckType>
Strategy<CardType, DeckType>* CreateG16PlainStrategy(){
    return new G16Plain();
}
template<typename CardType, typename DeckType>
Strategy<CardType, DeckType>* CreateG18PlainStrategy(){
    return new G18Plain();
}
template<typename CardType, typename DeckType>
Strategy<CardType, DeckType>* CreateG17CardStrategy(){
    return new G17Card<Card>();
}
template<typename CardType, typename DeckType>
Logger<CardType, DeckType>* CreateVerboseLogger(){
    return new VerboseLogger<CardType, DeckType>;
}
template<typename CardType, typename DeckType>
Logger<CardType, DeckType>* CreateSilentLogger(){
    return new SilentLogger<CardType, DeckType>;
}
template<typename CardType, typename DeckType>
Logger<CardType, DeckType>* CreateTournamentLogger(){
    return new TournamentLogger<CardType, DeckType>;
}
}

void InitializeCardStrategyFactory(Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>>& strategy_factory){
    strategy_factory.RegisterInstance(">=17", creator_functions::CreateG17CardStrategy<Card, Deck>);
}

void InitializeIntStrategyFactory(Factory<Strategy<int, int>, std::string, std::function<Strategy<int, int>*()>>& strategy_factory){
    strategy_factory.RegisterInstance(">=16", creator_functions::CreateG16PlainStrategy<int, int>);
    strategy_factory.RegisterInstance(">=18", creator_functions::CreateG18PlainStrategy<int, int>);
}

template<typename CardType, typename DeckType>
void InitializeLoggerFactory(Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>>& logger_factory){
    logger_factory.RegisterInstance("verbose", creator_functions::CreateVerboseLogger<CardType,DeckType>);
    logger_factory.RegisterInstance("silent", creator_functions::CreateSilentLogger<CardType,DeckType>);
    logger_factory.RegisterInstance("tournament", creator_functions::CreateTournamentLogger<CardType,DeckType>);
}

#endif // FACTORIES_INITIALIZATION_H
