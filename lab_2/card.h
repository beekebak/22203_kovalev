#include <unordered_map>
#include <string>

#ifndef CARD_H
#define CARD_H

static const int suits_count = 4;
static const int ranks_count = 13;

class card{
  public:
    int get_denomination_value(){
        if(order % ranks_count == 12) return 11; //ace
        else if (order % ranks_count < 9) return order % ranks_count + 2; //cards with number
        return 10; //jack, queen, king
    }
    std::string get_suit() {return suits.at(order%suits_count);}
    std::string get_rank() {return ranks.at(order%ranks_count);}
    card(int ord): order{ord} {}
  private:
    static const std::unordered_map<int, std::string> suits;
    static const std::unordered_map<int, std::string> ranks;
    int order;
};

const std::unordered_map<int, std::string> card::suits = {{0, "diamonds"}, {1, "hearts"}, {2, "spades"}, {3, "clubs"}};
const std::unordered_map<int, std::string> card::ranks = {{0, "2"},{1, "3"},{2, "4"},{3, "5"},{4, "6"}, {5, "7"},{6, "8"},{7, "9"},{8, "10"},
                                                                  {9, "jack"},{10, "queen"},{11, "king"},{12, "ace"}};

struct deck{
    int points=0;
    int ace_count=0;
    int max_score=0;
};

#endif // CARD_H
