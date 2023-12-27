#include "choose_table.h"

ChooseTable::ChooseTable(std::string path){
    std::ifstream input_file;
    input_file.exceptions(std::ifstream::badbit);
    input_file.open(path);
    table_ = nlohmann::json::parse(input_file);
}

State ChooseTable::MakeChoice(int score, int opponent_card){
    return chooses_.at(table_[score][opponent_card].get<std::string>());
}
