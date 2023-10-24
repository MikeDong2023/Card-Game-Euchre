#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>

using namespace std;

class Game {
 public:
  
  Game(int ptsTWin, vector<Player*> players, istream& inputFileStream, 
  bool shuffleStatus) 
    : ptsToWin(ptsTWin), players(players), pack(inputFileStream), 
    shuffleStatus(shuffleStatus){};

  void play() {
    while (!teamWin[0] && !teamWin[1]) {
        // Step one: shuffle
        shuffleOrReset(shuffleStatus);
        // Step two: deal
        dealer = players[dealerIndex]->get_name();
        deal();
        /*for (int i = 0; i < players.size(); ++i) {
            cout << players[i]->get_name() << endl;
            players[i]->printCards();
        }*/
        cout << "Hand " << handCount << '\n';
        cout << dealer << " deals" << endl;
        cout << upcard << " turned up"<< endl;
        // Step three: make trump
        make_trump(upcard, dealer, 1, order_up_suit);
        trump = order_up_suit;
        // Step four: play tricks
        play_hand(trump);
        // Step five: count score
        count_score();
        cout << players[0]->get_name() << " and " << players[2]->get_name() << 
        " have " << teamPts[0] << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name() << 
        " have " << teamPts[1] << " points" << endl;
        cout << endl;
        // Reset trackers tracking this round's infos
        teamOrderUp[0] = false;
        teamOrderUp[1] = false;
        march = false;
        euchred = false;
        handWinner[0] = false;
        handWinner[1] = false;
        dealerIndex = (dealerIndex + 1) % 4;
        trickCounts[0] = 0;
        trickCounts[1] = 0;
        ++handCount;
    }
    if (teamWin[0]) {
        cout << players[0]->get_name() << " and " << players[2]->get_name() 
        << " win!" << endl;
    } else {
        cout << players[1]->get_name() << " and " << players[3]->get_name() 
        << " win!" << endl;
    }
    
  };

 private:
  int ptsToWin;
  vector<Player*> players;
  Pack pack;
  bool shuffleStatus;
  string dealer = "";
  int dealerIndex = 0;
  Card upcard = Card();
  Suit order_up_suit = SPADES;
  Suit trump = SPADES;
  int trickCounts[2] = {0, 0};
  bool teamOrderUp[2] = {false, false};
  int teamPts[2] = {0, 0};
  bool march = false;
  bool euchred = false;
  bool teamWin[2] = {false, false};
  bool handWinner[2] = {false, false};
  int handCount = 0;
  // ...

  //Shuffles or resets based on the value of shuffleStatus
  void shuffleOrReset(bool shuffleStatus) {
    if(shuffleStatus) {
        pack.shuffle();
    }
    else {
        reset();
    }
  }
  void deal() {
    alternatingDeal(3, 2);
    alternatingDeal(2, 3);
    upcard = pack.deal_one();
  };
  /* Deals evenDeal cards to every player in Team 1
   * and oddDeal cards to every player in Team 2.
   */
  void alternatingDeal(int evenDeal, int oddDeal) {
    int currentPlayerIndex = (dealerIndex + 1) % 4;
    for(int i = 1; i <= 2; ++i) {
        deal(players[currentPlayerIndex], evenDeal);
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        deal(players[currentPlayerIndex], oddDeal);  
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
    }
  }
  //Deals numDealt cards to p.
  void deal(Player *p, int numDealt) {
    for(int i = 0; i < numDealt; ++i) {p->add_card(pack.deal_one());}
  }

  void make_trump(const Card &upcard, string dealer,
  int round, Suit &order_up_suit) {
    bool is_dealer = false;
    bool isTrumpMade = false;
    int cont = 0;

    int decider = (dealerIndex + 1) % 4;

    /*while(!isTrumpMade && round <= 2) {
        while (!isTrumpMade && cont < 4) {
            // Determine if is dealer
            is_dealer = dealer == players[decider]->get_name();
            // Making trump
            if (players[decider]->make_trump(upcard, is_dealer, round, 
            order_up_suit)) {
                isTrumpMade = true;
                // Check which team is it that ordered up
                teamOrderUp[decider % 2] = true;
                cout << players[decider]->get_name() << " orders up " << order_up_suit 
                << endl;
                if (round == 1) {
                    players[dealerIndex]->add_and_discard(upcard);
                }
                cout << endl;
                
            } else {
                cout << players[decider]->get_name() << " passes";
                cout << endl;
            }
            decider = (decider + 1) % 4;
            ++cont;
        }
        cont = 0;
        decider = (dealerIndex + 1) % 4;
        ++round;
    }*/
        while (!isTrumpMade && (round == 1) && cont < 4) {
            // Determine if is dealer
            is_dealer = dealer == players[decider]->get_name();
            // Making trump
            if (players[decider]->make_trump(upcard, is_dealer, round, 
            order_up_suit)) {
                isTrumpMade = true;
                // Check which team is it that ordered up
                teamOrderUp[decider % 2] = true;
                cout << players[decider]->get_name() << " orders up " << order_up_suit 
                << endl;
                players[dealerIndex]->add_and_discard(upcard);
                cout << endl;
                
            } else {
                cout << players[decider]->get_name() << " passes";
                cout << endl;
            }
            decider = (decider + 1) % 4;
            ++cont;
        }
        if (!isTrumpMade) {
            round = 2;
        }
        cont = 0;
        decider = (dealerIndex + 1) % 4;
        while (!isTrumpMade && (round == 2) && cont < 4) {
            // Determine if is dealer
            is_dealer = dealer == players[decider]->get_name();
            // Making trump
            if (players[decider]->make_trump(upcard, is_dealer, round, 
            order_up_suit)) {
                isTrumpMade = true;
                // Check which team is it that ordered up
                teamOrderUp[decider % 2] = true;
                cout << players[decider]->get_name() << " orders up " << order_up_suit 
                << endl;
                //players[dealerIndex]->add_and_discard(upcard);
                cout << endl;
                
            } else {
                cout << players[decider]->get_name() << " passes";
                cout << endl;
            }
            decider = (decider + 1) % 4;
            ++cont;
        }
    }
    
