#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "strategy.h"

using namespace testing;


TEST(G16PlainTest, LosesWhenSumIsOver21) {
    G16Plain strategy;
    int sum = 22;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(G16PlainTest, StopsWhenSumIsOver15) {
    G16Plain strategy;
    int sum = 16;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(G16PlainTest, TakesMoreWhenSumIs15OrLess) {
    G16Plain strategy;
    int sum = 15;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(G16PlainTest, StopsWhenSumIsExactly21) {
    G16Plain strategy;
    int sum = 21;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(G16PlainTest, CloneMethodCreatesNewInstance) {
    G16Plain originalStrategy;
    G16Plain* cloned = originalStrategy.CloneImpl();
    EXPECT_NE(&originalStrategy, cloned);
    EXPECT_TRUE(typeid(*cloned) == typeid(G16Plain));
    delete cloned;
}

TEST(G18PlainTest, LosesWhenSumIsOver21) {
    G18Plain strategy;
    int sum = 22;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(G18PlainTest, StopsWhenSumIsOver17) {
    G18Plain strategy;
    int sum = 18;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(G18PlainTest, TakesMoreWhenSumIs17OrLess) {
    G18Plain strategy;
    int sum = 17;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(G18PlainTest, StopsWhenSumIsExactly21) {
    G18Plain strategy;
    int sum = 21;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(TablePlainTest, TakesMoreWhenHInTable){
    TablePlainStrategy strategy;
    int sum = 2;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(TablePlainTest, StopsWhenSInTable){
    TablePlainStrategy strategy;
    int sum = 21;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}


TEST(TablePlainTest, LosesWhenMoreThanInTable){
    TablePlainStrategy strategy;
    int sum = 22;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(CowardPlainTest, TakesMoreWhenSumIsLessThan12){
    CowardPlain strategy;
    int sum = 11;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(CowardPlainTest, StopsWhenSumIsMoreThan11){
    CowardPlain strategy;
    int sum = 12;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(RandomPlainTest, LosesWhenSumIsOver21) {
    G16Plain strategy;
    int sum = 22;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(RandomPlainTest, StopsWhenSumIsExactly21) {
    RandomPlainStrategy strategy;
    int sum = 21;
    int opponentCard = 5;
    State result = strategy.MakeChoice(sum, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(RandomPlainTest, CloneMethodCreatesNewInstance) {
    RandomPlainStrategy originalStrategy;
    RandomPlainStrategy* cloned = originalStrategy.CloneImpl();
    EXPECT_NE(&originalStrategy, cloned);
    EXPECT_TRUE(typeid(*cloned) == typeid(RandomPlainStrategy));
    delete cloned;
}

TEST(G17CardTest, LosesWhenSumIsOver21) {
    G17Card<Card> strategy;
    Deck deck;
    deck.max_score = 22;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(G17CardTest, StopsWhenSumIsOver16) {
    G17Card<Card> strategy;
    Deck deck;
    deck.max_score = 17;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(G18CardTest, TakesMoreWhenSumIs16OrLess) {
    G17Card<Card> strategy;
    Deck deck;
    deck.max_score = 16;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(TableCardTest, TakesMoreWhenHInTable){
    TableCardStrategy<Card> strategy;
    Deck deck;
    deck.max_score = 2;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(TableCardTest, StopsWhenSInTable){
    TableCardStrategy<Card> strategy;
    Deck deck;
    deck.max_score = 20;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kStop);
}


TEST(TableCardTest, LosesWhenMoreThanInTable){
    TableCardStrategy<Card> strategy;
    Deck deck;
    deck.max_score = 22;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(CowardCardTest, TakesMoreWhenSumIsLessThan12){
    CowardCard<Card> strategy;
    Deck deck;
    deck.max_score = 10;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kTakeMore);
}

TEST(CowardCardTest, StopsWhenSumIsMoreThan11){
    CowardCard<Card> strategy;
    Deck deck;
    deck.max_score = 12;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(RandomCardTest, LosesWhenSumIsOver21) {
    RandomCardStrategy<Card> strategy;
    Deck deck;
    deck.max_score = 22;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kLose);
}

TEST(RandomCardTest, StopsWhenSumIsExactly21) {
    RandomCardStrategy<Card> strategy;
    Deck deck;
    deck.max_score = 21;
    Card opponentCard(5);
    State result = strategy.MakeChoice(deck, opponentCard);
    ASSERT_EQ(result, State::kStop);
}

TEST(RandomCardTest, CloneMethodCreatesNewInstance) {
    RandomCardStrategy<Card> originalStrategy;
    RandomCardStrategy<Card>* cloned = originalStrategy.CloneImpl();
    EXPECT_NE(&originalStrategy, cloned);
    EXPECT_TRUE(typeid(*cloned) == typeid(RandomCardStrategy<Card>));
    delete cloned;
}
