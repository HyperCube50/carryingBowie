#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <boost/algorithm/string.hpp>

#include "card.h"
#include "deck.h"
#include "player.h"

Deck deck;
Player player;
int minimumBet = 10;

enum RoundResult {
    ItIsATie,
    PlayerWin,
    PlayerLoose,
    BlackJack,
    DealerWin,
    InvalidBet
};

class Dealer {
public:
    static std::vector<Card> hiddenCards;
    static std::vector<Card> revealedCards;

    /// Take the top card from HiddenCards, remove it, and add it to RevealedCards.
    static void RevealCard() {
        Dealer::revealedCards.push_back(Dealer::hiddenCards[0]);
        Dealer::hiddenCards.erase(Dealer::hiddenCards.begin());
    }

    /// Value of all cards in RevealedCards
    static int GetHandValue() {
        int value = 0;

        for (Card card : Dealer::revealedCards) {
            value += card.value;
        }

        return value;
    }


    /// Write Dealer's RevealedCards to Console.
    static void WriteHand() {
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
};

std::vector<Card> Dealer::hiddenCards = {};
std::vector<Card> Dealer::revealedCards = {};


void InitializeHands();

void EndRound();

bool TakeBet();
void TakeActions();
bool IsHandBlackjack();
void StartRound();

int main(int argc, char** argv) {
    std::cout << "\n***** Welcome to IBW-B High Casino - Blackjack Game ***** \n" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Pay $100 to the dealer to buy your starting chips, \nand Press any key other than 'Q' to play. \n" << "\n";
    std::cout << "Select  'Q' to quit. \n\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string selection;
    getline(std::cin, selection);

    if (boost::iequals(selection, "Q"))
        exit(0);
    else
        StartRound();
}

void InitializeHands() {
    deck.Initialize();

    player.hand = deck.DealHand();
    Dealer::hiddenCards = deck.DealHand();
    Dealer::revealedCards = std::vector<Card>();

    // If hand contains two aces, make one Hard.
    if (player.hand[0].face == Ace && player.hand[1].face == Ace)
    {
        player.hand[1].value = 1;
    }

    if (Dealer::hiddenCards[0].face == Ace && Dealer::hiddenCards[1].face == Ace)
    {
        Dealer::hiddenCards[1].value = 1;
    }

    Dealer::RevealCard();

    player.WriteHand();
    Dealer::WriteHand();
}

void EndRound(RoundResult result) {
    switch(result) {
        case ItIsATie:
            player.ReturnBet();
            std::cout << "Player and Dealer in a Tie (Push)." << "\n";
            break;
        case PlayerWin:
            std::cout << "Player Wins " << player.WinBet(false) << " chips" << "\n";
            break;
        case PlayerLoose:
            player.ClearBet();
            std::cout << "Player Busts" << "\n";
            break;
        case BlackJack:
            std::cout << "Player Wins " << player.WinBet(true) << " chips with Blackjack." << "\n";
            break;
        case DealerWin:
            player.ClearBet();
            std::cout << "Dealer Wins." << "\n";
            break;

        case InvalidBet:
            std::cout << "Invalid Bet." << "\n";
            break;
    }

    if (player.Chips <= 0) {
        std::cout << "\n";
        std::cout << "You ran out of Chips after " << (player.HandsCompleted - 1) << " rounds." << "\n";
        std::cout << "A new set of Chips will be added and your play counter is reset....  Pay dealer another $100 to resume your gambling habit!" << "\n";

        player = Player();
    }

    std::cout << "Press any key to continue" << "\n";
    std::cin.get();

    StartRound();
}

bool TakeBet() {
    std::cout << "Blackjack Game Underway...\n\n";
    std::cout << "Player Chip Count: ";
    std::cout << player.Chips << "\n";

    std::cout << "Minimum Bet: " << minimumBet << "\n";

    std::cout << "Enter bet to begin your hand #" << player.HandsCompleted << ": ";
    std::string s;
    getline(std::cin, s);

    int bet = std::stoi(s);

    if (bet >= minimumBet && player.Chips >= bet)
    {
        player.AddBet(bet);
        return true;
    }

    return false;
}

void TakeActions() {
    std::string action;

    do
    {
        std::cout << "\n" << "\n";
        player.WriteHand();
        Dealer::WriteHand();

        std::cout << "(H) for 'Hit', (S) for 'Stand'; Select 'Q' to 'Quit' the Program: " << "\n";
        getline(std::cin, action);
        std::cout << "\n";

        if (boost::iequals(action, "Q")) {
            exit(0);
        } else if (boost::iequals(action, "H")) {
            player.hand.push_back(deck.DrawCard());
        } else if (boost::iequals(action, "S")) {
        } else {
            std::cout << "Invalid moves...  Please select from:" << "\n";
            std::cout << "(H) for 'Hit', (S) for 'Stand'; Select 'Q' to 'Exit' the Program: " << "\n";
            std::cout << "Press any key to continue." << "\n";
            std::cin.get();
        }

        if (player.GetHandValue() > 21) {
            for (Card card : player.hand) {
                if (card.value == 11) {
                    card.value = 1;
                    break;
                }
            }
        }
    } while (!boost::iequals(action, "S") && player.GetHandValue() <= 21);
    
}

bool IsHandBlackjack(std::vector<Card> hand) {
    if (hand.size() == 2) {
        if (hand[0].face == Ace && hand[1].value == 10) return true;
        else if (hand[1].face == Ace && hand[0].value == 10) return true;
    }
    return false;
}

void StartRound() {
    std::cout << "\n" << "\n";

    if (!TakeBet()) {
        EndRound(InvalidBet);
        return;
    }
    std::cout << "\n" << "\n";

    InitializeHands();
    TakeActions();

    Dealer::RevealCard();

    std::cout << "\n" << "\n";
    player.WriteHand();
    Dealer::WriteHand();

    player.HandsCompleted++;

    if (player.GetHandValue() > 21) {
        EndRound(PlayerLoose);
        return;
    }

    while (Dealer::GetHandValue() <= 16) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Dealer::revealedCards.push_back(deck.DrawCard());
        
        std::cout << "\n" << "\n";
        player.WriteHand();
        Dealer::WriteHand();
    }

    if (player.GetHandValue() > Dealer::GetHandValue()) {
        player.Wins++;

        if (IsHandBlackjack(player.hand)) {
            EndRound(BlackJack);
        } else {
            EndRound(PlayerWin);
        }
    } else if (Dealer::GetHandValue() > 21) {
        player.Wins++;
        EndRound(PlayerWin);
    } else if (Dealer::GetHandValue() > player.GetHandValue()) {
        EndRound(DealerWin);
    } else {
        EndRound(ItIsATie);
    }
}