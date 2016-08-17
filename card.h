#ifndef __CARD__INCLUDED
#define __CARD_INCLUDE


enum Suit: int {CLUBS, DIAMONDS, HEARTS, SPADES};
enum Rank: int {ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
/*
Suit& operator++(Suit& s) {
  return s = Suit(static_cast<int>(s) + 1);
}
Rank& operator++(Rank& r) {
  return r = Rank(static_cast<int>(r) + 1);
}
*/

class Card {
  Rank rank;
  Suit suit;
  public:
    Card(Rank r, Suit s);
    Rank getRank() const;
    Suit getSuit() const;
    void print() const;
};

// Poker rules: Suit does not matter in comparing cards
inline bool operator==(const Card& c1, const Card& c2) {
  if (c1.getRank() == c2.getRank()) return true;
  else return false;
}

inline bool operator>(const Card& c1, const Card& c2) {
  if(c1 == c2) return false;
  else {
    Rank r1 = c1.getRank();
    Rank r2 = c2.getRank();
    if (r1 == Rank::ACE) {
      return true;
    }
    else if (r2 == Rank::ACE) {
      return false;
    }
    else {
      return r1 > r2;
    }
  }
}

inline bool operator<(const Card& c1, const Card& c2) {
  return !(c1 == c2) && !(c1 > c2);
}

inline bool greaterSuit(const Card& c1,const Card& c2) {
  return c1.getSuit() > c2.getSuit();
}

#endif
