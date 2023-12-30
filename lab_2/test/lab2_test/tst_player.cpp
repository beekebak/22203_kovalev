#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "player.h"

using namespace testing;

class MockStrategy : public Strategy<Card, Deck>{
public:
    MockStrategy() : Strategy<Card, Deck>("MockStrategy"){}

    State MakeChoice(Deck& sum, Card& opponent_card) override{
        return State::kTakeMore;
    }

    MockStrategy* CloneImpl() const override{
        return new MockStrategy(*this);
    }
};

class MockStrategyInt : public Strategy<int, int>{
public:
    MockStrategyInt() : Strategy<int, int>("MockStrategy"){}

    State MakeChoice(int& sum, int& opponent_card) override{
        return State::kTakeMore;
    }

    MockStrategyInt* CloneImpl() const override{
        return new MockStrategyInt(*this);
    }
};

TEST(PlayerTest, ConstructWithStrategy) {
    MockStrategy* strategy = new MockStrategy();
    Player<Card, Deck> player(strategy);
    EXPECT_EQ(player.GetStrategyName(), "MockStrategy");
}

TEST(PlayerTest, CopyConstructor) {
    MockStrategy* strategy = new MockStrategy();
    Player<Card, Deck> original_player(strategy);
    Player<Card, Deck> copied_player(original_player);

    EXPECT_EQ(copied_player.GetStrategyName(), "MockStrategy");
}

TEST(PlayerTest, ShowScore) {
    Player<Card, Deck> player(new MockStrategy());
    EXPECT_EQ(player.ShowScore(), 0); // Initial score is 0.
}

TEST(PlayerTest, GetFirstAndLastCardScore) {
    Player<Card, Deck> player(new MockStrategy());

    Card card1(10);
    Card card2(2);
    player.RecieveCard(card1);
    player.RecieveCard(card2);

    EXPECT_EQ(player.GetFirstCardScore(), 10);
    EXPECT_EQ(player.GetLastCardScore(), 4);
}

TEST(PlayerTest, PlayNextMove) {
    Player<Card, Deck> player(new MockStrategy());
    Card opponent_card(9);

    State state = player.PlayNextMove(opponent_card);

    EXPECT_EQ(state, State::kTakeMore);
}

TEST(PlayerTest, RecieveCard) {
    Player<Card, Deck> player(new MockStrategy());
    Card card(12);

    player.RecieveCard(card);

    EXPECT_EQ(player.ShowScore(), 11);
}

TEST(PlayerTest, ShowScoreInitiallyZero) {
    Player<int, int> player;

    EXPECT_EQ(player.ShowScore(), 0);
}

TEST(PlayerTest, ShowScoreAfterReceivingCards) {
    Player<int, int> player;
    player.RecieveCard(10);
    player.RecieveCard(5);

    EXPECT_EQ(player.ShowScore(), 15);
}

TEST(PlayerTest, GetFirstAndLastCardScoreInt) {
    Player<int, int> player;
    player.RecieveCard(7);
    player.RecieveCard(3);
    player.RecieveCard(9);

    EXPECT_EQ(player.GetFirstCardScore(), 7);
    EXPECT_EQ(player.GetLastCardScore(), 9);
}

TEST(PlayerTest, PlayNextMoveInt) {
    MockStrategyInt* mock_strategy = new MockStrategyInt();
    Player<int, int> player(mock_strategy);
    player.RecieveCard(2);

    State state = player.PlayNextMove(5);

    EXPECT_EQ(state, State::kTakeMore);
}

TEST(PlayerTest, ReceiveCardUpdatesStateInt) {
    Player<int, int> player;

    player.RecieveCard(4);
    EXPECT_EQ(player.ShowScore(), 4);

    player.RecieveCard(6);
    EXPECT_EQ(player.ShowScore(), 10);
}
