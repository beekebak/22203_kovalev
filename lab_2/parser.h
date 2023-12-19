#include <string>
#include <vector>
#include "logger.h"
#include "strategy.h"
#include "game_config.h"

#ifndef PARSER_H
#define PARSER_H

class InputArgumentsParser{
  public:
    InputArgumentsParser(std::vector<std::string> programm_arguments) : args_{programm_arguments} {}
    std::vector<std::string> Parse(){
        DetermineGameType();
        std::vector<std::string> strats = DetermineStrategies();
        DetermineLoggerType(strats.size());
        DetermineDecksCount();
        DetermineFilesPath();
        return strats;
    }
  private:
    std::vector<std::string> args_;
    void DetermineGameType(){
        if(find(args_.begin(), args_.end(), "numbers") != args_.end()){
            Config::GetInstance().type = Config::GetInstance().game_types_.at("numbers");
            Config::GetInstance().deck_size_ = 10;
        }
    }
    std::vector<std::string> DetermineStrategies(){
        std::vector<std::string> strats;
        for(const std::string &str:args_){
            if(Config::GetInstance().type == GameType::kPlain &&
                find(Config::GetInstance().int_strategies_names_.begin(),
                     Config::GetInstance().int_strategies_names_.end(), str)!=
                    Config::GetInstance().int_strategies_names_.end()){
                strats.push_back(str);
            }
            else if(Config::GetInstance().type == GameType::kCard &&
                     find(Config::GetInstance().card_strategies_names_.begin(),
                          Config::GetInstance().card_strategies_names_.end(), str)!=
                         Config::GetInstance().card_strategies_names_.end()){
                strats.push_back(str);
            }
        }
        return strats;
    }
    void DetermineLoggerType(int players_count){
        bool logger_type_is_specified = false;
        for(const std::string &str:args_){
            if(Config::GetInstance().logger_names_.find(str) !=
                Config::GetInstance().logger_names_.end()){
                logger_type_is_specified = true;
                Config::GetInstance().logger_type_ = Config::GetInstance().logger_names_.at(str);
            }
        }
        if(logger_type_is_specified) return;
        if(players_count > 2){
            Config::GetInstance().logger_type_ = "tournament";
        }
    }
    void DetermineDecksCount(){
        for(const std::string &str:args_){
            if(str.rfind("decks=", 0) == 0){
                int flag_size = std::string("--configs=").size();
                Config::GetInstance().deck_count_ = std::stoi(str.substr(flag_size, str.size() - flag_size));
            }
        }
    }
    void DetermineFilesPath(){
        for(const std::string &str:args_){
            if(str.rfind("--configs=", 0) == 0){
                int flag_size = std::string("--configs=").size();
                Config::GetInstance().card_table_path_ = str.substr(flag_size, str.size() - flag_size) +
                                                         "/card_table_" + std::to_string(Config::GetInstance().deck_count_) +
                                                         ".json";
                Config::GetInstance().int_table_path_ = str.substr(flag_size, str.size() - flag_size) + "/int_table.json";
            }
        }
    }
};

#endif // PARSER_H
