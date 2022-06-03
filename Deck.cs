using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blackjack
{
    public class Deck
    {
        private List<Card> cards;

        /// Initilize on creation of Deck.
        public Deck()
        {
            Initialize();
        }


        /// Returns a Fresh Deck-- a deck organized by Suit and Face.
        public List<Card> GetFreshDeck()
        {
            List<Card> freshDeck = new List<Card>();

            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    freshDeck.Add(new Card((Suit)j, (Face)i));
                }
            }

            return freshDeck;
        }


        /// Remove top 2 cards of Deck and turn it into a list.
        public List<Card> DealHand()
        {
            // Create a temporary list of cards and give it the top two cards of the deck.
            List<Card> hand = new List<Card>();
            hand.Add(cards[0]);
            hand.Add(cards[1]);

            // Remove the cards added to the hand.
            cards.RemoveRange(0, 2);

            return hand;
        }

        /// Pick top card and remove it from the deck
        /// Return The top card of the deck
        public Card DrawCard()
        {
            Card card = cards[0];
            cards.Remove(card);

            return card;
        }


        /// Randomize the order of the cards in the Deck.
        public void Shuffle()
        {
            Random rng = new Random();

            int n = cards.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                Card RandomCard = cards[k];
                cards[k] = cards[n];
                cards[n] = RandomCard;
            }
        }

        /// Replace the deck with a Fresh Deck and then Shuffle it.
        public void Initialize()
        {
            cards = GetFreshDeck();
            Shuffle();
        }
    }
}