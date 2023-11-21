#include "actors.h"

dealers::numbers_dealer::numbers_dealer(){
    auto rd = std::random_device();
    rng = std::mt19937(rd());
}

int dealers::numbers_dealer::get_card(){
    return rng()%10+1;
}

dealers::cards_dealer::cards_dealer(int deck_count):deck(52, deck_count){
    auto rd = std::random_device();
    rng = std::mt19937(rd());
}

card dealers::cards_dealer::get_card(){
    int idx = 0;
    do{
        idx = rng()%52;
    } while(deck[idx] > 0);
    deck[idx]--;
    switch(idx%13){
        case 12: return card(denomination::Ace, static_cast<suit>(idx/13));
        case 11: return card(denomination::King, static_cast<suit>(idx/13));
        case 10: return card(denomination::Queen, static_cast<suit>(idx/13));
        case 9: return card(denomination::Jack, static_cast<suit>(idx/13));
        default: return card(idx%13+2, static_cast<suit>(idx/13));
    }
}

template<typename T, typename V>
void players::player<T, V>::recieve_card(T card){
    players_deck.push_back(card);
}

int players::numbers_player::show_score(){
    return state;
}

enum state players::numbers_player::play_next_move(int opponent_card){
    return strat->make_choice(state, opponent_card);
}

int players::cards_player::show_score(){
    return state.max_score;
}

enum state players::cards_player::play_next_move(card opponent_card){
    return strat->make_choice(state, opponent_card);
}
