#include<vector>
#include<random>
#include<memory>
#include"card.h"
#include"strategy.h"

#ifndef ACTORS_H
#define ACTORS_H

namespace dealers{
    template <typename T>
    class dealer{
      public:
        virtual T get_card() = 0;
        virtual ~dealer();
      protected:
        std::mt19937 rng; //random number generator;
    };

    class numbers_dealer:public dealer<int>{
      public:
        numbers_dealer();
        virtual int get_card() override;
    };

    class cards_dealer:public dealer<card>{
      public:
        cards_dealer(int deck_count=1);
        virtual card get_card() override;
      private:
        std::vector<int> deck;
    };
}

namespace players{
    template<typename T, typename V>
    class player{
      public:
        virtual int show_score()=0;
        virtual state play_next_move(T opponent_card)=0;
        void recieve_card(T);
        virtual ~player();
      protected:
        std::vector<T> players_deck;
        V state;
    };
    class numbers_player : public player<int, int>{
      public:
        int show_score() override;
        enum state play_next_move(int opponent_card) override;
      private:
        std::unique_ptr<numbers_strategy> strat;
    };
    class cards_player : public player<card, deck>{
      public:
        int show_score() override;
        enum state play_next_move(card opponent_card) override;
      private:
        std::unique_ptr<card_strategy> strat;
    };
}

#endif // ACTORS_H
