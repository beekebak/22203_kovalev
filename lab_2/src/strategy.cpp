#include "strategy.h"

template<typename Card, typename DeckType>
std::string Strategy<Card, DeckType>::GetName(){
    return name_;
}

template<typename Card, typename DeckType>
std::unique_ptr<Strategy<Card, DeckType>> Strategy<Card, DeckType>::Clone() const{
    return std::unique_ptr<Strategy<Card, DeckType>>(CloneImpl());
}

template<typename Card, typename DeckType>
void Strategy<Card, DeckType>::ChangeMaxScore(int& old_max_score, int new_max_score){
    if(new_max_score <= 21 && old_max_score < new_max_score){
        old_max_score = new_max_score;
    }
}

template<typename Card, typename DeckType>
void Strategy<Card, DeckType>::ChangeState(State& old_state, State new_state){
    switch(old_state){
    case State::kLose:
        old_state = new_state;
        break;
    case State::kTakeMore:
        old_state = new_state == State::kStop ? new_state : old_state;
        break;
    case State::kStop:
        break;
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

FactoryInitializator<Strategy<int, int>, std::string,
                    G16Plain> G16PlainInitialization("16ge");

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

FactoryInitializator<Strategy<int, int>, std::string,
                    G18Plain> G18PlainInitialization("18ge");

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

FactoryInitializator<Strategy<int, int>, std::string,
                    TablePlainStrategy> TablePlainInitialization("table_int");

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

FactoryInitializator<Strategy<int, int>, std::string,
                    CowardPlain> CowardPlainInitialization("coward_int");

RandomPlainStrategy::RandomPlainStrategy(): Strategy<int, int>("RandomInt"){
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}

RandomPlainStrategy::RandomPlainStrategy(const RandomPlainStrategy& other) : Strategy<int,int>(other.name_),
    rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}
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

FactoryInitializator<Strategy<int, int>, std::string,
                    RandomPlainStrategy> RandomPlainInitialization("random_int");


G17Card::G17Card(): Strategy<Card, Deck>(">=17"){};


State G17Card::MakeChoice(Deck& deck_state, Card& opponents_card){
    State answer = State::kLose;
    for(int i = 0; i <= deck_state.ace_count; i++){
        Strategy<Card, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
        if(deck_state.max_score - i*10 > 21){
            Strategy<Card, Deck>::ChangeState(answer, State::kLose);
        }
        else if(deck_state.max_score - i*10 > 16){
            Strategy<Card, Deck>::ChangeState(answer, State::kStop);
        }
        else{
            Strategy<Card, Deck>::ChangeState(answer, State::kTakeMore);
        }
    }
    for(int i = 1; i <= deck_state.ace_count && deck_state.max_score > 21; i++){
        deck_state.max_score -= 10;
        deck_state.ace_count--;
    }
    return answer;
}


G17Card* G17Card::CloneImpl() const{
    return new G17Card(*this);
}


FactoryInitializator<Strategy<Card, Deck>, std::string,
                    G17Card> G17CardInitialization("17ge");


CowardCard::CowardCard(): Strategy<Card, Deck>("CowardCard"){};


State CowardCard::MakeChoice(Deck& deck_state, Card& opponents_card){
    State answer = State::kLose;
    for(int i = 0; i <= deck_state.ace_count; i++){
        Strategy<Card, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
        if(deck_state.max_score - i*10 >= 22){
            Strategy<Card, Deck>::ChangeState(answer, State::kLose);
        }
        else if(deck_state.max_score - i*10 >= 12){
            Strategy<Card, Deck>::ChangeState(answer, State::kStop);
        }
        else{
            Strategy<Card, Deck>::ChangeState(answer, State::kTakeMore);
        }
    }
    for(int i = 1; i <= deck_state.ace_count && deck_state.max_score > 21; i++){
        deck_state.max_score -= 10;
        deck_state.ace_count--;
    }
    return answer;
}


CowardCard* CowardCard::CloneImpl() const {
    return new CowardCard(*this);
}


FactoryInitializator<Strategy<Card, Deck>, std::string,
                    CowardCard> CowardCardInitialization("coward_card");


TableCardStrategy::TableCardStrategy(): Strategy<Card, Deck>("TableCard"){}


State TableCardStrategy::MakeChoice(Deck& sum, Card& opponents_card) {
    return table_.MakeChoice(sum.max_score, opponents_card.GetDenominationValue());
}


TableCardStrategy* TableCardStrategy::CloneImpl() const {
    return new TableCardStrategy(*this);
}


void TableCardStrategy::SetTablePath(std::string path){
    table_ = ChooseTable(path);
}


FactoryInitializator<Strategy<Card, Deck>, std::string,
                    TableCardStrategy> TableCardInitialization("table_card");


RandomCardStrategy::RandomCardStrategy(): Strategy<Card, Deck>("RandomCard"){
    auto rd = std::random_device();
    rng_ = std::mt19937(rd());
}


RandomCardStrategy::RandomCardStrategy(const RandomCardStrategy& other) :
    rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}


State RandomCardStrategy::MakeChoice(Deck& sum, Card& opponents_card) {
    int temp = rng_()%100;
    if(temp < 34){
        actual_strategy_ = std::unique_ptr<Strategy<Card, Deck>>(new G17Card);
    }
    else if(34 <= temp && temp < 67){
        actual_strategy_ = std::unique_ptr<Strategy<Card, Deck>>(new TableCardStrategy);
    }
    else{
        actual_strategy_ = std::unique_ptr<Strategy<Card, Deck>>(new CowardCard);
    }
    return actual_strategy_->MakeChoice(sum, opponents_card);
}


RandomCardStrategy* RandomCardStrategy::CloneImpl() const {
    return new RandomCardStrategy(*this);
}


FactoryInitializator<Strategy<Card, Deck>, std::string,
                    RandomCardStrategy> RandomCardInitialization("random_card");

template class Strategy<Card, Deck>;
template class Strategy<int, int>;
