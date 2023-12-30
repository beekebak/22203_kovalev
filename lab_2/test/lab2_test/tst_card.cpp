#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../include/card.h"

using namespace testing;

TEST(Card, Card)
{
    Card card(13);
    EXPECT_EQ("2", card.GetRank());
    EXPECT_EQ("hearts", card.GetSuit());
    EXPECT_EQ(2, card.GetDenominationValue());
    Card ace(12);
    EXPECT_EQ(11, ace.GetDenominationValue());
    Card queen(10);
    EXPECT_EQ(10, queen.GetDenominationValue());
}

