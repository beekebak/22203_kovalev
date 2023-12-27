#include <map>
#include <string>
#include <fstream>
#include "../json/single_include/nlohmann/json.hpp"

#ifndef CHOOSE_TABLE_H
#define CHOOSE_TABLE_H

enum class State{
    kTakeMore,
    kStop,
    kLose
};

class ChooseTable{
  public:
    ChooseTable(std::string path);
    State MakeChoice(int score, int opponent_card);
  private:
    nlohmann::json table_;
    static const std::map<std::string, State> chooses_;
};

inline const std::map<std::string, State> ChooseTable::chooses_ = {{"H", State::kTakeMore},
            {"S", State::kStop},
            {"L", State::kLose}};

#endif // CHOOSE_TABLE_H
