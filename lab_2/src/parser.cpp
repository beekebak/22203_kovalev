#include "parser.h"

InputArgumentsParser::InputArgumentsParser(std::vector<std::string> programm_arguments, GameConfig& config) :
    args_{programm_arguments}, config_{config}{}

std::vector<std::string> InputArgumentsParser::Parse(){
    DetermineGameType();
    std::vector<std::string> strats = DetermineStrategies();
    DetermineLoggerType(strats.size());
    DetermineDecksCount();
    DetermineFilesPath();
    return strats;
}

void InputArgumentsParser::DetermineGameType(){
    if(find(args_.begin(), args_.end(), "numbers") != args_.end()){
        config_.type = config_.game_types_.at("numbers");
        config_.deck_size_ = 10;
    }
}

std::vector<std::string> InputArgumentsParser::DetermineStrategies(){
    std::vector<std::string> strats;
    for(const std::string &str:args_){
        if(config_.type == GameType::kPlain &&
            find(config_.int_strategies_names_.begin(),
                 config_.int_strategies_names_.end(), str)!=
                config_.int_strategies_names_.end()){
            strats.push_back(str);
        }
        else if(config_.type == GameType::kCard &&
                 find(config_.card_strategies_names_.begin(),
                      config_.card_strategies_names_.end(), str)!=
                     config_.card_strategies_names_.end()){
            strats.push_back(str);
        }
    }
    return strats;
}

void InputArgumentsParser::DetermineLoggerType(int players_count){
    bool logger_type_is_specified = false;
    for(const std::string &str:args_){
        if(config_.logger_names_.find(str) !=
            config_.logger_names_.end()){
            logger_type_is_specified = true;
            config_.logger_type_ = config_.logger_names_.at(str);
        }
    }
    if(logger_type_is_specified) return;
    if(players_count > 2){
        config_.logger_type_ = "tournament";
    }
}

void InputArgumentsParser::DetermineDecksCount(){
    for(const std::string &str:args_){
        if(str.rfind("decks=", 0) == 0){
            int flag_size = std::string("--configs=").size();
            config_.deck_count_ = std::stoi(str.substr(flag_size, str.size() - flag_size));
        }
    }
}

void InputArgumentsParser::DetermineFilesPath(){
    for(const std::string &str:args_){
        if(str.rfind("--configs=", 0) == 0){
            int flag_size = std::string("--configs=").size();
            config_.card_table_path_ = str.substr(flag_size, str.size() - flag_size) +
                                       "/card_table_" + std::to_string(config_.deck_count_) +
                                       ".json";
            config_.int_table_path_ = str.substr(flag_size, str.size() - flag_size) + "/int_table.json";
        }
    }
}
