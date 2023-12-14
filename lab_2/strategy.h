#include <memory>
#include "card.h"

#ifndef STRATEGY_H
#define STRATEGY_H

enum class State{
    kTakeMore,
    kStop,
    kLose
};

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

template <typename CardType>
class G17Card : public Strategy<CardType, Deck>{
  public:
    G17Card(): Strategy<CardType, Deck>(">=17"){};
    State virtual MakeChoice(Deck& deck_state, CardType& opponents_card) override{
        State answer = State::kLose;
        for(int i = 0; i <= deck_state.ace_count; i++){
            Strategy<CardType, Deck>::ChangeMaxScore(deck_state.max_score, deck_state.points - i*10);
            if(deck_state.max_score > 21){
                Strategy<CardType, Deck>::ChangeState(answer, State::kLose);
            }
            else if(deck_state.max_score > 16){
                Strategy<CardType, Deck>::ChangeState(answer, State::kStop);
            }
            else{
                Strategy<CardType, Deck>::ChangeState(answer, State::kTakeMore);
            }
        }
        return answer;
    }
    virtual G17Card* CloneImpl() const override{
        return new G17Card(*this);
    }
};


#endif // STRATEGY_H
