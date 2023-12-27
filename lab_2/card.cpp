#include "card.h"

int Card::GetDenominationValue(){
    if(order_ % kRanksCount == 12){
        return kAceDenomination;
    }
    else if (order_ % kRanksCount < 9){
        return order_ % kRanksCount + 2; //cards with number
    }
    return kKingQueenJackDenomination;
}

std::string Card::GetSuit() {
    return suits_.at(order_%kSuitsCount);
}

std::string Card::GetRank() {
    return ranks_.at(order_%kRanksCount);
}

Card::Card(int order): order_{order} {}
