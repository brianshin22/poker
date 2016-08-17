// main.cpp
// Brian Shin

// runner file for poker game
// can run with ./poker or with four arguments specifying number of 
// human players, total number of players, buy in, and small blind

#include "poker.h"
#include<iostream>

void testCard();
void testDeck();
void testPlayer();
void testHand();
void testPoker();

int main(int argc, char* argv[]) {
  
  if (argc == 1) {
    //testPoker();
    Poker game = Poker();
  }
  else if (argc == 5) {
    // num human players, total number of players, buy in, small blind
    Poker game = Poker(std::stoi(argv[1]),std::stoi(argv[2]),std::stol(argv[3]),std::stol(argv[4]));
  }
  else {
    std::cout << "Wrong number of parameters." << std::endl;
    exit(0);
  }
  
  //testPoker();
  //testHand();
  //testDeck();
  return 0;
}

void testPoker() {
  Poker game = Poker(2);
  std::cout << "Exited successfully." << std::endl;
}

void testHand() {
  Deck hand = Deck(7);
  hand.addCard(Card(ACE,DIAMONDS));
  hand.addCard(Card(FOUR,CLUBS));
  hand.addCard(Card(SIX,SPADES));
  hand.addCard(Card(SIX,CLUBS));
  hand.addCard(Card(KING,CLUBS));
  hand.addCard(Card(KING,SPADES));
  hand.addCard(Card(FOUR,DIAMONDS));
  hand.print();
  //std::cout << hand.size() << std::endl;

  std::cout << "Hand value: " << hand.valueHand() << std::endl;

  std::cout << "Straight flush score: " << hand.isStraightFlush() << std::endl;
  std::cout << "Four of a kind score: " << hand.is4s() << std::endl;
  std::cout << "Full house score: " << hand.isFullHouse() << std::endl;
  std::cout << "Flush score: " << hand.hasFlush() << std::endl;
  std::cout << "Straight score: " << hand.hasStraight() << std::endl;
  std::cout << "Set score: " << hand.isSet() << std::endl;
  std::cout << "Two pair score: " << hand.isTwoPair() << std::endl;
  std::cout << "One pair score: " << hand.isPair() << std::endl;
}

void testPlayer() {
  Deck deck = Deck();
  long money = 100000;
  Player a = Player(0,money);
  deck.shuffle();
  Deck hand1 = deck.subDeck(2);
  a.setHand(hand1);
  std::cout << "Player 1's hand: " << std::endl;
  a.printHand();
  Deck table = deck.subDeck(5);
  

  //std::cout << "Remaining deck: ";
  //deck.print();
  table.print();
  std::cout << "Flop: "<<std::endl;
  table.print(0,2);
  std::cout << "Turn: "<<std::endl;;
  table.print(3,3);
  std::cout << "River: "<<std::endl;
  table.print(4,4);
  
  //table.sortByRank();
  //table.print();    

/*
  std::cout << std::endl;
  a.printAmount();
  a.bet(1000);
  a.printAmount();
  a.addAmount(200001);
  a.printAmount();

*/
  
    

}

void testDeck() {

  Deck deck = Deck();
  deck.print();
  std::cout << std::endl;
  deck.shuffle();
  deck.print();
  //std::cout << std::endl;
  
  Card first = deck.draw();
  first.print();
  std::cout<<std::endl;
  deck.print();
  Deck hand = deck.subDeck(5);
  hand.print();
  hand.shuffle();
  hand.print();
  hand.sortByRank();
  hand.print();
  hand.sortBySuit();
  hand.print();
  
  for(int i=4;i>=0;--i) {
    hand.at(i).print();
  }

  //deck.print();
  
}

void testCard() {

  Card card = Card(KING,SPADES);
  card.print();
  Card card2(KING,CLUBS);
  card2.print();
  Card card3 = Card(ACE,SPADES);
  Card card4 = Card(NINE,CLUBS);
  
  Rank rank = ACE;
  Suit suit = CLUBS;
  std::cout << rank << " " << suit << std::endl;
  Card card5 = Card(rank,suit);
  rank = Rank(rank+1);
  suit = Suit(suit+1);
  Card card6 = Card(rank,suit);


  card5.print();
  card6.print();
  
  bool t1 = card > card2;
  bool t2 = card > card4;
  bool t3 = card2 > card3;

  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  std::cout << t3 << std::endl;
}
