#include <vector>
#include <random>
#include "card.h"

#ifndef DEALER_H
#define DEALER_H


template <typename CardType>
class Dealer{
  public:
    Dealer(int deck_size, int deck_count);
    Dealer(Dealer&) = default;
    Dealer(Dealer&&) = default;
    ~Dealer() = default;
    CardType GiveCard();
  private:
    std::vector<int> deck_;
    std::mt19937 rng_;
};

template <>
class Dealer<int>{
  public:
    Dealer(int deck_size, int deck_count);
    Dealer(Dealer&) = default;
    Dealer(Dealer&&) = default;
    ~Dealer() = default;
    int GiveCard();
  private:
    int deck_size_;
    std::mt19937 rng_;
};

#endif // DEALER_H
