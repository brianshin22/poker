// card.cpp
// Brian Shin

// card class using enums, Ace high

#include "card.h"
#include<iostream>

Card::Card(Rank r, Suit s) {
  suit = s;
  rank = r;
}

void Card::print() const{
  std::string s;
  std::string r;
  switch(suit) {
    case CLUBS:     s = "Clubs";break;
    case DIAMONDS:  s = "Diamonds";break;
    case HEARTS:    s = "Hearts";break;
    case SPADES:    s = "Spades";break;
    default:        s = "Not a valid suit"; 
  }

  switch(rank) {
    case Rank::ACE:       r = "Ace";break;
    case Rank::TWO:       r = "Two";break;
    case Rank::THREE:     r = "Three";break;
    case Rank::FOUR:      r = "Four";break;
    case Rank::FIVE:      r = "Five";break;
    case Rank::SIX:       r = "Six";break;
    case Rank::SEVEN:     r = "Seven";break;
    case Rank::EIGHT:     r = "Eight";break;
    case Rank::NINE:      r = "Nine";break;
    case Rank::TEN:       r = "Ten";break;
    case Rank::JACK:      r = "Jack";break;
    case Rank::QUEEN:     r = "Queen";break;
    case Rank::KING:      r = "King";break;
    default:              r = "Not a valid rank";
  }

  std::cout << r << " of " << s << std::endl;

}

Rank Card::getRank() const {
  return rank;
}

Suit Card::getSuit() const {
  return suit;
}


