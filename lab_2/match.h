#include "actors.h"
#include "logger.h"

#ifndef MATCH_H
#define MATCH_H

enum class MatchResult{
    kP1Win,
    kP2Win,
    kDraw
};

template<typename CardType, typename DeckType, int deck_count, int deck_size>
class Match
{
  public:
    Match(players::Player<CardType, DeckType>& f,
          players::Player<CardType, DeckType>& s,
          dealers::Dealer<CardType, deck_count, deck_size>& d,
          std::unique_ptr<Logger<CardType, DeckType>>& l):
          first_{f}, second_{s}, dealer_{d}, logger_{l} {}

    MatchResult DetermineWinner(State first_state, State second_state, int first_score, int second_score){
        switch(first_state){
          case State::kLose:
            if(second_state == State::kLose) return MatchResult::kDraw;
            else return MatchResult::kP2Win;
            break;
          case State::kStop:
            if(second_state == State::kLose){
                return MatchResult::kP1Win;
            }
            else if(second_state == State::kTakeMore){
                throw BadStateException();
            }
            else if(first_.score > second_.score){
                return MatchResult::kP2Win;
            }
            else if(first_.score == second_.score){
                return MatchResult::kDraw;
            }
            else if(first_.score < second_.score){
                return MatchResult::kP2Win;
            }
            break;
          case State::kTakeMore:
            throw BadStateException();
        }
    }

    MatchResult play(){
        enum State first_res{State::kTakeMore};
        enum State second_res{State::kTakeMore};
        do {
            first_res = first_.PlayNextMove(second_.GetFirstCardScore);
            if(first_res == State::kTakeMore) first_.RecieveCard(dealer_.GiveCard());
            logger_->PrintMoveLog(first_, first_res);
            second_res = second_.PlayNextMove(first_.GetFirstCardScore);
            if(second_res == State::kTakeMore) second_.RecieveCard(dealer_.GiveCard());
            logger_->PrintMoveLog(second_, second_res);
        } while(first_res == State::kTakeMore || second_res == State::kTakeMore);
        return DetermineWinner(first_, second_, first_.ShowScore(), second_.ShowScore());
    }
  private:
    class BadStateException{};
    players::Player<CardType, DeckType> first_;
    players::Player<CardType, DeckType> second_;
    dealers::Dealer<CardType, deck_count, deck_size> dealer_;
    std::unique_ptr<Logger<CardType, DeckType>> logger_;
};

#endif // MATCH_H
