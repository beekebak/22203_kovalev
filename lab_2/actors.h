#include<vector>
#include<random>
#include<memory>
#include<stdexcept>
#include"card.h"
#include"strategy.h"

#ifndef ACTORS_H
#define ACTORS_H

namespace dealers{
    template <typename CardType, int deck_count, int deck_size>
    class Dealer{
      public:
        Dealer():deck_(deck_size, deck_count){
            auto rd = std::random_device();
            rng_ = std::mt19937(rd());
        }
        CardType GiveCard(){
            int idx = rng_() % deck_size;
            for(int i = 0; deck_[idx] == 0 && i < deck_size; i++){
                idx = (idx + 1) % deck_size;
            }
            if(deck_[idx] == 0) throw std::range_error("no more cards");
        }
      private:
        std::vector<int> deck_;
        std::mt19937 rng_;
    };

    template <int deck_size>
    class Dealer<int, 0, deck_size>{
      public:
        Dealer(){
            auto rd = std::random_device();
            rng_ = std::mt19937(rd());
        }
        int GiveCard(){return rng_() % deck_size + 1;}
      private:
        std::mt19937 rng_;
    };
}

namespace players{
    template<typename CardType, typename DeckType>
    class Player;

    template<typename CardType>
    class Player<CardType, Deck>{
      public:
        Player(Strategy<CardType, Deck>* strategy) : strategy_(strategy){}
        Player() = default;
        Player(Player&&) = default;
        ~Player() = default;
        int ShowScore(){return state_.max_score;}
        std::string get_strategy_name(){
            return strategy_->GetName();
        }
        int GetFirstCardScore(){
            return players_deck_[0].GetDenominationValue();
        }
        int GetLastCardScore(){
            return players_deck_.back().GetDenominationValue();
        }
        enum State PlayNextMove(CardType opponent_card){
            return strategy_->MakeChoice(state_, opponent_card);
        }
        void RecieveCard(CardType card){
            players_deck_.push_back(card);
        }
      private:
        std::unique_ptr<Strategy<CardType, Deck>> strategy_;
        std::vector<CardType> players_deck_;
        Deck state_;
    };

    template<>
    class Player<int, int>{
      public:
        Player(Strategy<int, int>* strategy) : strategy_(strategy){}
        Player() = default;
        Player(Player&&) = default;
        ~Player() = default;
        int ShowScore(){
            return state_;
        }
        std::string GetStrategyName(){
            return strategy_->GetName();
        }
        int GetFirstCardScore(){
            return players_deck_[0];
        }
        int GetLastCardScore(){
            return players_deck_.back();
        }
        enum State PlayNextMove(int opponent_card){
            return strategy_->MakeChoice(state_, opponent_card);
        }
        void RecieveCard(int card){
            players_deck_.push_back(card);
        }
      private:
        std::unique_ptr<Strategy<int, int>> strategy_;
        std::vector<int> players_deck_;
        int state_ = 0;
    };
}

#endif // ACTORS_H
