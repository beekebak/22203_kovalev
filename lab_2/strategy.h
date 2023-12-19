#include <memory>
#include <iostream>
#include <random>
#include "card.h"
#include "choose_table.h"
#include "game_config.h"

#ifndef STRATEGY_H
#define STRATEGY_H

template <typename CardType, typename DeckType>
class Strategy{
  public:
    Strategy(std::string given_name = "unstated"):name_{given_name} {}
    std::string GetName(){
        return name_;
    }
    State virtual MakeChoice(DeckType& sum, CardType& opponents_card) = 0;
    virtual ~Strategy(){}
    auto Clone() const {
        return std::unique_ptr<Strategy>(CloneImpl());
    }
  protected:
    void ChangeState(State& old_state, State new_state){
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
    void ChangeMaxScore(int& old_max_score, int new_max_score){
        if(new_max_score <= 21 && old_max_score < new_max_score){
            old_max_score = new_max_score;
        }
    }
    virtual Strategy* CloneImpl() const = 0;
    std::string name_;
};

class G16Plain : public Strategy<int, int>{
  public:
    G16Plain(): Strategy<int, int>(">=16"){};
    State virtual MakeChoice(int& sum, int& opponents_card) override{
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
    virtual G16Plain* CloneImpl() const override{
        return new G16Plain(*this);
    }
};

class G18Plain : public Strategy<int, int>{
  public:
    G18Plain(): Strategy<int, int>(">=18"){};
    State virtual MakeChoice(int& sum, int& opponents_card) override{
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
    virtual G18Plain* CloneImpl() const override{
        return new G18Plain(*this);
    }
};

class TablePlainStrategy: public Strategy<int, int>{
  public:
    TablePlainStrategy(): Strategy<int,int>("TableInt"){}
    State virtual MakeChoice(int& sum, int& opponents_card) override{
        return table_.MakeChoice(sum, opponents_card);
    }
    virtual TablePlainStrategy* CloneImpl() const override{
        return new TablePlainStrategy(*this);
    }
  private:
    static ChooseTable table_;
};

class CowardPlain : public Strategy<int, int>{
public:
    CowardPlain(): Strategy<int, int>("CowardPlain"){};
    State virtual MakeChoice(int& sum, int& opponents_card) override{
        State answer = State::kLose;
        if(sum >= 12){
            Strategy<int, int>::ChangeState(answer, State::kStop);
        }
        else{
            Strategy<int, int>::ChangeState(answer, State::kTakeMore);
        }
        return answer;
    }
    virtual CowardPlain* CloneImpl() const override{
        return new CowardPlain(*this);
    }
};

ChooseTable TablePlainStrategy::table_ = ChooseTable(Config::GetInstance().int_table_path_);

class RandomPlainStrategy: public Strategy<int, int>{
public:
    RandomPlainStrategy(): Strategy<int, int>("RandomInt"){
        auto rd = std::random_device();
        rng_ = std::mt19937(rd());
    }
    RandomPlainStrategy(const RandomPlainStrategy& other) : rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}
    ~RandomPlainStrategy() = default;
    State virtual MakeChoice(int& sum, int& opponents_card) override{
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
    virtual RandomPlainStrategy* CloneImpl() const override{
        return new RandomPlainStrategy(*this);
    }
private:
    class RandomException{};
    std::mt19937 rng_;
    std::unique_ptr<Strategy<int,int>> actual_strategy_ = std::unique_ptr<Strategy<int,int>>(new G18Plain);
};

template <typename CardType>
class G17Card : public Strategy<CardType, Deck>{
  public:
    G17Card(): Strategy<CardType, Deck>(">=17"){};
    State virtual MakeChoice(Deck& deck_state, CardType& opponents_card) override{
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
    virtual G17Card* CloneImpl() const override{
        return new G17Card(*this);
    }
};

template <typename CardType>
class CowardCard : public Strategy<CardType, Deck>{
public:
    CowardCard(): Strategy<CardType, Deck>("CowardCard"){};
    State virtual MakeChoice(Deck& deck_state, CardType& opponents_card) override{
        State answer = State::kLose;
        for(int i = 0; i <= deck_state.ace_count; i++){
            Strategy<CardType, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
            if(deck_state.max_score - i*10 >= 12){
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
    virtual CowardCard* CloneImpl() const override{
        return new CowardCard(*this);
    }
};

template <typename CardType>
class TableCardStrategy: public Strategy<CardType, Deck>{
public:
    TableCardStrategy(): Strategy<CardType, Deck>("TableCard"){}
    State virtual MakeChoice(Deck& sum, CardType& opponents_card) override{
        return table_.MakeChoice(sum.max_score, opponents_card.GetDenominationValue());
    }
    virtual TableCardStrategy* CloneImpl() const override{
        return new TableCardStrategy(*this);
    }
private:
    static ChooseTable table_;
};

template <typename CardType>
ChooseTable TableCardStrategy<CardType>::table_ = ChooseTable(Config::GetInstance().card_table_path_);

template <typename CardType>
class RandomCardStrategy: public Strategy<CardType, Deck>{
public:
    RandomCardStrategy(): Strategy<CardType, Deck>("RandomInt"){
        auto rd = std::random_device();
        rng_ = std::mt19937(rd());
    }
    RandomCardStrategy(const RandomCardStrategy& other) : rng_(other.rng_), actual_strategy_(other.actual_strategy_->Clone()) {}
    ~RandomCardStrategy() = default;
    State virtual MakeChoice(Deck& sum, CardType& opponents_card) override{
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
    virtual RandomCardStrategy* CloneImpl() const override{
        return new RandomCardStrategy(*this);
    }
private:
    class RandomException{};
    std::mt19937 rng_;
    std::unique_ptr<Strategy<CardType, Deck>> actual_strategy_ = std::unique_ptr<Strategy<CardType, Deck>>(new G17Card<CardType>);
};

#endif // STRATEGY_H
