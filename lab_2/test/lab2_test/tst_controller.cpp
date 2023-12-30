#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "controller.h"

using namespace testing;

TEST(ControllerTest, ConstructedProperly) {
    std::vector<std::string> strategies = {"Strategy1", "Strategy2"};
    GameConfig config;
    Controller<int, int> controller(strategies, config);

    EXPECT_EQ(controller.strategy_names_, strategies);
}

TEST(ControllerTest, StartInitializesGameProperly) {
    std::vector<std::string> strategies = {"table_int", "coward_int"};
    GameConfig config;
    config.deck_size_ = 10;
    Controller<int, int> controller(strategies, config);
    EXPECT_NO_THROW(controller.Start());
    std::vector<std::string> strategies5 = {"abwasg", "sdadsa"};
    Controller<int, int> controller5(strategies5, config);
    EXPECT_ANY_THROW(controller5.Start());
}
