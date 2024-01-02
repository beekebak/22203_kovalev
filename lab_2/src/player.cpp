#include "player.h"

template<typename CardType>
Player<CardType, Deck>::Player(Strategy<CardType, Deck>* strategy) : strategy_(strategy){}

template<typename CardType>
int Player<CardType, Deck>::ShowScore(){
    return state_.max_score;
}

template<typename CardType>
std::string Player<CardType, Deck>::GetStrategyName(){
    return strategy_->GetName();
}

template<typename CardType>
int Player<CardType, Deck>::GetFirstCardScore(){
    return players_deck_[0].GetDenominationValue();
}

template<typename CardType>
int Player<CardType, Deck>::GetLastCardScore(){
    return players_deck_.back().GetDenominationValue();
}

template<typename CardType>
enum State Player<CardType, Deck>::PlayNextMove(CardType opponent_card){
    return strategy_->MakeChoice(state_, opponent_card);
}

template<typename CardType>
void Player<CardType, Deck>::RecieveCard(CardType card){
    players_deck_.push_back(card);
    state_.max_score += card.GetDenominationValue();
    if (card.GetDenominationValue() == 11){
        state_.ace_count++;
    }
}

Player<int, int>::Player(Strategy<int, int>* strategy) : strategy_(strategy){}

int Player<int, int>::ShowScore(){
    return state_;
}

std::string Player<int, int>::GetStrategyName(){
    return strategy_->GetName();
}

int Player<int, int>::GetFirstCardScore(){
    return players_deck_[0];
}

int Player<int, int>::GetLastCardScore(){
    return players_deck_.back();
}

enum State Player<int, int>::PlayNextMove(int opponent_card){
    return strategy_->MakeChoice(state_, opponent_card);
}

void Player<int, int>::RecieveCard(int card){
    players_deck_.push_back(card);
    state_ += card;
}

template class Player<Card, Deck>;
