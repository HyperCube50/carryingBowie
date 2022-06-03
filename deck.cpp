#include "deck.h"

Deck::Deck() {
    Initialize();
}


/// Returns a Fresh Deck-- a deck organized by Suit and Face.
std::vector<Card> Deck::GetFreshDeck() {
    std::vector<Card> freshDeck;

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            freshDeck.push_back(Card((Suit)j, (Face)i));
        }
    }

    return freshDeck;
}


/// Remove top 2 cards of Deck and turn it into a list.
std::vector<Card> Deck::DealHand() {
    // Create a temporary list of cards and give it the top two cards of the deck.
    std::vector<Card> hand;
    hand.push_back(cards[0]);
    hand.push_back(cards[1]);

    // Remove the cards added to the hand.
    cards.erase(cards.begin(), cards.begin() + 2);

    return hand;
}

/// Pick top card and remove it from the deck
/// Return The top card of the deck
Card Deck::DrawCard() {
    Card card = cards[0];
    cards.erase(cards.begin());

    return card;
}


/// Randomize the order of the cards in the Deck.
void Deck::Shuffle() {
    std::random_device rd;
    auto rng = std::default_random_engine{rd()};
    std::shuffle(cards.begin(), cards.end(), rng);
}

/// Replace the deck with a Fresh Deck and then Shuffle it.
void Deck::Initialize() {
    cards = GetFreshDeck();
    Shuffle();
}