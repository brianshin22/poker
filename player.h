#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "deck.h"

class Player {
  int id;
  Deck hand;
  long amount;
  
  public:
    Player(int num, long money);
    int getId() const;
    bool bet(long amount);
    bool addAmount(long amount);
    void fold();
    long getAmount() const;
    void setHand(const Deck& cards);
    Deck getHand() const;
    void printHand() const;
    void printAmount() const;
};

#endif
