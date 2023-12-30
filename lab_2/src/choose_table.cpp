#include "choose_table.h"
#include <iostream>

ChooseTable::ChooseTable(std::string path){
    std::ifstream input_file;
    input_file.exceptions(std::ifstream::badbit);
    input_file.open(path);
    table_ = nlohmann::json::parse(input_file);
}

State ChooseTable::MakeChoice(int score, int opponent_card){
    if(score <= 21){
        return chooses_.at(table_[std::to_string(score)][std::to_string(opponent_card)].get<std::string>());
    }
    return State::kLose;
}
