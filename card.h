#pragma once
#include <iostream>

enum Suit {
    Clubs, Spades, Diamonds, Hearts
};

enum Face {
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

class Card {
public:
    Suit suit;
    Face face;
    int value;

    Card(Suit s, Face f);

    void WriteDescription();
};