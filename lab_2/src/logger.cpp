#include "logger.h"

template<typename CardType, typename DeckType>
void Logger<CardType, DeckType>::PrintMatchResult(int player_number){
    if(player_number == kNoWinner){
        std::cout << "Ничья." << std::endl;
    }
    else{
        std::cout << "Игрок " << player_number << " победил." << std::endl;
    }
}

template<typename CardType, typename DeckType>
std::unique_ptr<Logger<CardType, DeckType>> Logger<CardType, DeckType>::Clone() const {
    return std::unique_ptr<Logger>(CloneImpl());
}

template<typename CardType, typename DeckType>
void VerboseLogger<CardType, DeckType>::PrintMoveLog(int number, Player<CardType, DeckType>& player,
                  State move_result){
    if(move_result == State::kTakeMore)
        std::cout << "Игрок " << number << " " << player.ShowScore() << " последняя "
                  << player.GetLastCardScore() << std::endl;
    else std::cout << "Игрок " << number << " " << "не брал карт" << std::endl;
}

template<typename CardType, typename DeckType>
void VerboseLogger<CardType, DeckType>::PrintMatchStartMessage(Player<CardType,DeckType>& first,
                            Player<CardType,DeckType>& second){
    std::cout << "Стратегия первого игрока " << first.GetStrategyName() << std::endl;
    std::cout << "Стратегия второго игрока " << second.GetStrategyName() << std::endl;
}

template<typename CardType, typename DeckType>
VerboseLogger<CardType, DeckType>* VerboseLogger<CardType, DeckType>::CloneImpl() const{
    return new VerboseLogger(*this);
}

template<typename CardType, typename DeckType>
SilentLogger<CardType, DeckType>* SilentLogger<CardType, DeckType>::CloneImpl() const{
    return new SilentLogger(*this);
}

template<typename CardType, typename DeckType>
void TournamentLogger<CardType, DeckType>::PrintGameResult(int winner_number,
                     std::string table_string_representation){
    if(winner_number == kNoWinner){
        std::cout << "Ничья в игре." << std::endl;
    }
    else{
        std::cout << "Игрок " << winner_number+1 << " выиграл игру." << std::endl;
    }
    std::cout << table_string_representation << std::endl;
}

template<typename CardType, typename DeckType>
TournamentLogger<CardType, DeckType>* TournamentLogger<CardType, DeckType>::CloneImpl() const{
    return new TournamentLogger(*this);
}

template class Logger<int, int>;
template class Logger<Card, Deck>;
template class VerboseLogger<int, int>;
template class VerboseLogger<Card, Deck>;
template class SilentLogger<int, int>;
template class SilentLogger<Card, Deck>;
template class TournamentLogger<int, int>;
template class TournamentLogger<Card, Deck>;