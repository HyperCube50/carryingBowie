#include "player.h"

/// Add Player's chips to their bet.
void Player::AddBet(int bet) {
    Bet += bet;
    Chips -= bet;
}

/// Set Bet to 0
void Player::ClearBet() {
    Bet = 0;
}

/// Cancel player's bet (in case of PUSH) . They will neither lose nor gain any chips.
void Player::ReturnBet() {
    Chips += Bet;
    ClearBet();
}


/// Give player chips that they won from their bet.
/// If player won with blackjack, 
/// player wins 1.5 times + their bet on top 
int Player::WinBet(bool blackjack) {
    int chipsWon;

    if (blackjack) {
        chipsWon = static_cast<int>(Bet + Bet * 1.5f);
    } else {
        chipsWon = Bet * 2;
    }

    Chips += chipsWon;
    ClearBet();

    return chipsWon;
}


/// Value of all cards in Hand
int Player::GetHandValue() {
    int value = 0;

    for(Card card : hand) {
        value += card.value;
    }

    return value;
}


/// Write player's hand to console.
void Player::WriteHand() {
    std::cout << "Bet: " << Bet << "  " << "Chips: " << Chips << "  " << "Wins: " << Wins << "\n";
    std::cout << "Round #" << HandsCompleted << "\n" << "\n";

    std::cout << "+++++ Your Hand has a value of: " << GetHandValue() << " points. +++++" << "\n";
    
    for (Card card : hand) {
        card.WriteDescription();
    }
    std::cout << "\n";
}