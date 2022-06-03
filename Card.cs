using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using static Blackjack.Suit;
using static Blackjack.Face;

namespace Blackjack
{
    public enum Suit
    {
        Clubs,
        Spades,
        Diamonds,
        Hearts
    }
    public enum Face
    {
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
    }

    public class Card
    {
        public Suit Suit { get; }
        public Face Face { get; }
        public int Value { get; set; }

        /// Assign Value 
        public Card(Suit suit, Face face)
        {
            Suit = suit;
            Face = face;

           
            switch (Face)
            {
                case Ace:
                    Value = 11;
                    break;
                case King:
                    Value = 10;
                    break;
                case Queen:
                    Value = 10;
                    break;
                case Jack:
                    Value = 10;
                    break;
                case Ten:
                    Value = 10;
                    break;
                case Nine:
                    Value = 9;
                    break;
                case Eight:
                    Value = 8;
                    break;
                case Seven:
                    Value = 7;
                    break;
                case Six:
                    Value = 6;
                    break;
                case Five:
                    Value = 5;
                    break;
                case Four:
                    Value = 4;
                    break;
                case Three:
                    Value = 3;
                    break;
                case Two:
                    Value = 2;
                    break;
            }
        }


        /// Print out the description of the card, marking Aces as Soft or Hard.
        public void WriteDescription()
        {
          
            if (Face == Ace)
            {
                if (Value == 11)
                {
                    Console.WriteLine("--> " + " Soft " + Face + " of " + Suit + "");
                }
                else
                {
                    Console.WriteLine("--> " + " Hard " + Face + " of " + Suit + "");
                }
            }
            else
            {
                Console.WriteLine("--> " + " " + Face + " of " + Suit + "");
            }
        }
    }
}