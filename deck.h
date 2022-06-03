#pragma once
#include <vector>
#include <random>
#include <algorithm>

#include "card.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();

    std::vector<Card> GetFreshDeck();

    std::vector<Card> DealHand();

    Card DrawCard();

    void Shuffle();

    void Initialize();
};