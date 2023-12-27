#include "factories_initialization.h"

void InitializeCardStrategyFactory(Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>>& strategy_factory){
    strategy_factory.RegisterInstance("17ge", creator_functions::CreateG17CardStrategy<Card, Deck>);
    strategy_factory.RegisterInstance("table_card", creator_functions::CreateTableCardStrategy<Card, Deck>);
    strategy_factory.RegisterInstance("random_card", creator_functions::CreateRandomCardStrategy<Card, Deck>);
    strategy_factory.RegisterInstance("coward_card", creator_functions::CreateCowardCardStrategy<Card, Deck>);
}

void InitializeIntStrategyFactory(Factory<Strategy<int, int>, std::string, std::function<Strategy<int, int>*()>>& strategy_factory){
    strategy_factory.RegisterInstance("16ge", creator_functions::CreateG16PlainStrategy<int, int>);
    strategy_factory.RegisterInstance("18ge", creator_functions::CreateG18PlainStrategy<int, int>);
    strategy_factory.RegisterInstance("random_int", creator_functions::CreateRandomPlainStrategy<int, int>);
    strategy_factory.RegisterInstance("table_int", creator_functions::CreateTablePlainStrategy<int,int>);
    strategy_factory.RegisterInstance("coward_int", creator_functions::CreateCowardPlainStrategy<int,int>);
}

template<typename CardType, typename DeckType>
void InitializeLoggerFactory(Factory<Logger<CardType, DeckType>, std::string, std::function<Logger<CardType, DeckType>*()>>& logger_factory){
    logger_factory.RegisterInstance("verbose", creator_functions::CreateVerboseLogger<CardType,DeckType>);
    logger_factory.RegisterInstance("silent", creator_functions::CreateSilentLogger<CardType,DeckType>);
    logger_factory.RegisterInstance("tournament", creator_functions::CreateTournamentLogger<CardType,DeckType>);
}

template void InitializeLoggerFactory(Factory<Logger<Card, Deck>, std::string, std::function<Logger<Card, Deck>*()>>& logger_factory);
template void InitializeLoggerFactory(Factory<Logger<int, int>, std::string, std::function<Logger<int, int>*()>>& logger_factory);
