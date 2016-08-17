// deck.cpp
// Brian Shin

// Deck class - can represent any number of cards as "deck" - full or hand, subdeck


#include "deck.h"
#include<iostream>
#include<algorithm>
#include<random>
#include<chrono>
#include<math.h>

Deck::Deck() {
  for(int suit = 0; suit <= 3; ++suit) {
    for(int rank = 1; rank <= NUM_RANKS; ++rank) {
      //std::cout << rank << " " << suit << std::endl;
      //Card next(Rank(rank),Suit(suit));
      //next.print();  
      cards.push_back(Card(Rank(rank),Suit(suit)));
    }
  }
  for(int i=0;i<NUM_RANKS;++i) ranks[i] = 0;
  for(auto &iter : cards) {
    ++ranks[iter.getRank()];
  }
  

}

Deck::~Deck() {}

Deck::Deck(int numCards) {
  for(int i=0;i<NUM_RANKS;++i) ranks[i] = 0;
}

void Deck::print() const {
  for(auto iter : cards) {
    iter.print();
  }
  std::cout << std::endl;
  //print_ranks();
}

void Deck::print_ranks() const {
  std::cout << "Ranks: " << std::endl;
  for(int i=0;i<NUM_RANKS;++i) {
    std::cout << i + 1 << ": " << ranks[i] << std::endl;
  }
  std::cout << std::endl;
}

void Deck::print(unsigned low, unsigned high) const {
  if (high > cards.size() || low > cards.size()) {
    throw std::invalid_argument("Invalid range of deck to print.");
  }
  else {
    for(int i=low;i<=high;++i) {
      cards[i].print();
    }
  }
}

void Deck::shuffle() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(cards.begin(),cards.end(), std::default_random_engine(seed));
}

void Deck::clear() {
  cards.clear();
  for(int i=0;i<NUM_RANKS;++i) ranks[i] = 0;
}

Card Deck::at(int index) const{
  if (index < 0 || index >= cards.size()) {
    throw std::invalid_argument("Deck index out of bounds.");
  }
  return cards.at(index);
}

Card Deck::draw() {
  Card result = cards.back();
  --ranks[result.getRank()-1];
  cards.pop_back();
  return result;
}

Deck Deck::subDeck(int numCards) {
  Deck sub = Deck(numCards);
  for(int i=0;i<numCards;++i) {
    sub.cards.push_back(draw());
  }
  for(auto &iter : cards) {
    ++ranks[iter.getRank()-1];
  }
  return sub;
}

void Deck::setDeck(const Deck& deck) {
  cards = deck.cards;
  for(auto &iter : cards) {
    ++ranks[iter.getRank()-1];
  }
}

void Deck::addCard(const Card& card) {
  cards.push_back(card);
  ++ranks[card.getRank()-1];
}

bool Deck::isEmpty() const{
  return cards.empty();
}

int Deck::size() const {
  return cards.size();
}

int Deck::valueHand() {
  // check for empty hand (fold)
  if (isEmpty()) {
    return 0;
  }
  int result = isStraightFlush();
  if (result != -1) {
    return result;    
  }
  result = is4s();
  if (result != -1) {
    return result;
  }
  result = isFullHouse();
  if (result != -1) {
    return result;
  }
  result = hasFlush();
  if (result != -1) {
    return result;
  }
  result = hasStraight();
  if (result != -1) {
    return result;
  }
  result = isSet();
  if (result != -1) {
    return result;
  }
  result = isTwoPair();
  if (result != -1) {
    return result;
  }
  result = isPair();
  if (result != -1) {
    return result;
  }
  return valueHighCard();

}


int Deck::isStraightFlush() {
  if (cards.size() < 5) {
    return -1;
  }
  else {
    sortBySuit();
    int index = 0;
    while (index < size() - 4) {
      if (hasFlush() != -1) {
        Deck temp = Deck(5);
        for(int i=index;i<index+5;++i) {
          temp.addCard(cards.at(i));
        }
        int result = temp.hasStraight();
        if (result != -1) return result - STRAIGHT + STRAIGHT_FLUSH;
        //temp.sortByRank();
        //if (temp.hasStraight()) {
        //  return true;
        //}
      }
      ++index;
    }

    return -1; 
  }
}

