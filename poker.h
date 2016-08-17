#ifndef POKER_INCLUDED
#define POKER_INCLUDED

#include "player.h"

class Poker {
  
  // Texas holdem poker
  const int hand_size = 2;
  int humans;
  int num_players;
  std::vector<Player> players;
  std::vector<int> human_ids;
  Deck deck;
  Deck table; // cards on the table (flop, turn, river)
  long pot;
  long small_blind;
  bool game_on;  

  public:
    Poker(int human_players = 0, int total_players=2, long buy_in=100000, long small_blind=100);
    ~Poker();
    void playTurn();
    int valueHand(const Player& player);
    void printStatus() const;
    
  private:
    int findWinner();
    void payWinner(int winner);
    void collectBets();
    
    
    

};


#endif
