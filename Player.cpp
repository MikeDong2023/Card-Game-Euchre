#include "Player.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

class SimplePlayer : public Player {
  private: 
    std::string name;
    //playerCards is the hand
    std::vector<Card> playerCards;
  public :
    SimplePlayer(const std::string name) : name(name) {}

    const std::string & get_name() const override {
      return name;
    }

    /*void printCards() override{
      for (int i = 0; i < playerCards.size(); ++i){
        std::cout << playerCards[i] << std::endl;
      }
    }*/

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
      playerCards.push_back(c);
    };

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round, 
    Suit &order_up_suit) const override {
      if (round == 1){
        Suit proposedTrump = upcard.get_suit();
        //checking player's hand for right and left bowers, 
        //and Q, K, A of the trump suit
        int goodCardsCount = 0;
        for (int i = 0; i < playerCards.size(); ++i) {
          if ((playerCards[i].is_face_or_ace() == true && 
          playerCards[i].is_trump(proposedTrump))) {
            ++goodCardsCount;
          }
        }
        //decide based on the amount of good cards and upcard if player should order up
        if ((goodCardsCount >= 2)
        ) {
          order_up_suit = upcard.get_suit();
          return true;
        } else {
          return false;
        }
      } else {
        Suit sameColorSuit;
        if (upcard.get_suit() == SPADES) {
          sameColorSuit = CLUBS;
        } else if (upcard.get_suit() == CLUBS) {
          sameColorSuit = SPADES;
        } else if (upcard.get_suit() == HEARTS) {
          sameColorSuit = DIAMONDS;
        } else {
          sameColorSuit = HEARTS;
        }
        //checking player's hand for right and left bowers, 
        //and Q, K, A of the trump suit
        int goodCardsCount = 0;
        for (int i = 0; i < playerCards.size(); ++i) {
          if ((playerCards[i].is_face_or_ace() == true && 
          playerCards[i].is_trump(sameColorSuit))) {
            ++goodCardsCount;
          }
        }
        //decide based on count and if is dealer
        if (((goodCardsCount >= 1) && !is_dealer) || is_dealer){
          order_up_suit = sameColorSuit;
          return true;
        } else {
          return false;
        }   
      }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
      playerCards.push_back(upcard);
      int iOfLow = 0;
      for (int i = 1; i < playerCards.size(); ++i) {
        if (Card_less(playerCards[i], playerCards[iOfLow], upcard.get_suit())) {
          iOfLow = i;
        }
      }
      playerCards.erase(playerCards.begin() + iOfLow);
    }

    bool justTrumps(std::vector<Card> hand, Suit trump) {
      for(int i = 0; i < playerCards.size(); ++i) {
        if(!playerCards[i].is_trump(trump)) {return false;}
      }
      return true;
    }
    //REQUIRES Player has at least one nontrump
    //EFFECTS returns the highest nontrump and erases it from their hand
    Card highestNonTrump(std::vector<Card> &hand, Suit trump) {
      assert(!justTrumps(hand, trump));
      int maxNonTrumpInd = 0;
      bool nonTrumpFound = false;
      //Set highestNonTrump to first nontrump
      while(maxNonTrumpInd < hand.size() && !nonTrumpFound) {
        nonTrumpFound = !hand[maxNonTrumpInd].is_trump(trump);
        ++maxNonTrumpInd;
      }
      maxNonTrumpInd = maxNonTrumpInd - 1;
      //Find highest nontrump
      for(int i = 0; i < hand.size(); ++i) {
        if(!hand[i].is_trump(trump) && Card_less(hand[maxNonTrumpInd], hand[i], trump)) {
          maxNonTrumpInd = i;
        }
      }
      Card highestNonTrump = hand[maxNonTrumpInd];
      hand.erase(hand.begin() + maxNonTrumpInd);
      return highestNonTrump;
    }
    //REQUIRES player has at least 1 card
    //EFFECTS returns the highest card and erases it from the player's hand
    Card highestCard(std::vector<Card> &hand, Suit trump) {
      int maxIndex = 0;
      for(int i = 0; i < hand.size(); ++i) {
        if(Card_less(hand[maxIndex], hand[i], trump)) {maxIndex = i;}
      }
      Card highest = hand[maxIndex];
      hand.erase(hand.begin() + maxIndex);
      return highest;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override {
      assert(playerCards.size() > 0);
      bool onlyTrump = justTrumps(playerCards, trump);

      if (!onlyTrump) {
        return highestNonTrump(playerCards, trump);
      } else {
        return highestCard(playerCards, trump);
      }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
      assert(playerCards.size() > 0);
      Suit ledSuit = led_card.get_suit(trump);
      Card inSuitHigh = Card(TWO, ledSuit);
      Card notSuitLow = Card(JACK, trump);
      bool hasLedSuit = false;
      int indexInSuitHigh = 0;
      int indexNotSuitLow = 0;
      
      
      for (int i = 0; i < playerCards.size(); ++i) {
        if (playerCards[i].get_suit(trump) == ledSuit) {
          hasLedSuit = true;
          if (Card_less(inSuitHigh, playerCards[i], led_card, trump)) {
            inSuitHigh = playerCards[i];
            indexInSuitHigh = i;
          }
        } else {
          if (Card_less(playerCards[i], notSuitLow, led_card, trump)) {
            notSuitLow = playerCards[i];
            indexNotSuitLow = i;
          }
        }
      }
      if (hasLedSuit) {
         playerCards.erase(playerCards.begin() + indexInSuitHigh);
         //std::cout << indexInSuitHigh << std::endl;
         return inSuitHigh;
      } else {
         playerCards.erase(playerCards.begin() + indexNotSuitLow);
         //std::cout << indexNotSuitLow << std::endl;
         return notSuitLow;
      }
    }
};

