#include <string>

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

class Config{
  private:
    Config() = default;
    ~Config() = default;
  public:
    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(Config const&) = delete;
    Config& operator=(Config&&) = delete;
    static Config& GetInstance(){
        static Config instance;
        return instance;
    }

    int deck_size_ = 10;
    int deck_count_ = 1;
    std::string card_table_path_ = "./main/plusi/22203_kovalev/lab_2/card_table_1.json";
    std::string int_table_path_ = "./main/plusi/22203_kovalev/lab_2/int_table.json";
};

#endif // GAME_CONFIG_H
