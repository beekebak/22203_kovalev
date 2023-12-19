#include <vector>
#include <functional>
#include "factory.h"
#include "strategy.h"
#include "card.h"
#include "logger.h"
#include "game.h"
#include "actors.h"
#include "factories_initialization.h"

int main(int argc, char* argv[]){
    Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>> strategy_factory;
    InitializeCardStrategyFactory(strategy_factory);
    Factory<Logger<Card, Deck>, std::string, std::function<Logger<Card, Deck>*()>> logger_factory;
    InitializeLoggerFactory<Card, Deck>(logger_factory);
    std::vector<players::Player<Card, Deck>> players__;
    players__.emplace_back(players::Player<Card, Deck>(strategy_factory.CreateObject(">=17")));
    players__.emplace_back(players::Player<Card, Deck>(strategy_factory.CreateObject(">=17")));
    Game<Card, Deck> game(players__, logger_factory.CreateObject("verbose"), MatchType::kManual);
    game.OrganizeTournament();
}
