#include<vector>
#include<random>
#include<memory>
#include<stdexcept>
#include"card.h"
#include"strategy.h"

#ifndef ACTORS_H
#define ACTORS_H

namespace dealers{
    template <typename T, int deck_count>
    class dealer{
      public:
        dealer():deck(52, deck_count){
            auto rd = std::random_device();
            rng = std::mt19937(rd());
        }
        T get_card(){
            int idx = rng()%52;
            for(int i = 0; deck[idx] == 0 && i < 52; i++){
                idx = (idx + 1) % 52;
            }
            if(deck[idx] == 0) throw std::range_error("no more cards");
        }
      private:
        std::vector<int> deck;
        std::mt19937 rng; //random number generator;
    };

    template <>
    class dealer<int, 0>{
      public:
        dealer(){
            auto rd = std::random_device();
            rng = std::mt19937(rd());
        }
        int get_card(){return rng()%10+1;}
      private:
        std::mt19937 rng; //random number generator;
    };
}

namespace players{
    template<typename T, typename V>
    class player{}; //don't know how to forbid

    template<typename T>
    class player<T, deck>{
      public:
        int get_score(){return state.max_score;}
        std::string get_strategy_name(){return strat->get_name();}
        int get_last_card_score(){return players_deck.back().get_denomination_value();}
        enum state play_next_move(T opponent_card){return strat->make_choice(state, opponent_card);}
        void recieve_card(T card){players_deck.push_back(card);}
      private:
        std::unique_ptr<strategy<T, deck>> strat;
        std::vector<T> players_deck;
        deck state;
    };

    template<>
    class player<int, int>{
      public:
        int show_score(){return state;}
        std::string get_strategy_name(){return strat->get_name();}
        int get_last_card_score(){return players_deck.back();}
        enum state play_next_move(int opponent_card){return strat->make_choice(state, opponent_card);};
        void recieve_card(int card){players_deck.push_back(card);}
      private:
        std::unique_ptr<strategy<int, int>> strat;
        std::vector<int> players_deck;
        int state;
    };
}

#endif // ACTORS_H
