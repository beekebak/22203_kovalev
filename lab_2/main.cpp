#include <vector>
#include "factory.h"
#include "strategy.h"
#include "card.h"
#include "logger.h"
#include "game.h"
#include "actors.h"

namespace creator_functions {
    Strategy<int, int>* CreateG16PlainStrategy(){
        return new G16Plain();
    }
    Strategy<int, int>* CreateG18PlainStrategy(){
        return new G18Plain();
    }
    Strategy<Card, Deck>* CreateG17CardStrategy(){
        return new G17Card<Card>();
    }
}

void InitializeCardFactory(Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>>& StrategyFactory){
    StrategyFactory.RegisterInstance(">=17", creator_functions::CreateG17CardStrategy);
}

void InitializeIntFactory(Factory<Strategy<int, int>, std::string, std::function<Strategy<int, int>*()>>& StrategyFactory){
    StrategyFactory.RegisterInstance(">=16", creator_functions::CreateG16PlainStrategy);
    StrategyFactory.RegisterInstance(">=18", creator_functions::CreateG18PlainStrategy);
}

int main(int argc, char* argv[]){
    Factory<Strategy<Card, Deck>, std::string, std::function<Strategy<Card, Deck>*()>> StrategyFactory;
    InitializeCardFactory(StrategyFactory);
    std::vector<players::Player<Card, Deck>> players;
    players.push_back(players::Player<Card, Deck>(StrategyFactory.CreateObject(">=17")));
    players.push_back(players::Player<Card, Deck>(StrategyFactory.CreateObject(">=17")));
    Game<Card, Deck> game(players, new VerboseLogger<Card, Deck>);
    game.OrganizeTournament();
    game.ProcessEndgame();
}
