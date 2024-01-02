#include <memory>
#include <iostream>
#include <random>
#include "card.h"
#include "choose_table.h"
#include "game_config.h"
#include "factory_initializator.h"

#ifndef STRATEGY_H
#define STRATEGY_H

template <typename CardType, typename DeckType>
class Strategy{
  public:
    Strategy(std::string given_name = "unstated"):name_{given_name} {}
    std::string GetName();
    State virtual MakeChoice(DeckType& sum, CardType& opponents_card) = 0;
    virtual ~Strategy(){}
    std::unique_ptr<Strategy> Clone() const;
  protected:
    void ChangeState(State& old_state, State new_state);
    void ChangeMaxScore(int& old_max_score, int new_max_score);
    virtual Strategy* CloneImpl() const = 0;
    std::string name_;
};

class G16Plain : public Strategy<int, int>{
  public:
    G16Plain();
    State MakeChoice(int& sum, int& opponents_card) override;
    G16Plain* CloneImpl() const override;
};

class G18Plain : public Strategy<int, int>{
  public:
    G18Plain();
    State MakeChoice(int& sum, int& opponents_card) override;
    G18Plain* CloneImpl() const override;
};

class TablePlainStrategy: public Strategy<int, int>{
  public:
    TablePlainStrategy();
    State MakeChoice(int& sum, int& opponents_card) override;
    TablePlainStrategy* CloneImpl() const override;
    static void SetTablePath(std::string path);
  private:
    static ChooseTable table_;
};

//inline ChooseTable TablePlainStrategy::table_ = ChooseTable("./main/plusi/22203_kovalev/lab_2/int_table.json");
inline ChooseTable TablePlainStrategy::table_ = ChooseTable("/home/beekebak/main/plusi/22203_kovalev/lab_2/int_table.json");

class CowardPlain : public Strategy<int, int>{
  public:
    CowardPlain();
    State MakeChoice(int& sum, int& opponents_card) override;
    CowardPlain* CloneImpl() const override;
};

class RandomPlainStrategy: public Strategy<int, int>{
public:
    RandomPlainStrategy();
    RandomPlainStrategy(const RandomPlainStrategy& other);
    ~RandomPlainStrategy() = default;
    State MakeChoice(int& sum, int& opponents_card) override;
    RandomPlainStrategy* CloneImpl() const override;
private:
    class RandomException{};
    std::mt19937 rng_;
    std::unique_ptr<Strategy<int,int>> actual_strategy_ = std::unique_ptr<Strategy<int,int>>(new G18Plain);
};

class G17Card : public Strategy<Card, Deck>{
  public:
    G17Card();
    State MakeChoice(Deck& deck_state, Card& opponents_card) override;
    G17Card* CloneImpl() const override;
};

class CowardCard : public Strategy<Card, Deck>{
public:
    CowardCard();
    State MakeChoice(Deck& deck_state, Card& opponents_card) override;
    CowardCard* CloneImpl() const override;
};


class TableCardStrategy: public Strategy<Card, Deck>{
public:
    TableCardStrategy();
    State MakeChoice(Deck& sum, Card& opponents_card) override;
    TableCardStrategy* CloneImpl() const override;
    static void SetTablePath(std::string path);
private:
    static ChooseTable table_;
};


//inline ChooseTable TableCardStrategy<CardType>::table_ = ChooseTable("./main/plusi/22203_kovalev/lab_2/card_table.json");
inline ChooseTable TableCardStrategy::table_ = ChooseTable("/home/beekebak/main/plusi/22203_kovalev/lab_2/card_table.json");


class RandomCardStrategy: public Strategy<Card, Deck>{
public:
    RandomCardStrategy();
    RandomCardStrategy(const RandomCardStrategy& other);
    ~RandomCardStrategy() = default;
    State MakeChoice(Deck& sum, Card& opponents_card) override;
    RandomCardStrategy* CloneImpl() const override;
private:
    class RandomException{};
    std::mt19937 rng_;
    std::unique_ptr<Strategy<Card, Deck>> actual_strategy_ = std::unique_ptr<Strategy<Card, Deck>>(new G17Card);
};

#endif // STRATEGY_H
