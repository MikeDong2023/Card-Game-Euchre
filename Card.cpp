#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}



//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////
Card::Card() : rank(TWO), suit(SPADES) {};

Card::Card(Rank rank_in, Suit suit_in) : rank(rank_in), suit(suit_in) {};

Rank Card::get_rank() const {
  return rank;
};

Suit Card::get_suit() const {
  return suit;
};

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
Suit Card::get_suit(Suit trump) const {
  if (is_left_bower(trump)) {
    return trump;
  }
  return suit;
};

bool Card::is_face_or_ace() const {
  return get_rank() >= JACK;
}

//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(Suit trump) const {
  return get_rank() == JACK && get_suit() == trump;
};

//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(Suit trump) const {
  return get_rank() == JACK && Suit_next(get_suit()) == trump;
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(Suit trump) const {
  return get_suit(trump) == trump;
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit) {
  Suit nextSuit;
  switch(suit) {
    case HEARTS:
    nextSuit = DIAMONDS;
    break;

    case DIAMONDS:
    nextSuit = HEARTS;
    break;

    case SPADES:
    nextSuit = CLUBS;
    break;

    default:
    nextSuit = SPADES;
  }
  return nextSuit;
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump) {
  Suit suitA = a.get_suit(trump);
  Suit suitB = b.get_suit(trump);
  Rank rankA = a.get_rank();
  Rank rankB = b.get_rank();

  //if neither are trump, use < operator
  if(suitA != trump && suitB != trump) {
    return a < b;
  }
  //if trump then trump wins
  if (suitA == trump && suitB != trump) {
    return false;
  }
  if (suitB == trump && suitA != trump) {
    return true;
  } 
  //when both trump, JACK wins
  if (rankA == JACK && rankB != JACK) {
    return false;
  }
  if (rankB == JACK && rankA != JACK) {
    return true;
  }
  //When both trump and not jack, higher rank wins 
  if (rankA != JACK && rankB != JACK) {
    return rankA < rankB;
  }
  //if both trump and both jack, right bower wins 
  return b.is_right_bower(trump);
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
// Check if one of them is left or right bower
if (a.is_right_bower(trump)){
  return false;
}
if (b.is_right_bower(trump)){
  return true;
}
if (a.is_left_bower(trump)) {
  return false;
} 
if (b.is_left_bower(trump)) {
  return true;
}

// Check is one of them is trump suit; if both, which is bigger
if (a.get_suit() == trump && b.get_suit() != trump) {
  return false;
} else if (a.get_suit() != trump && b.get_suit() == trump) {
  return true;
} else if (a.get_suit() == trump && b.get_suit() == trump) {
  if (a.get_rank() < b.get_rank()) {
    return true;
  } else {
    return false;
  }
}

// Check if one of them is led suit; if both, which is bigger
if (a.get_suit() == led_card.get_suit(trump) && 
b.get_suit() != led_card.get_suit(trump)) {
  return false;
} else if (a.get_suit() != led_card.get_suit(trump) && 
b.get_suit() == led_card.get_suit(trump)) {
  return true;
} else if (a.get_suit() == led_card.get_suit(trump) && 
b.get_suit() == led_card.get_suit(trump)) {
  if (a.get_rank() < b.get_rank()) {
    return true;
  } else {
    return false;
  }
}
// Check which one is bigger normally
if (a.get_rank() < b.get_rank()) {
  return true;
}
/*if (a.get_rank() > b.get_rank()) {
  return false;
}*/
if (a.get_rank() == b.get_rank()) {
  if (a.get_suit() < b.get_suit()) {
    return true;
  }
  if (a.get_suit() > b.get_suit()) {
    return false;
  }
}
  return false;
}
//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream& is, Card& card) {
    is >> card.rank;
    std::string temp;
    is >> temp; // Read and discard "of" string
    is >> card.suit;
    return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank < rhsRank || (lhsRank == rhsRank && lhsSuit < rhsSuit);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank < rhsRank || (lhsRank == rhsRank && lhsSuit <= rhsSuit);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank > rhsRank || (lhsRank == rhsRank && lhsSuit > rhsSuit);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank > rhsRank || (lhsRank == rhsRank && lhsSuit >= rhsSuit);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank == rhsRank && lhsSuit == rhsSuit;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
  Rank lhsRank = lhs.get_rank();
  Rank rhsRank = rhs.get_rank();
  Suit lhsSuit = lhs.get_suit();
  Suit rhsSuit = rhs.get_suit();

  return lhsRank != rhsRank || lhsSuit != rhsSuit;
}