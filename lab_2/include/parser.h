#include <string>
#include <vector>
#include "logger.h"
#include "strategy.h"
#include "game_config.h"

#ifndef PARSER_H
#define PARSER_H

class InputArgumentsParser{
  public:
    InputArgumentsParser(std::vector<std::string> programm_arguments, GameConfig& config);
    std::vector<std::string> Parse();
  private:
    std::vector<std::string> args_;
    GameConfig config_;
    void DetermineGameType();
    std::vector<std::string> DetermineStrategies();
    void DetermineLoggerType(int players_count);
    void DetermineDecksCount();
    void DetermineFilesPath();
};

#endif // PARSER_H
