#include <string>
#include <vector>
#include <map>

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

enum class GameType{
    kPlain,
    kCard
};

struct GameConfig{
    GameType type = GameType::kCard;
    int deck_size_ = 52;
    int deck_count_ = 1;
    std::string card_table_path_ = "./main/plusi/22203_kovalev/lab_2/card_table.json";
    std::string int_table_path_ = "./main/plusi/22203_kovalev/lab_2/int_table.json";
    std::string logger_type_ = "verbose";
    const std::vector<std::string> card_strategies_names_ = {"17ge", "table_card", "random_card",
                                                "coward_card"};
    const std::vector<std::string> int_strategies_names_ = {"16ge", "18ge", "random_int",
                                                      "table_int", "coward_int"};
    const std::map<std::string, std::string> logger_names_ = {{"detailed", "verbose"}, {"fast", "silent"},
                                                        {"tournament", "tournament"}};
    const std::map<std::string, GameType> game_types_ = {{"card", GameType::kCard},
                                                        {"numbers", GameType::kPlain}};
};

#endif // GAME_CONFIG_H
