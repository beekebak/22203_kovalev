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
    Strategy<CardType, DeckType>* CreateCowardPlainStrategy(){
        return new CowardPlain();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateRandomPlainStrategy(){
        return new RandomPlainStrategy();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateTablePlainStrategy(){
        return new TablePlainStrategy();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateG17CardStrategy(){
        return new G17Card<CardType>();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateTableCardStrategy(){
        return new TableCardStrategy<CardType>();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateCowardCardStrategy(){
        return new CowardCard<CardType>();
    }
    template<typename CardType, typename DeckType>
    Strategy<CardType, DeckType>* CreateRandomCardStrategy(){
        return new RandomCardStrategy<CardType>();
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

void InitializeCardStrategyFactory(Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>>& strategy_factory);
void InitializeIntStrategyFactory(Factory<Strategy<int, int>, std::string, std::function<Strategy<int, int>*()>>& strategy_factory);
template<typename CardType, typename DeckType>
void InitializeLoggerFactory(Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>>& logger_factory);

#endif // FACTORIES_INITIALIZATION_H
