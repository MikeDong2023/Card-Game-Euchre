#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
/* In the first round, a Simple player (whether dealer or not)
 * will only order up if they have at least 2 face or ace cards
 * of the same suit as the upcard.
 */
TEST(test_player_make_trump_round1) {
    //George has exactly 1 matching ace and the right bower
    Player * george = Player_factory("George", "Simple");
    george->add_card(Card(SEVEN, HEARTS));
    george->add_card(Card(EIGHT, HEARTS));
    george->add_card(Card(NINE, HEARTS));
    george->add_card(Card(JACK, CLUBS));
    george->add_card(Card(ACE, SPADES));
    Card up1(QUEEN, SPADES);
    Suit trump;
    ASSERT_TRUE(george->make_trump(up1, false, 1, trump));
    ASSERT_TRUE(george->make_trump(up1, true, 1, trump));
    ASSERT_EQUAL(SPADES, trump);
    delete george; //DIE, GEORGE!!!!!
    //John has 1 matching face card
    Player * john = Player_factory("John", "Simple");
    john->add_card(Card(SEVEN, HEARTS));
    john->add_card(Card(EIGHT, HEARTS));
    john->add_card(Card(NINE, HEARTS));
    john->add_card(Card(JACK, CLUBS));
    john->add_card(Card(KING, DIAMONDS));
    Card up2(JACK, DIAMONDS);
    ASSERT_FALSE(john->make_trump(up2, false, 1, trump));
    ASSERT_FALSE(john->make_trump(up2, true, 1, trump));
    delete john;
    //Thomas has no matching face cards
    Player * tom = Player_factory("Thomas", "Simple");
    tom->add_card(Card(NINE, CLUBS));
    tom->add_card(Card(EIGHT, CLUBS));
    tom->add_card(Card(KING, HEARTS));
    tom->add_card(Card(KING, DIAMONDS));
    tom->add_card(Card(TEN, HEARTS));
    Card up3(TEN, CLUBS);
    ASSERT_FALSE(tom->make_trump(up3, false, 1, trump));
    ASSERT_FALSE(tom->make_trump(up3, true, 1, trump));
    delete tom;
    //James has 2 matching face cards and an ace
    Player * james = Player_factory("James", "Simple");
    james->add_card(Card(EIGHT, HEARTS));
    james->add_card(Card(TEN, HEARTS));
    james->add_card(Card(KING, HEARTS));
    james->add_card(Card(JACK, DIAMONDS));
    james->add_card(Card(ACE, HEARTS));
    Card up4(QUEEN, HEARTS);
    ASSERT_TRUE(james->make_trump(up4, false, 1, trump));
    ASSERT_TRUE(james->make_trump(up4, true, 1, trump));
    ASSERT_EQUAL(HEARTS, trump);
    delete james;
}
/* A Simple Player considers ordering up the suit with the same color as the upcard,
 * which would make that suit trump. They will order up if that would mean they have 
 * one or more cards that are either face or ace cards of the trump suit in their hand.
 */
