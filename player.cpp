// player.cpp
// Brian Shin


#include "player.h"
#include<stdexcept>
#include<iostream>

Player::Player(int num, long money) {
  id = num;
  amount = money;
  hand.clear();
}

int Player::getId() const{
  return id;
}

bool Player::bet(long money) {
  if (money > amount) {
    //throw std::invalid_argument("Not enough money");
    std::cout << "Player " << getId() << " does not have enough money to bet $" << money << ". Try again." << std::endl;
    return false;
  }
  else {
    amount -= money;
    //std::cout << "Successfully bet $" << money <<  ", left with $" << amount << std::endl;
    return true;
  }

}

bool Player::addAmount(long money) {
  amount += money;
  return true;
}

void Player::fold() {
  hand.clear();
}

long Player::getAmount() const{
  return amount;
}

Deck Player::getHand() const{
  return hand;
}

void Player::setHand(const Deck& sub_deck) {
  hand.setDeck(sub_deck);
}

void Player::printHand() const{
  if(hand.isEmpty()) {
    std::cout << "Empty hand." << std::endl;
    std::cout << std::endl;
  }
  else {
    hand.print();
  }
}

void Player::printAmount() const{
  std::cout << "$" << amount << std::endl;
}


