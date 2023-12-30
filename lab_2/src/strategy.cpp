#include "strategy.h"

template<typename CardType, typename DeckType>
std::string Strategy<CardType, DeckType>::GetName(){
    return name_;
}

template<typename CardType, typename DeckType>
std::unique_ptr<Strategy<CardType, DeckType>> Strategy<CardType, DeckType>::Clone() const{
    return std::unique_ptr<Strategy<CardType, DeckType>>(CloneImpl());
}

template<typename CardType, typename DeckType>
void Strategy<CardType, DeckType>::ChangeMaxScore(int& old_max_score, int new_max_score){
    if(new_max_score <= 21 && old_max_score < new_max_score){
        old_max_score = new_max_score;
    }
}

template<typename CardType, typename DeckType>
void Strategy<CardType, DeckType>::ChangeState(State& old_state, State new_state){
    switch(old_state){
    case State::kLose:
        old_state = new_state;
        break;
    case State::kTakeMore:
        old_state = new_state == State::kStop ? new_state : old_state;
        break;
    case State::kStop: break;
    }
}

G16Plain::G16Plain():Strategy<int, int>(">=16"){}

State G16Plain::MakeChoice(int& sum, int& opponents_card){
    State answer = State::kLose;
    if(sum > 21){
        Strategy<int, int>::ChangeState(answer, State::kLose);
    }
    else if(sum > 15){
        Strategy<int, int>::ChangeState(answer, State::kStop);
    }
    else{
        Strategy<int, int>::ChangeState(answer, State::kTakeMore);
    }
    return answer;
}

G16Plain* G16Plain::CloneImpl() const{
    return new G16Plain(*this);
}

G18Plain::G18Plain():Strategy<int, int>(">=18"){}

State G18Plain::MakeChoice(int& sum, int& opponents_card){
    State answer = State::kLose;
    if(sum > 21){
        Strategy<int, int>::ChangeState(answer, State::kLose);
    }
    else if(sum > 17){
        Strategy<int, int>::ChangeState(answer, State::kStop);
    }
    else{
        Strategy<int, int>::ChangeState(answer, State::kTakeMore);
    }
    return answer;
}

G18Plain* G18Plain::CloneImpl() const{
    return new G18Plain(*this);
}

TablePlainStrategy::TablePlainStrategy(): Strategy<int,int>("TableInt"){}

State TablePlainStrategy::MakeChoice(int& sum, int& opponents_card){
    return table_.MakeChoice(sum, opponents_card);
}

TablePlainStrategy* TablePlainStrategy::CloneImpl() const{
    return new TablePlainStrategy(*this);
}

void TablePlainStrategy::SetTablePath(std::string path){
    table_ = ChooseTable(path);
}

CowardPlain::CowardPlain(): Strategy<int, int>("CowardPlain"){};

State CowardPlain::MakeChoice(int& sum, int& opponents_card){
    State answer = State::kLose;
    if(sum >= 22){
        Strategy<int, int>::ChangeState(answer, State::kLose);
    }
    else if(sum >= 12){
        Strategy<int, int>::ChangeState(answer, State::kStop);
    }
    else{
        Strategy<int, int>::ChangeState(answer, State::kTakeMore);
    }
    return answer;
}

CowardPlain* CowardPlain::CloneImpl() const{
    return new CowardPlain(*this);
}

RandomPlainStrategy::RandomPlainStrategy(): Strategy<int, int>("RandomInt"){
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}

RandomPlainStrategy::RandomPlainStrategy(const RandomPlainStrategy& other) : rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}
State RandomPlainStrategy::MakeChoice(int& sum, int& opponents_card){
    int temp = rng_()%100;
    if(temp < 25){
        actual_strategy_ = std::unique_ptr<Strategy<int, int>>(new G16Plain);
    }
    else if(25 <= temp && temp < 50){
        actual_strategy_ = std::unique_ptr<Strategy<int, int>>(new TablePlainStrategy);
    }
    else if(50 <= temp && temp < 75){
        actual_strategy_ = std::unique_ptr<Strategy<int, int>>(new G18Plain);
    }
    else{
        actual_strategy_ = std::unique_ptr<Strategy<int, int>>(new CowardPlain);
    }
    return actual_strategy_->MakeChoice(sum, opponents_card);
}
RandomPlainStrategy* RandomPlainStrategy::CloneImpl() const {
    return new RandomPlainStrategy(*this);
}

