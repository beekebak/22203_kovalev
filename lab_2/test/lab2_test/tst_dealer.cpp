#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "dealer.h"

using namespace testing;

TEST(Dealer, CardDealer){
    Dealer<Card> first(52, 1);
    for(int i = 0; i < 51; i++){
        first.GiveCard();
    }
    ASSERT_NO_THROW(first.GiveCard());
    ASSERT_ANY_THROW(first.GiveCard());

    Dealer<Card> second(52, 2);
    for(int i = 0; i < 103; i++){
        second.GiveCard();
    }
    ASSERT_NO_THROW(second.GiveCard());
    ASSERT_ANY_THROW(second.GiveCard());
}

TEST(DEALER, IntDealer){
    Dealer<int> first(10, 1);
    int card = first.GiveCard();
    ASSERT_TRUE(0 < card && card < 11);
}

