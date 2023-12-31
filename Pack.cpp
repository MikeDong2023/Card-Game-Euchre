#include "Pack.hpp" 

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack():next(0) {
    int i = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
       for (int r = NINE; r <= ACE; ++r) {
        cards[i] = Card(static_cast<Rank>(r), static_cast<Suit>(s));
        ++i;
       } 
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) : next(0){
   for (int i = 0; i < PACK_SIZE; ++i) {
    Card card;
    pack_input >> card;
    cards[i] = card;
   }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card topCard = cards[next];
    ++next;
    return topCard;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
   
    int count = 1;
    while(count <= 7) {
        std::array<Card, PACK_SIZE> temp;
        int mid = PACK_SIZE / 2;
        int left = 0;
        int right = mid;

        for (int i = 0; i < PACK_SIZE; ++i) {
            if (i % 2 == 0) {
                temp[i] = cards[right];
                ++right;
            } else {
                temp[i] = cards[left];
                ++left;
            }
        }
        cards = temp;
        ++count;
    }
    
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    return next >= PACK_SIZE;
}