#include "match.h"

template<typename CardType, typename DeckType>
Match<CardType, DeckType>::Match(Player<CardType, DeckType> f,
      Player<CardType, DeckType> s,
      Dealer<CardType> d,
      std::unique_ptr<Logger<CardType, DeckType>> l,
      MatchType type, int first_number, int second_number,
      std::istream& stream):
    first_{f}, second_{s}, dealer_{d}, logger_{l->Clone()},
    match_type_{type}, first_player_number_{first_number},
    second_player_number_{second_number}, in_stream_{stream} {}

template<typename CardType, typename DeckType>
MatchResult Match<CardType, DeckType>::DetermineWinner(State first_state, State second_state, int first_score, int second_score){
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
            return MatchResult::kP1Win;
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
    throw BadStateException();
}

template<typename CardType, typename DeckType>
MatchResult Match<CardType, DeckType>::play(){
    enum State first_res{State::kTakeMore};
    enum State second_res{State::kTakeMore};
    first_.RecieveCard(dealer_.GiveCard());
    logger_->PrintMoveLog(first_player_number_, first_, first_res);
    second_.RecieveCard(dealer_.GiveCard());
    logger_->PrintMoveLog(second_player_number_, second_, second_res);
    do {
        if(match_type_ == MatchType::kManual){
            std::string input;
            in_stream_ >> input;
            if(input == "quit"){
                throw GameQuitException();
            }
        }
        first_res = first_.PlayNextMove(second_.GetFirstCardScore());
        if(first_res == State::kTakeMore) first_.RecieveCard(dealer_.GiveCard());
        logger_->PrintMoveLog(first_player_number_, first_, first_res);
        second_res = second_.PlayNextMove(first_.GetFirstCardScore());
        if(second_res == State::kTakeMore) second_.RecieveCard(dealer_.GiveCard());
        logger_->PrintMoveLog(second_player_number_, second_, second_res);
    } while(first_res == State::kTakeMore || second_res == State::kTakeMore);
    return DetermineWinner(first_res, second_res, first_.ShowScore(), second_.ShowScore());
}

template class Match<int, int>;
template class Match<Card, Deck>;
