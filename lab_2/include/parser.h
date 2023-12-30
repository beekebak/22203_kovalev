#include <string>
#include <vector>
#include "logger.h"
#include "strategy.h"
#include "game_config.h"

#ifndef PARSER_H
#define PARSER_H

class InputArgumentsParser{
  public:
    InputArgumentsParser(std::vector<std::string> programm_arguments);
    std::vector<std::string> Parse(GameConfig& config);
  private:
    std::vector<std::string> args_;
    void DetermineGameType(GameConfig& config);
    std::vector<std::string> DetermineStrategies(GameConfig& config);
    void DetermineLoggerType(int players_count, GameConfig& config);
    void DetermineDecksCount(GameConfig& config);
    void DetermineFilesPath(GameConfig& config);
};

#endif // PARSER_H
