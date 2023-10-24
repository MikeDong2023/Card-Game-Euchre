#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    const int numCards = 5; 
    Rank rankArray[numCards] = {ACE, TEN, QUEEN, KING, JACK};
    Suit suitArray[numCards] = {HEARTS, SPADES, DIAMONDS, CLUBS, SPADES};

    for(int i = 0; i < numCards; ++i) {
        Card c(rankArray[i], suitArray[i]);
        ASSERT_EQUAL(rankArray[i], c.get_rank());
        ASSERT_EQUAL(suitArray[i], c.get_suit());
    }
}

TEST(test_default_constructor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_get_suit_trump_clubs) {
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);

    ASSERT_EQUAL(CLUBS, c1.get_suit(CLUBS));
    ASSERT_EQUAL(CLUBS, jackArray[0].get_suit(CLUBS));
    ASSERT_EQUAL(CLUBS, jackArray[3].get_suit(CLUBS));
    ASSERT_EQUAL(HEARTS, c2.get_suit(CLUBS));
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(CLUBS));
    ASSERT_EQUAL(SPADES, c4.get_suit(CLUBS));    
}
TEST(test_get_suit_trump_spades) {
Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_EQUAL(CLUBS, c1.get_suit(SPADES));
    ASSERT_EQUAL(SPADES, jackArray[3].get_suit(SPADES));
    ASSERT_EQUAL(SPADES, jackArray[0].get_suit(SPADES));
    ASSERT_EQUAL(HEARTS, c2.get_suit(SPADES));
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(SPADES));
    ASSERT_EQUAL(SPADES, c4.get_suit(SPADES));
}
TEST(test_get_suit_trump_diamonds) {
Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_EQUAL(CLUBS, c1.get_suit(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, jackArray[1].get_suit(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, jackArray[2].get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, c2.get_suit(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(DIAMONDS));
    ASSERT_EQUAL(SPADES, c4.get_suit(DIAMONDS));
}
TEST(test_get_suit_trump_hearts) {
Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_EQUAL(CLUBS, c1.get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, jackArray[1].get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, jackArray[2].get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, c2.get_suit(HEARTS));
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(HEARTS));
    ASSERT_EQUAL(SPADES, c4.get_suit(HEARTS));
}
TEST(test_face_or_ace) {
    Card aceArray[4] = {Card(ACE, CLUBS), Card(ACE, HEARTS),
                        Card(ACE, DIAMONDS), Card(ACE, SPADES)};
    Card kingArray[4] = {Card(KING, CLUBS), Card(KING, HEARTS),
                         Card(KING, DIAMONDS), Card(KING, SPADES)};
    Card queenArray[4] = {Card(QUEEN, CLUBS), Card(QUEEN, HEARTS), 
                        Card(QUEEN, DIAMONDS), Card(QUEEN, SPADES)};
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    const int numNonAceOrFace = 4;
    Card nonAceOrFace[numNonAceOrFace] = {Card(), Card(TEN, DIAMONDS),
                                         Card(FOUR, CLUBS), Card(FIVE, HEARTS)};
    for(int i = 0; i < 4; ++i) {
        ASSERT_TRUE(aceArray[i].is_face_or_ace());
        ASSERT_TRUE(kingArray[i].is_face_or_ace());
        ASSERT_TRUE(queenArray[i].is_face_or_ace());
        ASSERT_TRUE(jackArray[i].is_face_or_ace());
    }
    for(int i = 0; i < numNonAceOrFace; ++i) {
        ASSERT_FALSE(nonAceOrFace[i].is_face_or_ace());
    }
}

TEST(test_is_right_bower_clubs) {
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[0].is_right_bower(CLUBS));
    ASSERT_FALSE(jackArray[1].is_right_bower(CLUBS));
    ASSERT_FALSE(jackArray[2].is_right_bower(CLUBS));
    ASSERT_FALSE(jackArray[3].is_right_bower(CLUBS));
    ASSERT_FALSE(c1.is_right_bower(CLUBS));
    ASSERT_FALSE(c2.is_right_bower(CLUBS));
    ASSERT_FALSE(c3.is_right_bower(CLUBS));
    ASSERT_FALSE(c4.is_right_bower(CLUBS));
}
TEST(test_is_right_bower_spades) {
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[3].is_right_bower(SPADES));
    ASSERT_FALSE(jackArray[0].is_right_bower(SPADES));
    ASSERT_FALSE(jackArray[1].is_right_bower(SPADES));
    ASSERT_FALSE(jackArray[2].is_right_bower(SPADES));
    ASSERT_FALSE(c1.is_right_bower(SPADES));
    ASSERT_FALSE(c2.is_right_bower(SPADES));
    ASSERT_FALSE(c3.is_right_bower(SPADES));
    ASSERT_FALSE(c4.is_right_bower(SPADES));
}
TEST(test_is_right_bower_diamonds) {
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[2].is_right_bower(DIAMONDS));
    ASSERT_FALSE(jackArray[0].is_right_bower(DIAMONDS));
    ASSERT_FALSE(jackArray[1].is_right_bower(DIAMONDS));
    ASSERT_FALSE(jackArray[3].is_right_bower(DIAMONDS));
    ASSERT_FALSE(c1.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c2.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c3.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c4.is_right_bower(DIAMONDS));
}
TEST(test_is_right_bower_hearts) {
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[1].is_right_bower(HEARTS));
    ASSERT_FALSE(jackArray[0].is_right_bower(HEARTS));
    ASSERT_FALSE(jackArray[2].is_right_bower(HEARTS));
    ASSERT_FALSE(jackArray[3].is_right_bower(HEARTS));
    ASSERT_FALSE(c1.is_right_bower(HEARTS));
    ASSERT_FALSE(c2.is_right_bower(HEARTS));
    ASSERT_FALSE(c3.is_right_bower(HEARTS));
    ASSERT_FALSE(c4.is_right_bower(HEARTS));
}
TEST(test_is_left_bower_spades) {
    const Suit trump = SPADES;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[0].is_left_bower(trump));
    ASSERT_FALSE(jackArray[1].is_left_bower(trump));
    ASSERT_FALSE(jackArray[2].is_left_bower(trump));
    ASSERT_FALSE(jackArray[3].is_left_bower(trump));
    ASSERT_FALSE(c1.is_left_bower(trump));
    ASSERT_FALSE(c2.is_left_bower(trump));
    ASSERT_FALSE(c3.is_left_bower(trump));
    ASSERT_FALSE(c4.is_left_bower(trump));
}
TEST(test_is_left_bower_clubs) {
    const Suit trump = CLUBS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_FALSE(jackArray[0].is_left_bower(trump));
    ASSERT_FALSE(jackArray[1].is_left_bower(trump));
    ASSERT_FALSE(jackArray[2].is_left_bower(trump));
    ASSERT_TRUE(jackArray[3].is_left_bower(trump));
    ASSERT_FALSE(c1.is_left_bower(trump));
    ASSERT_FALSE(c2.is_left_bower(trump));
    ASSERT_FALSE(c3.is_left_bower(trump));
    ASSERT_FALSE(c4.is_left_bower(trump));
}
TEST(test_is_left_bower_diamonds) {
    const Suit trump = DIAMONDS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_FALSE(jackArray[0].is_left_bower(trump));
    ASSERT_TRUE(jackArray[1].is_left_bower(trump));
    ASSERT_FALSE(jackArray[2].is_left_bower(trump));
    ASSERT_FALSE(jackArray[3].is_left_bower(trump));
    ASSERT_FALSE(c1.is_left_bower(trump));
    ASSERT_FALSE(c2.is_left_bower(trump));
    ASSERT_FALSE(c3.is_left_bower(trump));
    ASSERT_FALSE(c4.is_left_bower(trump));
}
TEST(test_is_left_bower_hearts) {
    const Suit trump = HEARTS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_FALSE(jackArray[0].is_left_bower(trump));
    ASSERT_FALSE(jackArray[1].is_left_bower(trump));
    ASSERT_TRUE(jackArray[2].is_left_bower(trump));
    ASSERT_FALSE(jackArray[3].is_left_bower(trump));
    ASSERT_FALSE(c1.is_left_bower(trump));
    ASSERT_FALSE(c2.is_left_bower(trump));
    ASSERT_FALSE(c3.is_left_bower(trump));
    ASSERT_FALSE(c4.is_left_bower(trump));
}
TEST(test_is_trump_clubs) {
    const Suit trump = CLUBS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[0].is_trump(trump));
    ASSERT_FALSE(jackArray[1].is_trump(trump));
    ASSERT_FALSE(jackArray[2].is_trump(trump));
    ASSERT_TRUE(jackArray[3].is_trump(trump));
    ASSERT_TRUE(c1.is_trump(trump));
    ASSERT_FALSE(c2.is_trump(trump));
    ASSERT_FALSE(c3.is_trump(trump));
    ASSERT_FALSE(c4.is_trump(trump));
}
TEST(test_is_trump_spades) {
    const Suit trump = SPADES;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_TRUE(jackArray[0].is_trump(trump));
    ASSERT_FALSE(jackArray[1].is_trump(trump));
    ASSERT_FALSE(jackArray[2].is_trump(trump));
    ASSERT_TRUE(jackArray[3].is_trump(trump));
    ASSERT_FALSE(c1.is_trump(trump));
    ASSERT_FALSE(c2.is_trump(trump));
    ASSERT_FALSE(c3.is_trump(trump));
    ASSERT_TRUE(c4.is_trump(trump));
}
TEST(test_is_trump_diamonds) {
    const Suit trump = DIAMONDS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_FALSE(jackArray[0].is_trump(trump));
    ASSERT_TRUE(jackArray[1].is_trump(trump));
    ASSERT_TRUE(jackArray[2].is_trump(trump));
    ASSERT_FALSE(jackArray[3].is_trump(trump));
    ASSERT_FALSE(c1.is_trump(trump));
    ASSERT_FALSE(c2.is_trump(trump));
    ASSERT_TRUE(c3.is_trump(trump));
    ASSERT_FALSE(c4.is_trump(trump));
}
TEST(test_is_trump_hearts) {
    const Suit trump = HEARTS;
    Card jackArray[4] = {Card(JACK, CLUBS), Card(JACK, HEARTS),
                         Card(JACK, DIAMONDS), Card(JACK, SPADES)};
    Card c1(SIX, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(EIGHT, DIAMONDS);
    Card c4(NINE, SPADES);
    ASSERT_FALSE(jackArray[0].is_trump(trump));
    ASSERT_TRUE(jackArray[1].is_trump(trump));
    ASSERT_TRUE(jackArray[2].is_trump(trump));
    ASSERT_FALSE(jackArray[3].is_trump(trump));
    ASSERT_FALSE(c1.is_trump(trump));
    ASSERT_TRUE(c2.is_trump(trump));
    ASSERT_FALSE(c3.is_trump(trump));
    ASSERT_FALSE(c4.is_trump(trump));
}

// Add more test cases here
TEST(test_rank_and_suit) {
    Card ace_hearts(ACE, HEARTS);
    ASSERT_EQUAL(ace_hearts.get_rank(), ACE);
    ASSERT_EQUAL(ace_hearts.get_suit(), HEARTS);
}
TEST(test_read_card) {
    istringstream s("Three of Diamonds");
    Card c;
    s >> c;
    ASSERT_EQUAL(THREE, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
}
TEST(test_print_card) {
    Card c(SEVEN, CLUBS);
    ostringstream s;
    s << c;
    ASSERT_EQUAL(s.str(), "Seven of Clubs");
}
TEST(test_suit_next) {
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}
TEST(test_operators) {
    ASSERT_TRUE(Card(ACE, SPADES) < Card(ACE, HEARTS));
    ASSERT_TRUE(Card(ACE, HEARTS) < Card(ACE, CLUBS))
    ASSERT_TRUE(Card(ACE, CLUBS) < Card(ACE, DIAMONDS));
    ASSERT_FALSE(Card(ACE, SPADES) > Card(ACE, HEARTS));
    ASSERT_FALSE(Card(ACE, SPADES) == Card(ACE, HEARTS));
    ASSERT_FALSE(Card(ACE, SPADES) >= Card(ACE, HEARTS));
    ASSERT_TRUE(Card(ACE, SPADES) <= Card(ACE, HEARTS));
    ASSERT_TRUE(Card(ACE, SPADES) == Card(ACE, SPADES));
    ASSERT_TRUE(Card(ACE, SPADES) <= Card(ACE, SPADES));
    ASSERT_TRUE(Card(ACE, SPADES) >= Card(ACE, SPADES));

    ASSERT_TRUE(Card(TEN, SPADES) < Card(JACK, SPADES));
    ASSERT_TRUE(Card(JACK, SPADES) < Card(QUEEN, SPADES));
    ASSERT_TRUE(Card(QUEEN, SPADES) < Card(KING, SPADES));
    ASSERT_TRUE(Card(KING, SPADES) < Card(ACE, SPADES));
    ASSERT_TRUE(Card(TEN, SPADES) <= Card(JACK, SPADES));
    ASSERT_TRUE(Card(JACK, SPADES) <= Card(QUEEN, SPADES));
    ASSERT_TRUE(Card(QUEEN, SPADES) <= Card(KING, SPADES));
    ASSERT_TRUE(Card(KING, SPADES) <= Card(ACE, SPADES));
    ASSERT_FALSE(Card(TEN, SPADES) > Card(JACK, SPADES));
    ASSERT_FALSE(Card(JACK, SPADES) > Card(QUEEN, SPADES));
    ASSERT_FALSE(Card(QUEEN, SPADES) > Card(KING, SPADES));
    ASSERT_FALSE(Card(KING, SPADES) > Card(ACE, SPADES));
    ASSERT_FALSE(Card(TEN, SPADES) >= Card(JACK, SPADES));
    ASSERT_FALSE(Card(JACK, SPADES) >= Card(QUEEN, SPADES));
    ASSERT_FALSE(Card(QUEEN, SPADES) >= Card(KING, SPADES));
    ASSERT_FALSE(Card(KING, SPADES) >= Card(ACE, SPADES));
}
TEST(test_card_less) {
    //nontrump < trump
    ASSERT_TRUE(Card_less(Card(ACE, HEARTS), Card(EIGHT, CLUBS), CLUBS));
    //nothing is less than itself
    ASSERT_FALSE(Card_less(Card(KING, SPADES), Card(KING, SPADES), SPADES));
    //compare bowers
    ASSERT_TRUE(Card_less(Card(JACK, HEARTS), Card(JACK, DIAMONDS), DIAMONDS));
    //Check rank order, both trump
    ASSERT_TRUE(Card_less(Card(TWO, SPADES), Card(THREE, SPADES), SPADES));
    //Check rank order, both nontrump
    ASSERT_TRUE(Card_less(Card(TWO, SPADES), Card(THREE, SPADES), CLUBS));
    //Check suit order
    ASSERT_TRUE(Card_less(Card(FOUR, SPADES), Card(FOUR, DIAMONDS), HEARTS));
    //Jack trump > nonjack trump
    ASSERT_FALSE(Card_less(Card(JACK, SPADES), Card(ACE, SPADES), SPADES));
}
TEST(test_card_less_led) {
    //nontrump < trump
    ASSERT_TRUE(Card_less(Card(ACE, HEARTS), Card(EIGHT, CLUBS), Card(NINE, HEARTS), CLUBS));
    //nothing is less than itself
    ASSERT_FALSE(Card_less(Card(KING, SPADES), Card(KING, SPADES), Card(NINE, HEARTS), SPADES));
    //compare bowers
    ASSERT_TRUE(Card_less(Card(JACK, HEARTS), Card(JACK, DIAMONDS), Card(NINE, HEARTS), DIAMONDS));
    //Check rank order, both trump & nonjack
    ASSERT_TRUE(Card_less(Card(TWO, SPADES), Card(THREE, SPADES), Card(NINE, HEARTS), SPADES));
    //Check rank order, both nontrump
    ASSERT_TRUE(Card_less(Card(TWO, SPADES), Card(THREE, SPADES), Card(NINE, HEARTS), CLUBS));
    //Check suit order of nontrump nonled cards
    ASSERT_TRUE(Card_less(Card(FOUR, SPADES), Card(FOUR, DIAMONDS), Card(SEVEN, HEARTS), CLUBS));
    //Jack trump > nonjack trump
    ASSERT_FALSE(Card_less(Card(JACK, SPADES), Card(ACE, SPADES), Card(TEN, HEARTS), SPADES));
    //Led > nonled
    ASSERT_TRUE(Card_less(Card(SEVEN, CLUBS), Card(FOUR, HEARTS), Card(KING, HEARTS), DIAMONDS));
}
TEST_MAIN()
