#include "parser.h"

InputArgumentsParser::InputArgumentsParser(std::vector<std::string> programm_arguments) :
    args_{programm_arguments} {}

std::vector<std::string> InputArgumentsParser::Parse(GameConfig& config){
    DetermineGameType(config);
    std::vector<std::string> strats = DetermineStrategies(config);
    DetermineLoggerType(strats.size(), config);
    DetermineDecksCount(config);
    DetermineFilesPath(config);
    return strats;
}

void InputArgumentsParser::DetermineGameType(GameConfig& config){
    if(find(args_.begin(), args_.end(), "numbers") != args_.end()){
        config.type = config.game_types_.at("numbers");
        config.deck_size_ = 10;
    }
}

std::vector<std::string> InputArgumentsParser::DetermineStrategies(GameConfig& config){
    std::vector<std::string> strats;
    for(const std::string &str:args_){
        if(config.type == GameType::kPlain &&
            find(config.int_strategies_names_.begin(),
                 config.int_strategies_names_.end(), str)!=
                config.int_strategies_names_.end()){
            strats.push_back(str);
        }
        else if(config.type == GameType::kCard &&
                 find(config.card_strategies_names_.begin(),
                      config.card_strategies_names_.end(), str)!=
                     config.card_strategies_names_.end()){
            strats.push_back(str);
        }
    }
    return strats;
}

void InputArgumentsParser::DetermineLoggerType(int players_count, GameConfig& config){
    bool logger_type_is_specified = false;
    for(const std::string &str:args_){
        if(config.logger_names_.find(str) !=
            config.logger_names_.end()){
            logger_type_is_specified = true;
            config.logger_type_ = config.logger_names_.at(str);
        }
    }
    if(logger_type_is_specified) return;
    if(players_count > 2){
        config.logger_type_ = "tournament";
    }
}

void InputArgumentsParser::DetermineDecksCount(GameConfig& config){
    for(const std::string &str:args_){
        if(str.rfind("decks=", 0) == 0){
            int flag_size = std::string("decks=").size();
            config.deck_count_ = std::stoi(str.substr(flag_size, str.size() - flag_size));
        }
    }
}

void InputArgumentsParser::DetermineFilesPath(GameConfig& config){
    for(const std::string &str:args_){
        if(str.rfind("--configs=", 0) == 0){
            int flag_size = std::string("--configs=").size();
            config.card_table_path_ = str.substr(flag_size, str.size() - flag_size) +
                                       "/card_table" + ".json";
            config.int_table_path_ = str.substr(flag_size, str.size() - flag_size) + "/int_table.json";
        }
    }
}
