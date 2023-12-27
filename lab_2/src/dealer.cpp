#include "dealer.h"
#include <stdexcept>

template <typename CardType>
Dealer<CardType>::Dealer(int deck_size, int deck_count):deck_(std::vector<int>(deck_size, deck_count)){
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}

template <typename CardType>
CardType Dealer<CardType>::GiveCard(){
    int idx = rng_() % deck_.size();
    for(int i = 0; deck_[idx] == 0 && i < deck_.size(); i++){
        idx = (idx + 1) % deck_.size();
    }
    if(deck_[idx] == 0) throw std::range_error("no more cards");
    deck_[idx]--;
    return CardType(idx);
}

Dealer<int>::Dealer(int deck_size, int deck_count) : deck_size_{deck_size}{
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}

int Dealer<int>::GiveCard(){
    return rng_() % deck_size_ + 1;
}

template class Dealer<Card>;