int Deck::hasFlush() {
  if (cards.size() < 5) {
    return -1;
  }
  else {
    sortBySuit();
    //print();
    //std::cout << size() << std::endl;
    int index=0;
    while (index < cards.size()-4) {
      //std::cout << at(index).getSuit();
      //std::cout << at(index+4).getSuit();
      int result = isFlush(index);
      if (result != -1) return result + FLUSH;
      ++index;
    }
    return -1;

  }
}

// check a deck for flush starting at index given deck sorted by suit 
int Deck::isFlush(int index) {
  if (index+4 >= cards.size()) {
    std::cout << "Flush check: index out of bounds." << std::endl;
    return -1;
  }
  sortBySuit();
  // five card hand contains a flush, find highest value card
  if (cards.at(index).getSuit() == cards.at(index+4).getSuit()) {
    Card max_rank = cards.at(index);
    for(int i=index+1;i<=index+4;++i) {
      if (cards.at(i) > max_rank) max_rank = cards.at(i);
    }
    return valueCard(max_rank.getRank());
  }
  return -1;
 
}

// check deck (not necessarily five cards) for a five card straight starting at index given deck sorted by rank
int Deck::hasStraight() {
  if (cards.size() < 5) {
    std::cout << "Need at least five cards in deck." << std::endl;
    return -1;
  }
  sortByRank();
  //print();

  int current_count;

  // check for Ace low straight
  if (cards.at(0).getRank() == ACE && cards.at(cards.size()-1).getRank() == TWO) {
    int i = cards.size() - 2;
    Rank current = THREE;
    current_count = 2;
    
    while (i > 0) {
      if (cards.at(i).getRank() == Rank(current-1)) {
        --i;
        continue;
      }
      else if (cards.at(i).getRank() != current) {
        break;
      }
      --i;
      current = Rank(current + 1);
      if (++current_count == 5) return STRAIGHT + ACE_VALUE;
    }
  }

  // check for all other straights
  int j =0;
  while (j < cards.size() - 4) {
    //std::cout << "test. j = " << j << std::endl;
    current_count = 1;
    Rank current;
    if (cards.at(j).getRank() == ACE) {
      current = KING;
    }
    else {
      current = Rank(cards.at(j).getRank() - 1);
    }
    int i = j+1;
    while(i<cards.size()) {
      //std::cout << "Test rank: " << current << std::endl;
      //std::cout << "Current card: " << cards.at(i).getRank() << std::endl;
      if (cards.at(i).getRank() == Rank(current+1) || (cards.at(i).getRank() == ACE && 
        current == KING)) {
        ++i;
        continue;
      }
      else if (cards.at(i).getRank() != current) {
        j = i - 1;
        break;
      }
      current = Rank(current - 1);
      ++i;
      ++current_count;
      if (current_count == 5) {
        // return value of highest card
        return STRAIGHT + current + 5;
      }
    }
    ++j;
  }

  return -1;
}

int Deck::is4s() {
  /*
  sortByRank();
  return (cards.at(0).getRank() == cards.at(3).getRank()) || 
          (cards.at(1).getRank() == cards.at(4).getRank()) || 
          (cards.at(2).getRank() == cards.at(5).getRank()) || 
          (cards.at(3).getRank() == cards.at(6).getRank()); 
  */
  for(int i=0;i<NUM_RANKS;++i) {
    if (ranks[i] == 4) {
      return valueCard(i+1) + FOUR_OF_A_KIND;
    }
  }
  return -1;
}

int Deck::isFullHouse() {
  if (cards.size() < 5) {
    std::cout << "Need at least five cards in deck." << std::endl;
    return -1;
  }
  if (is4s() != -1) return -1;
  if (hasSet() != -1) {
    for(int i=0;i<NUM_RANKS;++i) {
      if (ranks[i] == 2) return hasSet() + FULL_HOUSE;
    }
  }
  return -1;
  
}

