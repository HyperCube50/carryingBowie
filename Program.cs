
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using Blackjack;

namespace Blackjack
{
    public class Program
    {
        private static Deck deck = new Deck();
        private static Player player = new Player();
        public static int MinimumBet { get; } = 10;

        private enum RoundResult
        {
            ItIsATie,
            PlayerWin,
            PlayerLoose,
            BlackJack,
            DealerWin,
            InvalidBet
        }

        /// <summary>
        /// Initialize Deck, deal the player and dealer hands, and display them.
        /// </summary>
        static void InitializeHands()
        {
            deck.Initialize();

            player.Hand = deck.DealHand();
            Dealer.HiddenCards = deck.DealHand();
            Dealer.RevealedCards = new List<Card>();

            // If hand contains two aces, make one Hard.
            if (player.Hand[0].Face == Face.Ace && player.Hand[1].Face == Face.Ace)
            {
                player.Hand[1].Value = 1;
            }

            if (Dealer.HiddenCards[0].Face == Face.Ace && Dealer.HiddenCards[1].Face == Face.Ace)
            {
                Dealer.HiddenCards[1].Value = 1;
            }

            Dealer.RevealCard();

            player.WriteHand();
            Dealer.WriteHand();
        }

        /// Handles everything for the round.
        static void StartRound()
        {
            Console.Clear();

            if (!TakeBet())
            {
                EndRound(RoundResult.InvalidBet);
                return;
            }
            Console.Clear();

            InitializeHands();
            TakeActions();

            Dealer.RevealCard();

            Console.Clear();
            player.WriteHand();
            Dealer.WriteHand();

            player.HandsCompleted++;

            if (player.GetHandValue() > 21)
            {
                EndRound(RoundResult.PlayerLoose);
                return;
            }

            while (Dealer.GetHandValue() <= 16)
            {
                Thread.Sleep(1000);
                Dealer.RevealedCards.Add(deck.DrawCard());

                Console.Clear();
                player.WriteHand();
                Dealer.WriteHand();
            }


            if (player.GetHandValue() > Dealer.GetHandValue())
            {
                player.Wins++;

                if (IsHandBlackjack(player.Hand))
                {
                    EndRound(RoundResult.BlackJack);
                }
                else
                {
                    EndRound(RoundResult.PlayerWin);
                }
            }
            else if (Dealer.GetHandValue() > 21)
            {
                player.Wins++;
                EndRound(RoundResult.PlayerWin);
            }
            else if (Dealer.GetHandValue() > player.GetHandValue())
            {
                EndRound(RoundResult.DealerWin);
            }
            else
            {
                EndRound(RoundResult.ItIsATie);   //Push
            }
        }

        /// Returns true if the hand is blackjack
        public static bool IsHandBlackjack(List<Card> hand)
        {
            if (hand.Count == 2)
            {
                if (hand[0].Face == Face.Ace && hand[1].Value == 10) return true;
                else if (hand[1].Face == Face.Ace && hand[0].Value == 10) return true;
            }
            return false;
        }


        /// Ask user for action and perform that action until they stand or bust.
        static void TakeActions()
        {
            string action;
            do
            {
                Console.Clear();
                player.WriteHand();
                Dealer.WriteHand();

                Console.WriteLine("(H) for 'Hit', (S) for 'Stand'; Select 'Q' to 'Quit' the Program: ");
                action = Console.ReadLine();
                switch (action.ToUpper())
                {
                    case "Q":
                        System.Environment.Exit(0);
                        break;

                    case "H":
                        player.Hand.Add(deck.DrawCard());
                        break;
                    case "S":
                        break;

                    default:
                        Console.WriteLine("Invalid moves...  Please select from:");
                        Console.WriteLine("(H) for 'Hit', (S) for 'Stand'; Select 'Q' to 'Exit' the Program: ");
                        Console.WriteLine("Press any key to continue.");
                        Console.ReadKey();
                        break;
                }

                if (player.GetHandValue() > 21)
                {
                    foreach (Card card in player.Hand)
                    {
                        if (card.Value == 11) // Only a soft ace can have a value of 11
                        {
                            card.Value = 1;
                            break;
                        }
                    }
                }
            } while (!action.ToUpper().Equals("S") && player.GetHandValue() <= 21);
        }


        /// Take player's bet
        /// Check if the bet is valid
        static bool TakeBet()
        {
            Console.Write("Blackjack Game Underway...\n\n");
            Console.Write("Player Chip Count: ");
            Console.WriteLine(player.Chips);

            Console.Write("Minimum Bet: ");
            Console.WriteLine(MinimumBet);

            Console.Write("Enter bet to begin your hand #" + player.HandsCompleted + ": ");
            string s = Console.ReadLine();

            if (Int32.TryParse(s, out int bet) && bet >= MinimumBet && player.Chips >= bet)
            {
                player.AddBet(bet);
                return true;
            }
            return false;
        }

        /// Perform action based on result of round and start next round.
        static void EndRound(RoundResult result)
        {
            switch (result)
            {
                case RoundResult.ItIsATie:
                    player.ReturnBet();
                    Console.WriteLine("Player and Dealer in a Tie (Push).");
                    break;
                case RoundResult.PlayerWin:
                    Console.WriteLine("Player Wins " + player.WinBet(false) + " chips");
                    break;
                case RoundResult.PlayerLoose:
                    player.ClearBet();
                    Console.WriteLine("Player Busts");
                    break;
                case RoundResult.BlackJack:
                    Console.WriteLine("Player Wins " + player.WinBet(true) + " chips with Blackjack.");
                    break;
                case RoundResult.DealerWin:
                    player.ClearBet();
                    Console.WriteLine("Dealer Wins.");
                    break;

                case RoundResult.InvalidBet:
                    Console.WriteLine("Invalid Bet.");
                    break;
            }

            if (player.Chips <= 0)
            {
                Console.WriteLine();
                Console.WriteLine("You ran out of Chips after " + (player.HandsCompleted - 1) + " rounds.");
                Console.WriteLine("A new set of Chips will be added and your play counter is reset....  Pay dealer another $100 to resume your gambling habit!");

                player = new Player();
            }


            Console.WriteLine("Press any key to continue");
            Console.ReadKey();
            StartRound();
        }

        static void Main(string[] arg)
        {
            Console.WriteLine("\n***** Welcome to IBW-B High Casino - Blackjack Game ***** \n");
            Thread.Sleep(1000);
            Console.WriteLine("Pay $100 to the dealer to buy your starting chips, \nand Press any key other than 'Q' to play. \n");
            Console.WriteLine("Select  'Q' to quit. \n");

            Thread.Sleep(1000);
            string selection;
            selection = Console.ReadLine();
            switch (selection.ToUpper())
            {
                case "Q":
                    System.Environment.Exit(0);
                    break;

                default:
                    StartRound();
                    break;
            }
        }

    }
}

