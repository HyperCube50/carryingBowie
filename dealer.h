#pragma once
#include <vector>

#include "card.h"

namespace Dealer {
    extern int test;
    extern std::vector<Card> hiddenCards;
    extern std::vector<Card> revealedCards;

    extern void RevealCard();
    extern int GetHandValue();
    extern void WriteHand();
};