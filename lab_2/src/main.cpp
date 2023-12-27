#include <vector>
#include <functional>
#include "card.h"
#include "controller.h"
#include "parser.h"
#include "game_config.h"

int main(int argc, char* argv[]){
    if(argc < 2) return -1;
    GameConfig config;
    InputArgumentsParser parser(std::vector<std::string>(argv+1, argv+argc), config);
    std::vector<std::string> strategies = parser.Parse();
    if(config.type == GameType::kCard){
        Controller<Card, Deck> controller(strategies, config);
        controller.Start();
    }
    else{
        Controller<int, int> controller(strategies, config);
        controller.Start();
    }
    return 0;
}
