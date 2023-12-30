#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>
#include "match.h"

using namespace testing;

class MatchTest : public ::testing::Test {
public:
    Player<int,int> mockPlayerOne = Player<int,int>(new G16Plain());
    Player<int,int> mockPlayerTwo = Player<int,int>(new G16Plain());
    Dealer<int> mockDealer = Dealer<int>(52, 1);
    std::unique_ptr<SilentLogger<int,int>> mockLogger = std::unique_ptr<SilentLogger<int,int>>(new SilentLogger<int,int>);
};

TEST_F(MatchTest, FirstPlayerWinsByDefault) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kStop, State::kLose, 0, 0);
    EXPECT_EQ(result, MatchResult::kP1Win);
}

TEST_F(MatchTest, SecondPlayerWinsWhenFirstPlayerLoses) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kLose, State::kStop, 0, 0);
    EXPECT_EQ(result, MatchResult::kP2Win);
}

TEST_F(MatchTest, DrawWhenBothPlayersLose) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kLose, State::kLose, 0, 0);
    EXPECT_EQ(result, MatchResult::kDraw);
}

TEST_F(MatchTest, DrawWhenBothPlayersStopWithEqualScores) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kStop, State::kStop, 20, 20);
    EXPECT_EQ(result, MatchResult::kDraw);
}

TEST_F(MatchTest, FirstPlayerWinsWhenStoppingWithHigherScore) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kStop, State::kStop, 21, 20);
    EXPECT_EQ(result, MatchResult::kP1Win);
}

TEST_F(MatchTest, SecondPlayerWinsWhenStoppingWithHigherScore) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    MatchResult result = match.DetermineWinner(State::kStop, State::kStop, 19, 20);
    EXPECT_EQ(result, MatchResult::kP2Win);
}

TEST_F(MatchTest, ThrowsBadStateExceptionWhenFirstPlayerTakesMoreInTheEnd) {
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kAutomatic, 1, 2);
    EXPECT_ANY_THROW(match.DetermineWinner(State::kTakeMore, State::kStop, 0, 0));
}

TEST_F(MatchTest, ThrowsExceptionToEndGame){
    std::istringstream stream(std::string("quit"));
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kManual, 1, 2, stream);
    EXPECT_ANY_THROW(match.play());
}

TEST_F(MatchTest, NoThrowIfCorrectInput){
    std::istringstream stream(std::string("asdv"));
    Match<int, int> match(mockPlayerOne, mockPlayerTwo, mockDealer, std::move(mockLogger), MatchType::kManual, 1, 2, stream);
    EXPECT_NO_THROW(match.play());
}