TEST(test_player_make_trump_round2) {
    /* Player has exactly 1 matching face card, the right bower, and no aces. They order
     * up regardless of whether they are the dealer.
     */
    Player * george = Player_factory("George", "Simple");
    george->add_card(Card(SEVEN, HEARTS));
    george->add_card(Card(EIGHT, HEARTS));
    george->add_card(Card(NINE, HEARTS));
    george->add_card(Card(JACK, DIAMONDS));
    george->add_card(Card(JACK, SPADES));
    Card up1(QUEEN, DIAMONDS);
    Suit trump;
    ASSERT_TRUE(george->make_trump(up1, false, 2, trump));
    ASSERT_TRUE(george->make_trump(up1, true, 2, trump));
    ASSERT_EQUAL(HEARTS, trump);
    delete george;
    /* Player has exactly 1 matching ace and no matching face cards. They order up
     * regardless of whether they are the dealer.
     */
    Player * tom = Player_factory("Thomas", "Simple");
    tom->add_card(Card(ACE, SPADES));
    tom->add_card(Card(EIGHT, DIAMONDS));
    tom->add_card(Card(KING, HEARTS));
    tom->add_card(Card(KING, DIAMONDS));
    tom->add_card(Card(TEN, HEARTS));
    Card up3(TEN, CLUBS);
    ASSERT_TRUE(tom->make_trump(up3, false, 2, trump));
    ASSERT_TRUE(tom->make_trump(up3, true, 2, trump));
    delete tom;
    /* Player has no matching face or ace cards. They only order up if they are the
     * dealer.
     */
    Player * james = Player_factory("James", "Simple");
    james->add_card(Card(ACE, CLUBS));
    james->add_card(Card(NINE, CLUBS));
    james->add_card(Card(TEN, CLUBS));
    james->add_card(Card(KING, CLUBS));
    james->add_card(Card(QUEEN, CLUBS));
    ASSERT_FALSE(james->make_trump(Card(TEN, HEARTS), false, 2, trump));
    ASSERT_TRUE(james->make_trump(Card(TEN, HEARTS), true, 2, trump));
    delete james;
}
TEST(test_player_lead_card) {
    //A simple player will lead with the highest nontrump
    Player * tom = Player_factory("Thomas", "Simple");
    tom->add_card(Card(NINE, CLUBS));
    tom->add_card(Card(EIGHT, CLUBS));
    tom->add_card(Card(KING, HEARTS));
    tom->add_card(Card(KING, DIAMONDS));
    tom->add_card(Card(JACK, SPADES));
    ASSERT_EQUAL(Card(KING, DIAMONDS), tom->lead_card(CLUBS));
    delete tom;
    /* If all cards are trump, a simple player will play the highest 
     * (right bower in this case).
     */
    Player * george = Player_factory("George", "Simple");
    george->add_card(Card(KING, SPADES));
    george->add_card(Card(QUEEN, SPADES));
    george->add_card(Card(JACK, CLUBS));
    george->add_card(Card(TEN, SPADES));
    george->add_card(Card(NINE, SPADES));
    ASSERT_EQUAL(Card(JACK, CLUBS), george->lead_card(SPADES));
    delete george;
}
/* If a Simple Player can follow suit, they play the highest card that follows suit.
 * Otherwise, they play the lowest card in their hand.
 */
