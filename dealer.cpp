#include "dealer.h"

namespace Dealer {
    /// Take the top card from HiddenCards, remove it, and add it to RevealedCards.
    void RevealCard() {
        Dealer::revealedCards.push_back(Dealer::hiddenCards[0]);
        Dealer::hiddenCards.erase(Dealer::hiddenCards.begin());
    }

    /// Value of all cards in RevealedCards
    int GetHandValue() {
        int value = 0;

        for (Card card : Dealer::revealedCards) {
            value += card.value;
        }

        return value;
    }


    /// Write Dealer's RevealedCards to Console.
    void WriteHand() {
        std::cout << "+++++ Dealer's Hand has a value of: " << Dealer::GetHandValue() << " points. +++++" << "\n";
        
        for (Card card : Dealer::revealedCards)
        {
            card.WriteDescription();
        }

        for (int i = 0; i < Dealer::hiddenCards.size(); i++)
        {
            std::cout << "  <Second dealer Card is Hidden, for now>" << "\n";
        }

        std::cout << "\n";
    }
}