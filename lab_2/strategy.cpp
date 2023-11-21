#include "strategy.h"

template <typename T, typename V>
void strategy<T,V>::change_state(state& old_state, state new_state){
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

template <typename T, typename V>
void strategy<T,V>::change_max_score(int& old_max_score, int new_max_score){
    if(new_max_score <= 21 && old_max_score < new_max_score) old_max_score = new_max_score;
}

state ge16_plain::make_choice(int sum, int opponents_card){
    return sum >= 16 ? state::stop : state::take_more;
}

state ge18_plain::make_choice(int sum, int opponents_card){
    return sum >= 18 ? state::stop : state::take_more;
}
state ge17_card::make_choice(deck deck_state, card opponents_card){
    state answer = state::lose;
    for(int i = 0; i < deck_state.ace_count; i++){
        change_max_score(deck_state.max_score, deck_state.points - i*10);
        if(deck_state.max_score > 21) change_state(answer, state::lose);
        else if(deck_state.max_score > 16) change_state(answer, state::stop);
        else change_state(answer, state::take_more);
    }
    return answer;
}