//At leat 1 card matches the led suit.
TEST(test_player_play_card_follow) {
    //All cards match the led suit. Player plays the highest card, the right bower.
    Player * tom = Player_factory("Thomas", "Simple");
    tom->add_card(Card(NINE, CLUBS));
    tom->add_card(Card(EIGHT, CLUBS));
    tom->add_card(Card(KING, CLUBS));
    tom->add_card(Card(JACK, SPADES));
    tom->add_card(Card(TEN, CLUBS));
    Card led(ACE, CLUBS);
    ASSERT_EQUAL(tom->play_card(led, CLUBS), Card(JACK, SPADES));
    delete tom;
    //One card matches the led suit. The player plays it.
    Player * george = Player_factory("George", "Simple");
    george->add_card(Card(SEVEN, CLUBS));
    george->add_card(Card(EIGHT, CLUBS));
    george->add_card(Card(NINE, HEARTS));
    george->add_card(Card(JACK, DIAMONDS));
    george->add_card(Card(JACK, SPADES));
    ASSERT_EQUAL(george->play_card(Card(TEN, DIAMONDS), CLUBS), Card(JACK, DIAMONDS));
    delete george;
    //2 cards match the led suit. Player plays the highest one, the ace of hearts.
    Player * adam = Player_factory("Adam", "Simple");
    adam->add_card(Card(JACK, DIAMONDS));
    adam->add_card(Card(TEN, HEARTS));
    adam->add_card(Card(ACE, HEARTS));
    adam->add_card(Card(TEN, CLUBS));
    adam->add_card(Card(JACK, SPADES));
    ASSERT_EQUAL(adam->play_card(Card(QUEEN, HEARTS), CLUBS), Card(ACE, HEARTS));
    //Ditto, but with a different trump suit. Result should be identical.
    adam->add_card(Card(ACE, HEARTS));
    ASSERT_EQUAL(adam->play_card(Card(QUEEN, HEARTS), DIAMONDS), Card(ACE, HEARTS));
    delete adam;
    
}
//None of the player cards match the led suit
TEST(test_player_play_card_no_follow) {
    /* None of the cards are trump. Player plays the lowest ranked card, the
     * eight of clubs.
     */
    Player * tom = Player_factory("Thomas", "Simple");
    tom->add_card(Card(NINE, CLUBS));
    tom->add_card(Card(EIGHT, CLUBS));
    tom->add_card(Card(KING, CLUBS));
    tom->add_card(Card(JACK, SPADES));
    tom->add_card(Card(TEN, CLUBS));
    Card led1(ACE, HEARTS);
    ASSERT_EQUAL(tom->play_card(led1, CLUBS), Card(EIGHT, CLUBS));
    delete tom;
    /* Some of the cards are trump. Player plays the lowest card with
     * consideration of trump, the jack of clubs.
     */
    Player * john = Player_factory("John", "Simple");
    john->add_card(Card(SEVEN, HEARTS));
    john->add_card(Card(EIGHT, HEARTS));
    john->add_card(Card(NINE, HEARTS));
    john->add_card(Card(JACK, CLUBS));
    john->add_card(Card(KING, DIAMONDS));
    ASSERT_EQUAL(john->play_card(Card(ACE, SPADES), HEARTS), Card(JACK, CLUBS));
    delete john;
}
/* If the trump suit is ordered up during round one, the dealer picks up the upcard.
 * The dealer then discards the lowest card in their hand, even if this is the upcard,
 * for a final total of five cards. (Note that at this point, the trump suit is the suit
 * of the upcard.)
 */
TEST(test_add_and_discard) {
    //Case 1: upcard is not the lowest card
    Player * george = Player_factory("George", "Simple");
    george->add_card(Card(SEVEN, CLUBS)); //Discarded by a Simple Player
    george->add_card(Card(EIGHT, CLUBS));
    george->add_card(Card(NINE, CLUBS));
    george->add_card(Card(KING, DIAMONDS));
    george->add_card(Card(TEN, CLUBS));
    george->add_and_discard(Card(ACE, HEARTS));
    Card led(KING, SPADES);
    ASSERT_EQUAL(george->play_card(led, DIAMONDS), Card(EIGHT, CLUBS));
    ASSERT_EQUAL(george->play_card(led, DIAMONDS), Card(NINE, CLUBS));
    ASSERT_EQUAL(george->play_card(led, DIAMONDS), Card(TEN, CLUBS));
    ASSERT_EQUAL(george->play_card(led, DIAMONDS), Card(ACE, HEARTS));
    ASSERT_EQUAL(george->play_card(led, DIAMONDS), Card(KING, DIAMONDS));
    delete george;
    //Case 2: upcard is the lowest card
    Player * james = Player_factory("James", "Simple");
    james->add_card(Card(ACE, CLUBS));
    james->add_card(Card(TEN, CLUBS));
    james->add_card(Card(JACK, CLUBS));
    james->add_card(Card(JACK, SPADES));
    james->add_card(Card(QUEEN, CLUBS));
    james->add_and_discard(Card(NINE, CLUBS));
    Card led2(NINE, HEARTS);
    ASSERT_EQUAL(james->play_card(led2, HEARTS), Card(TEN, CLUBS));
    ASSERT_EQUAL(james->play_card(led2, HEARTS), Card(JACK, SPADES));
    ASSERT_EQUAL(james->play_card(led2, HEARTS), Card(JACK, CLUBS));
    ASSERT_EQUAL(james->play_card(led2, HEARTS), Card(QUEEN, CLUBS));
    ASSERT_EQUAL(james->play_card(led2, HEARTS), Card(ACE, CLUBS));
    delete james;
}
// Add more tests here

TEST_MAIN()
