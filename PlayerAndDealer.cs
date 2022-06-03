using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blackjack
{

    public class Player
    {
        public int Chips { get; set; } = 100;
        public int Bet { get; set; }
        public int Wins { get; set; }
        public int HandsCompleted { get; set; } = 1;

        public List<Card> Hand { get; set; }


        /// Add Player's chips to their bet.
        public void AddBet(int bet)
        {
            Bet += bet;
            Chips -= bet;
        }

        /// Set Bet to 0
        public void ClearBet()
        {
            Bet = 0;
        }

        /// Cancel player's bet (in case of PUSH) . They will neither lose nor gain any chips.
        public void ReturnBet()
        {
            Chips += Bet;
            ClearBet();
        }


        /// Give player chips that they won from their bet.
        /// If player won with blackjack, 
        /// player wins 1.5 times + their bet on top 
        public int WinBet(bool blackjack)
        {
            int chipsWon;
            if (blackjack)
            {
                chipsWon = (int)Math.Floor(Bet + Bet * 1.5);
            }
            else
            {
                chipsWon = Bet * 2;
            }

            Chips += chipsWon;
            ClearBet();
            return chipsWon;
        }

       
        /// Value of all cards in Hand
        public int GetHandValue()
        {
            int value = 0;
            foreach (Card card in Hand)
            {
                value += card.Value;
            }
            return value;
        }

       
        /// Write player's hand to console.
        public void WriteHand()
        {
        
            Console.Write("Bet: ");
   
            Console.Write(Bet + "  ");
            Console.Write("Chips: ");
      
            Console.Write(Chips + "  ");
            Console.Write("Wins: ");
     
            Console.WriteLine(Wins);
            Console.WriteLine("Round #" + HandsCompleted);

            Console.WriteLine();
            Console.WriteLine("+++++ Your Hand has a value of: " + GetHandValue() + " points. +++++");
            foreach (Card card in Hand)
            {
                card.WriteDescription();
            }
            Console.WriteLine();
        }
    }

    public class Dealer
    {
        public static List<Card> HiddenCards { get; set; } = new List<Card>();
        public static List<Card> RevealedCards { get; set; } = new List<Card>();

        /// Take the top card from HiddenCards, remove it, and add it to RevealedCards.
        public static void RevealCard()
        {
            RevealedCards.Add(HiddenCards[0]);
            HiddenCards.RemoveAt(0);
        }

        /// Value of all cards in RevealedCards
        public static int GetHandValue()
        {
            int value = 0;
            foreach (Card card in RevealedCards)
            {
                value += card.Value;
            }
            return value;
        }


        /// Write Dealer's RevealedCards to Console.
        public static void WriteHand()
        {
            Console.WriteLine("+++++ Dealer's Hand has a value of: " + GetHandValue() + " points. +++++");
            foreach (Card card in RevealedCards)
            {
                card.WriteDescription();
            }
            for (int i = 0; i < HiddenCards.Count; i++)
            {
                Console.WriteLine("  <Second dealer Card is Hidden, for now>");
            }
            Console.WriteLine();
        }
    }
}

