#include "card.h"

#ifndef STRATEGY_H
#define STRATEGY_H

enum class state{take_more, stop, lose};

template <typename T, typename V>
class strategy{
  public:
    strategy(std::string given_name):name{given_name} {}
    std::string get_name(){return name;}
    state virtual make_choice(T sum, V opponents_card) = 0;
    virtual ~strategy();
  protected:
    void change_state(state& old_state, state new_state){
        switch(old_state){
          case state::lose:
            old_state = new_state;
            break;
          case state::take_more:
            old_state = new_state == state::stop ? new_state : old_state;
            break;
          case state::stop: break;
        }
    }
    void change_max_score(int& old_max_score, int new_max_score){
        if(new_max_score <= 21 && old_max_score < new_max_score) old_max_score = new_max_score;
    }
    std::string name = "unstated";
};

class ge16_plain : public strategy<int, int>{
  public:
    ge16_plain(): strategy<int, int>(">=16"){};
    state virtual make_choice(int sum, int opponents_card) override;
};

class ge18_plain : public strategy<int, int>{
  public:
    ge18_plain(): strategy<int, int>(">=18"){};
    state virtual make_choice(int sum, int opponents_card) override;
};

template <typename T>
class ge17_card : public strategy<T, deck>{
  public:
    ge17_card: strategy<T, deck>(">=17");
    state virtual make_choice(deck deck_state, card opponents_card) override{
        state answer = state::lose;
        for(int i = 0; i < deck_state.ace_count; i++){
            strategy<T, deck>::change_max_score(deck_state.max_score, deck_state.points - i*10);
            if(deck_state.max_score > 21) strategy<T, deck>::change_state(answer, state::lose);
            else if(deck_state.max_score > 16) strategy<T, deck>::change_state(answer, state::stop);
            else strategy<T, deck>::change_state(answer, state::take_more);
        }
        return answer;
    }
};


#endif // STRATEGY_H
