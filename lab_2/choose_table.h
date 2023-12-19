#include <map>
#include <string>
#include <fstream>
#include "json/single_include/nlohmann/json.hpp"

#ifndef CHOOSE_TABLE_H
#define CHOOSE_TABLE_H

enum class State{
    kTakeMore,
    kStop,
    kLose
};

class ChooseTable{
  public:
    ChooseTable(std::string path){
        std::ifstream input_file;
        input_file.exceptions(std::ifstream::badbit);
        input_file.open(path);
        table_ = nlohmann::json::parse(input_file);
    }
    State MakeChoice(int score, int opponent_card){
        return chooses_.at(table_[score][opponent_card].get<std::string>());
    }
  private:
    nlohmann::json table_;
    static const std::map<std::string, State> chooses_;
};

const std::map<std::string, State> ChooseTable::chooses_ = {{"H", State::kTakeMore},
            {"S", State::kStop},
            {"L", State::kLose}};

#endif // CHOOSE_TABLE_H
