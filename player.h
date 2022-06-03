#pragma once
#include <vector>

#include "card.h"

class Player {
public:
    int Chips = 100;
    int Bet;
    int Wins;
    int HandsCompleted = 1;

    std::vector<Card> hand;

    void AddBet(int bet);

    void ClearBet();

    void ReturnBet();

    int WinBet(bool blackjack);

    int GetHandValue();

    void WriteHand();
};