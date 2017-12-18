#include "Card.cpp"

static const int CAPACITY = 108;
class Pack{
private:
    //index tracks the index of cards
    //num is the number of cards in the pack
    Card *cards;
    int index;
    int num;
public:
    Pack();
    // Pack(int) won't initially load cards
    Pack(int);
    void reset();
    Card deal();
    void shuffle();
    bool empty();
    int getNum();
    void insert(Card &);
    //big three
    Pack& operator=(const Pack&);
    ~Pack();
};
Pack:: Pack(int) :cards(new Card[CAPACITY]), index(0), num(0) {}            //deal with it later!
Pack:: Pack() : Pack(0){
    for(int i = 0; i < 4; ++i){
        string color = Card::colorArray[i];
        for(int j = 0; j < 13; ++j){
            cards[i * 13 + j] = Card(color, Card::faceArray[j]);
            num++;
        }
        for(int j = 1; j < 13; ++j){
            cards[52 + i * 12 + j - 1] = Card(color, Card:: faceArray[j]);
            num++;
        }
    }
    for(int i = 0; i < 4; ++i){
        cards[100 + i] = Card(Card::NONE, Card::WILD);
        cards[104 + i] = Card(Card::NONE, Card::WILD_4);
        num += 2;
    }
    // get a random shuffle
    srand((int)time(NULL));
    for(int i = rand() % 10; i > 0; --i)
        shuffle();
}

void Pack:: reset(){
    index = 0;
    num = CAPACITY;
}

Card Pack:: deal(){
    return cards[num--];
}

void Pack:: shuffle(){
    Card *newCards = new Card[CAPACITY];
    Card *half = cards + CAPACITY / 2, *head = cards;
    for(int i = 0; i < CAPACITY; i += 2, ++half, ++head){
        newCards[i] = *half;
        newCards[i+1] = *head;
    }
    delete []cards;
    
    cards = newCards;
    // create a more complex shuffle after finish
}

bool Pack:: empty(){
    return index = CAPACITY - 1;
}

int Pack:: getNum(){
    return num;
}

void Pack:: insert(Card &c){
    cards[num] = c;
    num++;
}

Pack& Pack:: operator=(const Pack& rhs){
    if(this == &rhs){
        return *this;
    }
    int size = rhs.num;
    for(int i = 0; i < size; ++i){
        cards[i] = rhs.cards[i];
    }
    index = 0;
    num = rhs.num;
    return *this;
}

Pack:: ~Pack(){
    delete []cards;
}