class HumanPlayer : public Player {
  private:
    std::string name;

    std::vector<Card> playerCards;

    void print_hand() const {
      for (size_t i=0; i < playerCards.size(); ++i)
        std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << playerCards[i] << "\n";
    }

  public:
    HumanPlayer(const std::string name) : name(name) {}

    const std::string & get_name() const override {
      return name;
    }

    /*void printCards() override{
      for (int i = 0; i < playerCards.size(); ++i){
        std::cout << playerCards[i] << std::endl;
      }
    }*/

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
      playerCards.push_back(c);
      std::sort(playerCards.begin(), playerCards.end());
    };

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round, 
    Suit &order_up_suit) const override {
      print_hand();
      std::cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
      
      std::string decision;
      std::cin >> decision;
      if (decision != "pass") {
        Suit ordered_up = string_to_suit(decision);
        order_up_suit = ordered_up;
        return true;
      }
      else {
        return false;
      }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
      std::sort(playerCards.begin(), playerCards.end());
      print_hand();
      std::cout << "Discard upcard: [-1]\n";
      std::cout << "Human player " << name << ", please select a card to discard:\n";
      
      int decision;
      std::cin >> decision;
      playerCards.erase(playerCards.begin() + decision);
      playerCards.push_back(upcard);
      //std::cout << std::endl;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override {
      std::sort(playerCards.begin(), playerCards.end());
      print_hand();
      std::cout << "Human player " << name << ", please select a card:\n";
      int decision;
      std::cin >> decision;
      Card chosen = playerCards[decision];
      playerCards.erase(playerCards.begin() + decision);
      return chosen;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
      std::sort(playerCards.begin(), playerCards.end());
      print_hand();
      std::cout << "Human player " << name << ", please select a card:\n";
      int decision;
      std::cin >> decision;
      Card chosen = playerCards[decision];
      playerCards.erase(playerCards.begin() + decision);
      return chosen;
  }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.


  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }

  // Invalid strategy if we get here
  assert(strategy != "Human" && strategy != "Simple");
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
	
