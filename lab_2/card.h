#include <unordered_map>
#include <string>

#ifndef CARD_H
#define CARD_H

static const int kSuitsCount = 4;
static const int kRanksCount = 13;
static const int kAceDenomination = 11;
static const int kKingQueenJackDenomination = 10;

class Card{
  public:
    int GetDenominationValue();
    std::string GetSuit();
    std::string GetRank();
    Card(int order = -1);
  private:
    static const std::unordered_map<int, std::string> suits_;
    static const std::unordered_map<int, std::string> ranks_;
    int order_;
};

inline const std::unordered_map<int, std::string> Card::suits_ = {{0, "diamonds"}, {1, "hearts"}, {2, "spades"}, {3, "clubs"}};
inline const std::unordered_map<int, std::string> Card::ranks_ = {{0, "2"},{1, "3"},{2, "4"},{3, "5"},{4, "6"}, {5, "7"},{6, "8"},{7, "9"},{8, "10"},
                                                                  {9, "jack"},{10, "queen"},{11, "king"},{12, "ace"}};

struct Deck{
    int points=0;
    int ace_count=0;
    int max_score=0;
};

#endif // CARD_H
