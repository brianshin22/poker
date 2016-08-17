#ifndef DECK_INCLUDED
#define DECK_INCLUDED

#include "card.h"
#include<vector>
   
class Deck {
  static const int ACE_VALUE = 14;
  static const int NUM_RANKS = 13; // number of different ranks of a card deck
  static const int NCARDS = 52;
  static const int STRAIGHT_FLUSH =  8000000; // + valueHighCard(straight_flush)
  static const int FOUR_OF_A_KIND =  7000000; // + quads card rank
  static const int FULL_HOUSE     =  6000000; // + set card rank
  static const int FLUSH          =  5000000; // + valueHighCard(flush)
  static const int STRAIGHT       =  4000000; // + valueHighCard(straight)
  static const int SET            =  3000000; // + set card rank
  static const int TWO_PAIR       =  2000000; // + high2 * 14^4 + low2 * 14^3 + card
  static const int PAIR           =  1000000; // + high * 14^2 + high2 * 14 + low               

  std::vector<Card> cards;
  int ranks[13];
  
  public:
    Deck();
    ~Deck();
    Deck(int numCards);
    void print() const;
    void print(unsigned low, unsigned high) const;
    void shuffle();
    void clear();
    Card at(int index) const;
    Card draw();
    Deck subDeck(int numCards);
    void setDeck(const Deck& deck);
    void addCard(const Card& Card);
    bool isEmpty() const;
    int size() const;
    int valueHand();
    void sortByRank();
    void sortBySuit();
  
  //private:

    int isStraightFlush();
    int is4s();
    int isFullHouse();
    int hasFlush();
    int isFlush(int index);
    int hasStraight();
    int isSet();
    int hasSet(); // returns position of set
    int isTwoPair();
    int isPair();
    int valueHighCard();
    int valueCard(int rank) const;

  private:
    void print_ranks() const;
    


};


#endif
