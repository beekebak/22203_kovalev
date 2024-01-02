#include "game.h"

template<typename CardType, typename DeckType>
Game<CardType, DeckType>::Game(std::vector<Player<CardType, DeckType>>& players,
    Logger<CardType, DeckType>* logger, MatchType type, GameConfig& config):
    logger_{std::unique_ptr<Logger<CardType,DeckType>>(logger)},
    game_type_{type}, config_{config}{
    for(int i = 0; i < players.size(); i++){
        players_set_.emplace_back(players[i]);
        result_table_.table.push_back(0);
    }
    InitializeLoadableStrategies();
}

template<typename CardType, typename DeckType>
void Game<CardType, DeckType>::ProcessEndgame(){
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

template<typename CardType, typename DeckType>
void Game<CardType, DeckType>::OrganizeTournament(){
    for(int i = 0; i < players_set_.size(); i++){
        for(int j = i+1; j < players_set_.size(); j++){
            MatchResult result = StartNewMatch(players_set_[i], players_set_[j], i+1, j+1);
            if(result == MatchResult::kP1Win){
                result_table_.table[i]++;
                logger_->PrintMatchResult(i+1);
            }
            else if(result == MatchResult::kP2Win){
                result_table_.table[j]++;
                logger_->PrintMatchResult(j+1);
            }
            else if(result == MatchResult::kDraw){
                logger_->PrintMatchResult(kNoWinner);
            }
            else return;
        }
    }
    ProcessEndgame();
}

template<typename CardType, typename DeckType>
MatchResult Game<CardType, DeckType>::StartNewMatch(Player<CardType, DeckType>& first,
                          Player<CardType, DeckType>& second,
                          int first_number, int second_number){
    logger_->PrintMatchStartMessage(first, second);
    Match<CardType, DeckType> match =
        Match<CardType, DeckType>(first, second,
                                  Dealer<CardType>(config_.deck_size_, config_.deck_count_),
                                  logger_->Clone(), game_type_, first_number,
                                  second_number);
    return match.Play();
}

template<typename CardType, typename DeckType>
void Game<CardType, DeckType>::InitializeLoadableStrategies(){
    if constexpr (std::is_same_v<CardType, int>)TablePlainStrategy::SetTablePath(config_.int_table_path_);
    if constexpr (std::is_same_v<CardType, Card>)TableCardStrategy<CardType>::SetTablePath(config_.card_table_path_);
}

template<typename CardType, typename DeckType>
std::string Game<CardType, DeckType>::ResultTable::ToString(){
    std::string representation = "";
    for(int i = 0; i < table.size(); i++){
        representation += "Player "  + std::to_string(i+1) + ": " + std::to_string(table[i]) + "\n";
    }
    return representation;
}

template class Game<int, int>;
template class Game<Card, Deck>;