template<typename CardType>
G17Card<CardType>::G17Card(): Strategy<CardType, Deck>(">=17"){};

template<typename CardType>
State G17Card<CardType>::MakeChoice(Deck& deck_state, CardType& opponents_card){
    State answer = State::kLose;
    for(int i = 0; i <= deck_state.ace_count; i++){
        Strategy<CardType, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
        if(deck_state.max_score - i*10 > 21){
            Strategy<CardType, Deck>::ChangeState(answer, State::kLose);
        }
        else if(deck_state.max_score - i*10 > 16){
            Strategy<CardType, Deck>::ChangeState(answer, State::kStop);
        }
        else{
            Strategy<CardType, Deck>::ChangeState(answer, State::kTakeMore);
        }
    }
    for(int i = 1; i <= deck_state.ace_count && deck_state.max_score > 21; i++){
        deck_state.max_score -= 10;
        deck_state.ace_count--;
    }
    return answer;
}

template<typename CardType>
G17Card<CardType>* G17Card<CardType>::CloneImpl() const{
    return new G17Card(*this);
}

template<typename CardType>
CowardCard<CardType>::CowardCard(): Strategy<CardType, Deck>("CowardCard"){};

template<typename CardType>
State CowardCard<CardType>::MakeChoice(Deck& deck_state, CardType& opponents_card){
    State answer = State::kLose;
    for(int i = 0; i <= deck_state.ace_count; i++){
        Strategy<CardType, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
        if(deck_state.max_score - i*10 >= 22){
            Strategy<CardType, Deck>::ChangeState(answer, State::kLose);
        }
        else if(deck_state.max_score - i*10 >= 12){
            Strategy<CardType, Deck>::ChangeState(answer, State::kStop);
        }
        else{
            Strategy<CardType, Deck>::ChangeState(answer, State::kTakeMore);
        }
    }
    for(int i = 1; i <= deck_state.ace_count && deck_state.max_score > 21; i++){
        deck_state.max_score -= 10;
        deck_state.ace_count--;
    }
    return answer;
}

template<typename CardType>
CowardCard<CardType>* CowardCard<CardType>::CloneImpl() const {
    return new CowardCard(*this);
}

template<typename CardType>
TableCardStrategy<CardType>::TableCardStrategy(): Strategy<CardType, Deck>("TableCard"){}

template<typename CardType>
State TableCardStrategy<CardType>::MakeChoice(Deck& sum, CardType& opponents_card) {
    return table_.MakeChoice(sum.max_score, opponents_card.GetDenominationValue());
}

template<typename CardType>
TableCardStrategy<CardType>* TableCardStrategy<CardType>::CloneImpl() const {
    return new TableCardStrategy(*this);
}

template<typename CardType>
void TableCardStrategy<CardType>::SetTablePath(std::string path){
    table_ = ChooseTable(path);
}

template<typename CardType>
RandomCardStrategy<CardType>::RandomCardStrategy(): Strategy<CardType, Deck>("RandomInt"){
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}

template<typename CardType>
RandomCardStrategy<CardType>::RandomCardStrategy(const RandomCardStrategy& other) : rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}

template<typename CardType>
State RandomCardStrategy<CardType>::MakeChoice(Deck& sum, CardType& opponents_card) {
    int temp = rng_()%100;
    if(temp < 34){
        actual_strategy_ = std::unique_ptr<Strategy<CardType, Deck>>(new G17Card<CardType>);
    }
    else if(34 <= temp && temp < 67){
        actual_strategy_ = std::unique_ptr<Strategy<CardType, Deck>>(new TableCardStrategy<CardType>);
    }
    else{
        actual_strategy_ = std::unique_ptr<Strategy<CardType, Deck>>(new CowardCard<CardType>);
    }
    return actual_strategy_->MakeChoice(sum, opponents_card);
}

template<typename CardType>
RandomCardStrategy<CardType>* RandomCardStrategy<CardType>::CloneImpl() const {
    return new RandomCardStrategy(*this);
}

template class Strategy<Card, Deck>;
template class Strategy<int, int>;
template class G17Card<Card>;
template class CowardCard<Card>;
template class TableCardStrategy<Card>;
template class RandomCardStrategy<Card>;

