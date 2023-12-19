#include <vector>
#include <functional>
#include "card.h"
#include "controller.h"
#include "parser.h"
#include "game_config.h"

int main(int argc, char* argv[]){
    if(argc < 2) return -1;
    InputArgumentsParser parser(std::vector<std::string>(argv+1, argv+argc));
    std::vector<std::string> strategies = parser.Parse();
    if(Config::GetInstance().type == GameType::kCard){
        Controller<Card, Deck> controller(strategies);
        controller.Start();
    }
    else{
        Controller<int, int> controller(strategies);
        controller.Start();
    }
    return 0;
}
