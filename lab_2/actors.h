#include <vector>
#include <random>
#include <memory>
#include <stdexcept>
#include "card.h"
#include "strategy.h"

#ifndef ACTORS_H
#define ACTORS_H

namespace dealers{
    template <typename CardType>
    class Dealer{
      public:
        Dealer():deck_(std::vector<int>(Config::GetInstance().deck_size_, Config::GetInstance().deck_count_)){
            auto rd = std::random_device();
            rng_ = std::mt19937(rd());
        }
        Dealer(Dealer&) = default;
        Dealer(Dealer&&) = default;
        ~Dealer() = default;
        CardType GiveCard(){
            int idx = rng_() % deck_.size();
            for(int i = 0; deck_[idx] == 0 && i < deck_.size(); i++){
                idx = (idx + 1) % deck_.size();
            }
            if(deck_[idx] == 0) throw std::range_error("no more cards");
            deck_[idx]--;
            return CardType(idx);
        }
      private:
        std::vector<int> deck_;
        std::mt19937 rng_;
    };

    template <>
    class Dealer<int>{
      public:
        Dealer(){
            auto rd = std::random_device();
            rng_ = std::mt19937(rd());
        }
        Dealer(Dealer&) = default;
        Dealer(Dealer&&) = default;
        ~Dealer() = default;
        int GiveCard(){return rng_() % Config::GetInstance().deck_size_ + 1;}
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
        Player(Player& other) : state_(other.state_), players_deck_(other.players_deck_),
                                strategy_(other.strategy_->Clone()){}
        Player(Player&&) = default;
        ~Player() = default;
        int ShowScore(){return state_.max_score;}
        std::string GetStrategyName(){
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
            state_.max_score += card.GetDenominationValue();
            if (card.GetDenominationValue() == 11){
                state_.ace_count++;
            }
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
        Player(const Player& other) : state_(other.state_), players_deck_(other.players_deck_),
                                strategy_(other.strategy_->Clone()) {}
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
            state_ += card;
        }
      private:
        std::unique_ptr<Strategy<int, int>> strategy_;
        std::vector<int> players_deck_;
        int state_ = 0;
    };
}

#endif // ACTORS_H
