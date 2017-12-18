#include "Player.cpp"
#include "Pack.cpp"
void test_match(){
    Card c1(Card::GREEN, Card::SEVEN);
    Card c2(Card::GREEN, Card::TWO);
    Card c3(Card::BLUE, Card::SEVEN);
    Card c4(Card::RED, Card::EIGHT);
    Card c5(Card::GREEN, Card::NONE);
    assert(c1.match(c2));
    assert(c1.match(c3));
    assert(!c1.match(c4));
    assert(c1.match(c5));
}
void test_operator(){
    Card c1(Card::GREEN, Card::SEVEN);
    cout << c1;
}
void test_Pack_ctor(){
    Pack p1;
    for(int i = 0; i < 108; i++){
        cout << p1.deal();
    }
}
void test_shuffle(){
    Pack p1;
    p1.shuffle();
    for(int i = 0; i < 108; i++){
        cout << p1.deal();
    }
}
void test_printHand(){
    Human h1("Tom");
    h1.firstDraw(Card(Card::GREEN, Card::ONE));
    h1.firstDraw(Card(Card::GREEN, Card::TWO));
    h1.firstDraw(Card(Card::GREEN, Card::THREE));
    h1.firstDraw(Card(Card::GREEN, Card::FOUR));
    h1.firstDraw(Card(Card::GREEN, Card::FIVE));
    h1.firstDraw(Card(Card::GREEN, Card::SIX));
    h1.firstDraw(Card(Card::GREEN, Card::SEVEN));
    h1.printHand();
}
void test_playCards(){
    Human h1("Tom");
    h1.firstDraw(Card(Card::GREEN, Card::ONE));
    h1.firstDraw(Card(Card::GREEN, Card::TWO));
    h1.firstDraw(Card(Card::GREEN, Card::THREE));
    h1.firstDraw(Card(Card::GREEN, Card::FOUR));
    h1.firstDraw(Card(Card::GREEN, Card::FIVE));
    h1.firstDraw(Card(Card::GREEN, Card::SIX));
    h1.firstDraw(Card(Card::GREEN, Card::SEVEN));
    cout << h1.playCard(Card(Card::GREEN, Card::SEVEN));
    h1.printHand();
}
int main(){
    //test_match();
    //test_operator();
    //cout << "\n\n";
    //test_Pack_ctor();
    //test_shuffle();
    //test_printHand();
    
    test_playCards();
    cout << "pass!\n";
}
