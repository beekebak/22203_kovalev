#include "card.h"

#ifndef STRATEGY_H
#define STRATEGY_H

enum class state{take_more, stop, lose};

template <typename T, typename V>
class strategy{
  public:
    int a = 10;
    state virtual make_choice(T sum, V opponents_card) = 0;
    virtual ~strategy();
  protected:
    void change_state(state& old_state, state new_state);
    void change_max_score(int& old_max_score, int new_max_score);
};

class numbers_strategy : public strategy<int, int>{};

class card_strategy : public strategy<deck, card>{};

class ge16_plain : public numbers_strategy{
  public:
    state virtual make_choice(int sum, int opponents_card) override;
};

class ge18_plain : public numbers_strategy{
  public:
    state virtual make_choice(int sum, int opponents_card) override;
};

class ge17_card : public card_strategy{
  public:
    state virtual make_choice(deck deck_state, card opponents_card) override;
};


#endif // STRATEGY_H
