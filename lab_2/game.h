#include <vector>
#include "actors.h"
#include "card.h"
#include "logger.h"
#include "match.h"
#include "strategy.h"
#include "factory.h"

#ifndef GAME_H
#define GAME_H

enum class Winner{
    kFirst,
    kSecond
};

template <typename CardType, typename DeckType>
class Game{
  public:
    Game(std::vector<players::Player<CardType, DeckType>> players, Logger<CardType, DeckType>* logger): logger_(logger){
        for(int i = 0; i < players.size(); i++){
            players_set_.push_back(players[i]);
            result_table_.table.push_back(0);
        }
    }

    MatchResult StartNewMatch(players::Player<CardType, DeckType> first,
                              players::Player<CardType, DeckType> second){
        logger_->PrintMatchStartMessage(first, second);
        Match<CardType, DeckType, deck_count_, deck_size_> match =
            Match(first, second,
            dealers::Dealer<CardType, deck_count_, deck_size_>(), logger_);
        return match.play();
    }

    void ProcessEndgame(){
        int winner_index = 0;
        int max_score = 0;
        for(int i = 1; i < result_table_.table.size(); i++){
            if(result_table_.table[i] > max_score){
                max_score = result_table_.table[i];
                winner_index = 0;
            }
            else if(result_table_.table[i] == max_score){
                winner_index = kNoWinner;
            }
        }
        logger_->PrintGameResult(winner_index, result_table_.ToString());
    }

    void OrganizeTournament(){
        for(int i = 0; i < players_set_.size(); i++){
            for(int j = i+1; j < players_set_.size(); j++){
                MatchResult result = StartNewMatch(players_set_[i], players_set_[j]);
                if(result == MatchResult::kP1Win){
                    result_table_[i]++;
                    logger_->PrintMatchResult(i);
                }
                else if(result == MatchResult::kP2Win){
                    result_table_[j]++;
                    logger_->PrintMatchResult(i);
                }
                else{
                    logger_->PrintMatchResult(kNoWinner);
                }
            }
        }
        ProcessEndgame();
    }

  private:
    constexpr static int deck_count_ = 1;
    constexpr static int deck_size_ = 52;
    std::vector<players::Player<CardType, DeckType>> players_set_;
    std::unique_ptr<Logger<CardType,DeckType>> logger_;
    struct ResultTable{
        std::vector<int> table;
        std::string ToString(){
            std::string representation = "";
            for(int i = 0; i < table.size(); i++){
                representation += "Player "  + std::to_string(i+1) + ": " + std::to_string(table[i]) + "\n";
            }
            return representation;
        };
    };
    ResultTable result_table_;
};

#endif // GAME_H
