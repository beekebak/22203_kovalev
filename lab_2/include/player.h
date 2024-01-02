#include <vector>
#include <random>
#include <memory>
#include <stdexcept>
#include "card.h"
#include "strategy.h"

#ifndef PLAYER_H
#define PLAYER_H

template<typename CardType, typename DeckType>
class Player;

template<typename CardType>
class Player<CardType, Deck>{
  public:
    Player(Strategy<CardType, Deck>* strategy);
    Player() = default;
    Player(Player& other) = default;
    Player(Player&&) = default;
    ~Player() = default;
    int ShowScore();
    std::string GetStrategyName();
    int GetFirstCardScore();
    int GetLastCardScore();
    enum State PlayNextMove(CardType opponent_card);
    void RecieveCard(CardType card);
  private:
    std::shared_ptr<Strategy<CardType, Deck>> strategy_;
    std::vector<CardType> players_deck_;
    Deck state_;
};

template<>
class Player<int, int>{
public:
    Player(Strategy<int, int>* strategy);
    Player() = default;
    Player(const Player& other) = default;
    Player(Player&&) = default;
    ~Player() = default;
    int ShowScore();
    std::string GetStrategyName();
    int GetFirstCardScore();
    int GetLastCardScore();
    enum State PlayNextMove(int opponent_card);
    void RecieveCard(int card);
private:
    std::shared_ptr<Strategy<int, int>> strategy_;
    std::vector<int> players_deck_;
    int state_ = 0;
};
#endif // PLAYER_H
