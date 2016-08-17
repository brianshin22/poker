// poker.cpp
// Brian Shin

// Poker game class for Texas Holdem

#include "poker.h"
#include<iostream>
#include<stdexcept>
#define MAX_PLAYERS 9


// Can initialize with number of players, the buy in amount, and starting blinds.
Poker::Poker(int human_players, int total_players, long buy_in, long small_blind) {
  // limit total number of players to 9
  if (total_players > MAX_PLAYERS) {
    std::cout << "Too many players." << std::endl;
    return;
  }

  // initialize players and give them uniue IDs
  humans = human_players;
  std::cout << "There are " << humans << " human players." <<std::endl;

  num_players = total_players;
  std::cout << "There are " << num_players << " total players." << std::endl;

  int current_humans = 0;
  for(int i=0;i<num_players;++i) {
    int id = 100 + i;
    players.push_back(Player(id,buy_in));
    if (current_humans < humans) {
      human_ids.push_back(id);
      current_humans++;
    }
  }
  pot = 0;
  small_blind = small_blind;
  table.clear();

  game_on = true;
  while (game_on) {
    playTurn();
    //playTurn();
    //game_on = false;
  }  

}

Poker::~Poker() {}

// play one turn
void Poker::playTurn() {

  printStatus();

  // check for valid players
  int i=0;
  std::vector<Player>::iterator it = players.begin();
  for(; it != players.end();) {
    if (it->getAmount() <= 0) {
      std::cout << "Player " << it->getId()<< " is out of money. Booting Player " << it->getId() << std::endl;
      players.erase(players.begin() + i);
    }
    else {
      ++it;
      ++i;
    }
  }

  if (players.size() <= 0) {
    std::cout << "Game is over." << std::endl;
    game_on = false;
    return;
  }
  else if (players.size() == 1) {
    std::cout << "No turn to play - Player " << players[0].getId() << " wins!" << std::endl;
    game_on = false;
    return;
  }

  // begin the turn
  else {
 
    deck = Deck();
    deck.shuffle();
    for(std::vector<Player>::iterator it = players.begin(); it != players.end();++it) {
      it->setHand(deck.subDeck(hand_size));
    }
    table = deck.subDeck(5);

    
    collectBets();

    /*
    int i=0;
    for(std::vector<Player>::iterator it = players.begin(); it != players.end();++it,++i) {
      std::cout << "Player " << i << ": $" << it->getAmount() << std::endl;
      it->printHand();
    }
    */

    printStatus();

    // print cards on the table (flop, turn, river)
    //std::cout << "Table:" << std::endl;
    //table.print();
    
    // vector position of winner of turn
    int winner = findWinner();

    std::cout << "Player " << players[winner].getId() << " wins. He/she wins $" << pot << std::endl;

    // pay out the pot
    payWinner(winner);
    //std::cout << "Player " << winner << " has $" << players[winner].getAmount() << std::endl;

    // clear players' hands
    for(std::vector<Player>::iterator it = players.begin(); it != players.end();++it) {
      it->fold();
    }
    table.clear();
    printStatus();
     
    std::cout << "Turn is over." << std::endl;
    std::cout << std::endl;


  }

}

// determine the worth of player's hand
int Poker::valueHand(const Player& player) {
  Deck temp = player.getHand();
  // player has folded
  if (temp.isEmpty()) {
    return 0;
  }
  for(int i=0;i<table.size();++i) {
    temp.addCard(table.at(i));
  }

  return temp.valueHand();
  
}

// print current state of game
void Poker::printStatus() const {
  std::cout << "Printing game status..." << std::endl;
  std::cout << "Pot: $" << pot << std::endl;
  std::cout << "Number of players: " << players.size() << std::endl;
  std::cout << std::endl;
  for(auto& it : players) {
    std::cout << "Player " << it.getId() << ": " << std::endl;
    it.printAmount();
    it.printHand();
    //std::cout << std::endl;
  }
  //std::cout << std::endl;
  std::cout << "Table: " << std::endl;
  table.print();

  //std::cout << std::endl;
}

// find the player with highest hand value
int Poker::findWinner() {
  int winner = 0;
  int i =0;
  for(const auto& it : players) {
    if (valueHand(it) > valueHand(players[winner])) {
      winner = i;
    }
    ++i;
  }
  return winner;
}

// pay winning player(s), clear pot
void Poker::payWinner(int winner) {
  if (!players[winner].addAmount(pot)) {
    std::cout << "Could not award pot to winner. Exiting." << std::endl;
    throw std::runtime_error("Possible overflow");
  }
  std::cout << "Added pot to Player " << players[winner].getId() << std::endl;
  pot = 0;  
}

// take money from players, add to pot
// will need to account for folds and convey this information
void Poker::collectBets() {
  std::cout << "Collecting bets from players." << std::endl;
  std::cout << std::endl;
  int i=0;
  
  std::vector<Player>::iterator p = players.begin();

  // collect from user input
  for(auto& it : human_ids) {
    long bet;
    char action;
    while (p->getId() != it && p!= players.end()) ++p;
    std::cout << "Player " << it << ": $" << p->getAmount() << std::endl;
    std::cout << "Press b to bet or f to fold." << std::endl;
    std::cin >> action;
    while (action != 'b' && action != 'f') {
      std::cout << "Invalid input. Try again." << std::endl;
      std::cin >> action;
    }
    if (action == 'b') {
      std::cout << "Enter amount to bet." << std::endl;
      std::cin >> bet;
      while (bet > p->getAmount()) {
        std::cout << "Bet is too high. Place a lower bet." << std::endl;
        std::cin >> bet;
      }
      std::cout << "Betting " << bet << std::endl;
      if (p->bet(bet)) {
        pot += bet;
      }
    }
    
    // user folds
    else {
      p->fold();
      std::cout << "Player " << p->getId() << " folds. " << std::endl;
    }
    ++p;

  }

  while(p != players.end()) {
    long money = 50000;//it.getAmount();
    if (p->getAmount() < money) {
      while(!p->bet(p->getAmount())){}
    }
    else {
      while(!p->bet(money)){}
    }
    pot += money;
    ++p;
    //it.printAmount();
    //++i;
  }
}
