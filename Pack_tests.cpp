#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}
TEST(test_stream_ctor) {
    const int deckSize = 3;
    istringstream s1("Four of Hearts\nTwo of Clubs\nAce of Spades");
    Card deck[deckSize] = {Card(FOUR, HEARTS), Card(TWO, CLUBS), Card(ACE, SPADES)};
    Pack p(s1);
    for(int i = 0; i < deckSize; ++i) {
        Card c = p.deal_one();
        ASSERT_EQUAL(deck[i].get_rank(), c.get_rank());
        ASSERT_EQUAL(deck[i].get_suit(), c.get_suit());
    }
}
// Add more tests here

TEST_MAIN()