// check if deck has a set as highest rated hand
int Deck::isSet() {
  int result = hasSet();
  if (result != -1 && isFullHouse() == -1) {
    return result + SET;
  }  
  return -1;
  /*
  sortByRank();
  int index = 0;
  while (index < cards.size() - 2) {
    if (cards.at(index).getRank() == cards.at(index+2).getRank()) return index; 
    ++index;
  }
  return -1;
  */
}

// check if  deck contains at least one set (can be two in seven card hand)
// return value of highest set in hand if any, -1 otherwise
int Deck::hasSet() {
  if (cards.size() < 5) {
    std::cout << "Need at least five cards in deck." << std::endl;
    return -1;
  }
  // set of Aces
  if (ranks[0] == 3) {
    return valueCard(1);
  }
  for(int i=12;i>=1;--i) {
    if (ranks[i] == 3) return i+1; 
  }
  return -1;
  //return (hasSet() != -1 && !isFullHouse() && !is4s());
}

// check if there are at least two pairs in deck (can be three in seven card hand)
int Deck::isTwoPair() {
  if (cards.size() < 5) {
    std::cout << "Need at least five cards in deck." << std::endl;
    return -1;
  }
  if (isSet() != -1) {
    return -1;
  }
  int num_pairs = 0;
  int high_pair = -1;
  int low_pair = -1;
  int high_card = -1;
  // check for Ace pair first
  if (ranks[0] == 2) {
    high_pair = 1;
    num_pairs++;
  }
  else if (ranks[0] == 1) {
    high_card = ACE_VALUE;
  }
  for(int i=NUM_RANKS-1;i>0;--i) {
    if (ranks[i] == 2) {
      if (high_pair == -1) high_pair = i+1; 
      else if (i + 1 > low_pair) {
        low_pair = i+1;
      }
      num_pairs++;
    }
    else if (ranks[i] == 1 && i+1 > high_card) {
      high_card = i+1;
    }
  }
  //std::cout << "High pair: " << high_pair << " Low pair: " << low_pair  << " High card: " << high_card << std::endl;
  if (num_pairs >= 2) return high_pair * pow(14,4) + low_pair * pow(14,2) + high_card; 
  return -1;
}

// check if there is exactly one pair in deck
int Deck::isPair() {
  if (isTwoPair() != -1) {
    return -1;
  }
  int num_pairs = 0;
  int pair_value = -1;
  int high_card = -1;
  int mid_card = -1;
  int low_card = -1;
  if (ranks[0] == 2) {
    num_pairs++;
    pair_value = ACE_VALUE;
  }
  else if (ranks[0] == 1) {
    high_card = ACE_VALUE;
  }
  for(int i=NUM_RANKS-1;i>0;--i) {
    if (ranks[i] == 2) {
      num_pairs++;
      pair_value = i + 1;
    }
    else if (ranks[i] == 1) {
      if (high_card != -1) {
        if (mid_card != -1) {
          low_card = i + 1;
        }
        else mid_card = i + 1;
      }
      else high_card = i+1;
    }
  }
  
  if (num_pairs == 1) {
    return pair_value * pow(14,3) + high_card * pow(14,2) + mid_card * 14 + low_card;
  }
  return -1;
  
}

int Deck::valueHighCard() {
  if (ranks[0] == 1) return ACE_VALUE;
  for(int i=NUM_RANKS-1;i>0;--i) {
    if(ranks[i] == 1) return i + 1;
  }
}

void Deck::sortByRank() {
  std::sort(cards.begin(),cards.end());
  std::reverse(cards.begin(),cards.end()); 
}

void Deck::sortBySuit() {
  std::sort(cards.begin(),cards.end(),greaterSuit);
}

int Deck::valueCard(int rank) const{
  if (rank == 1) return ACE_VALUE;
  else return rank;
}


