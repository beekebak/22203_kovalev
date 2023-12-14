#include "actors.h"
#include "logger.h"

#ifndef MATCH_H
#define MATCH_H

enum class MatchResult{
    kP1Win,
    kP2Win,
    kDraw
};

template<typename CardType, typename DeckType>
class Match
{
  public:
    Match(players::Player<CardType, DeckType> f,
          players::Player<CardType, DeckType> s,
          dealers::Dealer<CardType> d,
          std::unique_ptr<Logger<CardType, DeckType>> l):
          first_{f}, second_{s}, dealer_{d}, logger_{l->Clone()} {}

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
            else if(first_score > second_score){
                return MatchResult::kP2Win;
            }
            else if(first_score == second_score){
                return MatchResult::kDraw;
            }
            else if(first_score < second_score){
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
        first_.RecieveCard(dealer_.GiveCard());
        logger_->PrintMoveLog(1, first_, first_res);
        second_.RecieveCard(dealer_.GiveCard());
        logger_->PrintMoveLog(2, second_, second_res);
        do {
            first_res = first_.PlayNextMove(second_.GetFirstCardScore());
            if(first_res == State::kTakeMore) first_.RecieveCard(dealer_.GiveCard());
            logger_->PrintMoveLog(1, first_, first_res);
            second_res = second_.PlayNextMove(first_.GetFirstCardScore());
            if(second_res == State::kTakeMore) second_.RecieveCard(dealer_.GiveCard());
            logger_->PrintMoveLog(2, second_, second_res);
        } while(first_res == State::kTakeMore || second_res == State::kTakeMore);
        return DetermineWinner(first_res, second_res, first_.ShowScore(), second_.ShowScore());
    }
  private:
    class BadStateException{};
    players::Player<CardType, DeckType> first_;
    players::Player<CardType, DeckType> second_;
    dealers::Dealer<CardType> dealer_;
    std::unique_ptr<Logger<CardType, DeckType>> logger_;
};

#endif // MATCH_H
