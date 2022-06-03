#include "card.h"

Card::Card(Suit s, Face f) {
    suit = s;
    face = f;

    switch (face) {
        case Ace:
            value = 11;
            break;
        case King:
            value = 10;
            break;
        case Queen:
            value = 10;
            break;
        case Jack:
            value = 10;
            break;
        case Ten:
            value = 10;
            break;
        default:
            value = face;
            break;
    }
}

void Card::WriteDescription() {
    std::string suitName;

    switch (suit) {
        case Clubs:
            suitName = "clubs";
            break;
        case Spades:
            suitName = "spades";
            break;
        case Diamonds:
            suitName = "diamonds";
            break;
        case Hearts:
            suitName = "clubs";
            break;
    }

    if (face == Ace)
    {
        if (value == 11)
        {
            std::cout << "--> " << " Soft " << face << " of " << suitName << "" << "\n";
        }
        else
        {
            std::cout << "--> " << " Hard " << face << " of " << suitName << "" << "\n";
        }
    }
    else
    {
        std::cout << "--> " << " " << face << " of " << suitName << "" << "\n";
    }
}