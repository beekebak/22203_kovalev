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
    Game(std::vector<players::Player<CardType, DeckType>>& players):
          logger_(std::unique_ptr<Logger<CardType,DeckType>>(new VerboseLogger<CardType, DeckType>)){
        for(int i = 0; i < players.size(); i++){
            players_set_.emplace_back(players[i]);
            result_table_.table.push_back(0);
            std::cout << std::endl;
        }
    }

    void ProcessEndgame(){
        int winner_index = 0;
        int max_score = result_table_.table[0];
        for(int i = 1; i < result_table_.table.size(); i++){
            if(result_table_.table[i] > max_score){
                max_score = result_table_.table[i];
                winner_index = i;
            }
            else if(result_table_.table[i] == max_score){
                winner_index = kNoWinner;
            }
        }
        logger_->PrintGameResult(winner_index, result_table_.ToString());
    }

    void OrganizeTournament(){
        //std::cout << players_set_.size();
        for(int i = 0; i < players_set_.size(); i++){
            for(int j = i+1; j < players_set_.size(); j++){
                MatchResult result = StartNewMatch(players_set_[i], players_set_[j]);
                if(result == MatchResult::kP1Win){
                    result_table_.table[i]++;
                    logger_->PrintMatchResult(i+1);
                }
                else if(result == MatchResult::kP2Win){
                    result_table_.table[j]++;
                    logger_->PrintMatchResult(j+1);
                }
                else{
                    logger_->PrintMatchResult(kNoWinner);
                }
            }
        }
        ProcessEndgame();
    }

  private:
    int deck_count_ = 1;
    int deck_size_ = 52;
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

    MatchResult StartNewMatch(players::Player<CardType, DeckType>& first,
                              players::Player<CardType, DeckType>& second){
        logger_->PrintMatchStartMessage(first, second);
        Match<CardType, DeckType> match =
            Match<CardType, DeckType>(first, second,
                                      dealers::Dealer<CardType>(deck_size_, deck_count_), logger_->Clone());
        return match.play();
    }
};

#endif // GAME_H
