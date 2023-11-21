#ifndef CARD_H
#define CARD_H

enum class suit{diamonds=0, hearts=1, spades=2, clubs=3};

enum class denomination{Jack = 10, Queen = 10, King = 10, Ace = 11};

struct card{
    int card_denomination;
    suit card_suit;
    card(int value, suit cover): card_denomination{value}, card_suit{cover} {}
    card(denomination value, suit cover): card_denomination{static_cast<int>(value)}, card_suit{cover} {}
};

struct deck{
    int points=0;
    int ace_count=0;
    int max_score=0;
};

#endif // CARD_H
