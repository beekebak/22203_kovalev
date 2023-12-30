#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "parser.h"

using namespace testing;


TEST(InputArgumentsParserTest, CorrectlyDeterminesGameType) {
    GameConfig config;
    std::vector<std::string> args = {"blackjack", "numbers"};
    InputArgumentsParser parser(args);
    parser.Parse(config);

    EXPECT_EQ(config.type, GameType::kPlain);
    EXPECT_EQ(config.deck_size_, 10);
}

TEST(InputArgumentsParserTest, CorrectlyDeterminesStrategies) {
    GameConfig config;
    std::vector<std::string> args = {"blackjack", "17ge", "random_int"};
    config.type = GameType::kCard;

    InputArgumentsParser parser(args);
    auto strategies = parser.Parse(config);

    EXPECT_EQ(strategies.size(), 1);
    EXPECT_EQ(strategies[0], "17ge");
}

TEST(InputArgumentsParserTest, CorrectlyDeterminesLoggerType) {
    GameConfig config;
    std::vector<std::string> args = {"blackjack", "detailed", "fast"};
    InputArgumentsParser parser(args);
    parser.Parse(config);
    EXPECT_EQ(config.logger_type_, "silent");
    std::vector<std::string> args1 = {"blackjack", "detailed"};
    InputArgumentsParser parser1(args1);
    parser1.Parse(config);
    EXPECT_EQ(config.logger_type_, "verbose");
}

TEST(InputArgumentsParserTest, CorrectlyDeterminesDecksCount) {
    GameConfig config;
    std::vector<std::string> args = {"blackjack", "--decks=3"};
    InputArgumentsParser parser(args);
    parser.Parse(config);
    EXPECT_EQ(config.deck_count_, 1);

    std::vector<std::string> args1 = {"blackjack", "decks=3"};
    InputArgumentsParser parser1(args1);
    parser1.Parse(config);
    EXPECT_EQ(config.deck_count_, 3);
}

TEST(InputArgumentsParserTest, CorrectlyDeterminesFilesPath) {
    GameConfig config;
    std::vector<std::string> args = {"blackjack", "--configs=/custom/path"};
    InputArgumentsParser parser(args);
    parser.Parse(config);

    EXPECT_EQ(config.card_table_path_, "/custom/path/card_table.json");
    EXPECT_EQ(config.int_table_path_, "/custom/path/int_table.json");
}
