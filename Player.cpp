#include "Card.cpp"
#include <vector>
class Player{
public:
    static Card nullCard;
    virtual string getName() = 0;
    virtual void drawCards(const Card&) = 0;
    virtual void firstDraw(const Card&) = 0;
    virtual Card playCard(const Card&) = 0;
    virtual int getHandSize() = 0;
    virtual bool getDraw() = 0;
    virtual void setDraw(bool) = 0;
};

Card Player:: nullCard = Card(Card::NONE, Card::NONE);

class Simple01 : public Player{
private:
    vector<Card> hand;
    vector<Card> newCards;
    int handSize;
    string name;
    bool draw;
public:
    Simple01(string);
    virtual string getName()    {return name;}
    virtual int getHandSize()   {return handSize;}
    virtual bool getDraw()      {return draw;}
    virtual void setDraw(bool b)  {draw = b;}
    virtual void drawCards(const Card&);
    virtual void firstDraw(const Card&);
    virtual Card playCard(const Card&);
};
Simple01:: Simple01(string name_in) : handSize(0), name(name_in), draw(false){}

//effects: put the newCard into newCards pile
void Simple01:: drawCards(const Card& newCard){
    newCards.push_back(newCard);
}
//the first time each player draw cards at the begining of a game.
//it doesn't set draw to false
void Simple01:: firstDraw(const Card& newCard){
    hand.push_back(newCard);
    handSize++;
}
// Simple01s always play the first card they can play
Card Simple01:: playCard(const Card& lastCard){
    //wait random seconds between 0 and 2, to make it looks more natural
    srand((int)time(NULL));
    unsigned int wait = rand() % 2;
    sleep(wait + 1);
    
    vector<Card>::iterator begin;
    vector<Card>::iterator end;
    Card temp = nullCard;
    if(!draw){
        begin = hand.begin();
        end = hand.end();
        while(begin != end){
            if((*begin).match(lastCard)){
                temp = *begin;
                hand.erase(begin);
                break;
            }
            ++begin;
        }
    }
    else{
        begin = newCards.begin();
        end = newCards.end();
        while(begin != end){
            if((*begin).match(lastCard)){
                Card temp = *begin;
                newCards.erase(begin);
            }
            //merge newCards with hands.
            if(begin != end){
                hand.push_back(*begin);
                handSize++;
            }
            ++begin;
        }
    }
    return temp;
}

//----------------------------------------------------------------------------
class Human : public Player{
private:
    vector<Card> hand;
    vector<Card> newCards;
    int handSize;
    string name;
    bool draw;
public:
    Human(string);
    virtual string getName()    {return name;}
    virtual int getHandSize()   {return handSize;}
    virtual bool getDraw()      {return draw;}
    virtual void setDraw(bool b)  {draw = b;}
    virtual void drawCards(const Card&);
    virtual void firstDraw(const Card&);
    virtual Card playCard(const Card&);
    void printHand() const;
    void printNewCards() const;
};

//ctor
Human:: Human(string name_in) : handSize(0), name(name_in), draw(false){}

//effects: put the newCard into newCards pile
void Human:: drawCards(const Card& newCard){
    newCards.push_back(newCard);
}
//the first time each player draw cards at the begining of a game.
//it doesn't set draw to false
void Human:: firstDraw(const Card& newCard){
    hand.push_back(newCard);
    handSize++;
}
//effects: if the player didn't draw a card, display the hand and prompt
//         the player to select a card to play. if the player has draw a card
//         display the newCards pile and prompt the player to select a card.
//         The player can choose not to play a card in either cases.
Card Human:: playCard(const Card& lastCard){
    int option;
    if(!draw){
        bool error = false;
        //use a loop to check errors
        do{
            cout << "Player " << name << ", ";
            cout << "enter the index of the card you want to play.  ";
            cout << "-1 to draw a card\n";
            printHand();
            
            //invalid input checking
            while (!(cin >> option)) {
                cin.clear(); //clear bad input flag
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                cout << "Invalid input; please re-enter.\n";
            }
            if(option != -1){
                //check if the option match last card
                if(lastCard.match(hand[option])){
                    //return the card being removed from hand.
                    Card toErase = hand[option];
                    hand.erase(hand.begin() + option);
                    handSize--;
                    return toErase;
                }
                cout << "the card you select does not match!";
                cout << " Please select another one or draw a card.\n\n\n";
                error = true;
            }
            else{
                error = false;
            }
        }while(error);
        return nullCard;
    }
    else{
        bool error = false;
        Card to_return;
        //use a loop to check errors
        do{
            cout << "From the cards you've drawn, do you have a card to play?\n";
            cout << "-1 to pass\n";
            printNewCards();
            cin >> option;
            if(option != -1){
                if(lastCard.match(newCards[option])){
                    to_return = newCards[option];
                    // remove selecting card from newCard
                    vector<Card>::iterator it = newCards.begin();
                    for(int i = 0; i < option; i++)
                        ++it;
                    newCards.erase(it);
                    error = false;
                }
                else{
                    cout << "the card you select does not match!";
                    cout << " Please select another one or draw a card.\n\n\n";
                    error = true;
                }
            }
            else{
                to_return = nullCard;
                error = false;
            }
        }while(error);
        //merge newCards and hand
        for(int size = (int)newCards.size(); size > 0; --size){
            hand.push_back(newCards.back());
            newCards.pop_back();
            handSize++;
        }
        //draw = false;
        return to_return;
    }
}

//effects: print the current cards in the hand according to standard interface
void Human:: printHand() const{
    for(auto &item : hand){
        cout << "|"<< item.getColor() <<"  " << item.getColor()<<" |  ";
    }
    cout << endl;
    for(auto &item : hand){
        cout << "   " <<item.getFace() << "     ";
    }
    cout << endl;
    for(auto &item : hand){
        cout << "|"<< item.getColor() << "  " << item.getColor()<<" |  ";
    }
    cout <<endl << "----------------------------------------------------";
    cout << "------------------------------------------------------------ \n";
    for(int i = 0; i < handSize; i++)
        cout << "   " << i << "     ";
    cout <<" (indexes)\n" << endl;
}

void Human:: printNewCards() const{
    for(auto &item : newCards){
        cout << "|"<< item.getColor() <<"  " << item.getColor()<<" |  ";
    }
    cout << endl;
    for(auto &item : newCards){
        cout << "   " <<item.getFace() << "     ";
    }
    cout << endl;
    for(auto &item : newCards){
        cout << "|"<< item.getColor() << "  " << item.getColor()<<" |  ";
    }
    cout <<endl << endl;
}

Player* playerFactory(string name, bool human){
    if(human)
        return new Human(name);
    return new Simple01(name);
}