  //}
    void play_hand(Suit trump) {
        //Set up first lead player
        int leadPlayer = (dealerIndex + 1) % players.size();
        for(int i = 0; i < 5; ++i) {
            leadPlayer = play_trick(leadPlayer);
        }
    }
    //Plays a trick and returns the index of the trick winner
    int play_trick(int leadPlayer) {
        int currentPlayer = (leadPlayer + 1) % players.size();
        int trickWinner = leadPlayer;
        // Play lead
        Card leadCard = players[leadPlayer]->lead_card(trump);
        Card highCard = leadCard;
        //Print lead card
        cout << leadCard << " led by " << players[leadPlayer]->get_name() << endl;
        //Plays following lead
        for (int j = 0; j < players.size() - 1; ++j) {
            Card currentCard = players[currentPlayer]->play_card(leadCard, trump);
            // Print current card
            cout << currentCard << " played by " << 
            players[currentPlayer]->get_name() << endl;
            if (Card_less(highCard, currentCard, leadCard, trump)) {
                trickWinner = currentPlayer;
                highCard = currentCard;
            }
            currentPlayer = (currentPlayer + 1) % players.size();
        }
        ++trickCounts[trickWinner % 2];
        cout << players[trickWinner]->get_name() << " takes the trick" << endl;
        cout << endl;
        return trickWinner;
    }
    void reset() {
        pack.reset();
    }
    void count_score() {

        if (teamOrderUp[0] && (trickCounts[0] == 3 || trickCounts[0] == 4)) {
            ++teamPts[0];
            handWinner[0] = true;
        } 
        else if (teamOrderUp[1] && (trickCounts[1] == 3 || trickCounts[1] == 4)) {
            ++teamPts[1];
            handWinner[1] = true;
        } 
        else if (teamOrderUp[0] && trickCounts[0] == 5) {
            teamPts[0] += 2;
            march = true;
            handWinner[0] = true;
        } else if (teamOrderUp[1] && trickCounts[1] == 5) {
            teamPts[1] += 2;
            march = true;
            handWinner[1] = true;
        } else if (!teamOrderUp[0] && 3 <= trickCounts[0] && trickCounts[0] <= 5){
            teamPts[0] += 2;
            euchred = true;
            handWinner[0] = true;
        } else if (!teamOrderUp[1] && 3 <= trickCounts[1] && trickCounts[1] <= 5){
            teamPts[1] += 2;
            euchred = true;
            handWinner[1] = true;
        }
        teamWin[0] = teamPts[0] >= ptsToWin;
        teamWin[1] = !teamWin[0] && teamPts[1] >= ptsToWin;

        if (handWinner[0]) {
            cout << players[0]->get_name() << " and " << players[2]->get_name() << 
            " win the hand" << endl;
        } else {
            cout << players[1]->get_name() << " and " << players[3]->get_name() << 
            " win the hand" << endl; 
        }

        if (march) {
            cout << "march!" << endl;
        }
        if (euchred) {
            cout << "euchred!" << endl;
        }
    }

};


int main(int argc, char **argv) {
  // Read command line args and check for errors
    string packFileName = argv[1];
    string shuffleType = argv[2];
    ifstream inputFileStream(packFileName);
    bool shuffleStatus = shuffleType == "shuffle";
    int ptsToWin = stoi(argv[3]);
    vector<Player*> players;
    for (int i = 0; i < 4; ++i) {
        players.push_back(Player_factory(argv[4 + i * 2], argv[5 + i * 2]));
    };
    string type1 = argv[5];
    string type2 = argv[7];
    string type3 = argv[9];
    string type4 = argv[11];
  // Check for command line argument errors
    if (!(argc == 12 &&
    0 <= ptsToWin &&
    ptsToWin <= 100 &&
    (shuffleType == "shuffle" || shuffleType == "noshuffle") &&
    (type1 == "Human" || type1 == "Simple") &&
    (type2 == "Human" || type2 == "Simple") &&
    (type3 == "Human" || type3 == "Simple") &&
    (type4 == "Human" || type4 == "Simple"))) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return -69;
    }
  // Check for file opening errors
    if (!(inputFileStream.is_open())) {
        cout << "Error opening " <<  packFileName << endl;
        return -70;
    }
    // Print the command line arguments
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << "\n";
    Game game(ptsToWin, players, inputFileStream, shuffleStatus);
    game.play();
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}
