#include "Player.cpp"
#include "Pack.cpp"
#include <list>
#include <iostream>
using namespace std;

class Game{
private:
    list<Player*> players;
    Pack cardPile;
    Pack discardPile;
    Card lastCard;
public:
    Game();
    
    //special effect will ask the current player to choose a color.
    //Then change lastCard to a card with that color but don't have face.
    void special_effect(list<Player*>::iterator& current);
    
    //check if the iterator equals the end, and if it equals,
    //assign begin() to current
    void check_restart(list<Player*>::iterator& current);
    
    //playGame is the panel of the whole game. The game is running on playgame()
    void playGame();
        
    // judge determindes the next player to play,
    // the punishments (for now, +4_wild is simply
    // change color & the next player draw four cards), and special effects.
    list<Player*>::iterator judge(const list<Player*>::iterator currentPlayer);
    
    //game interface
    void gameInterface();
};
Game:: Game() : discardPile(Pack(0)){
    int numPlayers;
    string name;
    cout << "********\n  Uno!\n********\n";
    cout << "Please enter the number of players: ";
    cin >> numPlayers;
    cout << "Please enter your name: \n";
    cin >> name;
    // create Simple players
    for(int i = 0; i < numPlayers - 1; ++i){
        players.push_back(playerFactory("Simple 0" + to_string(i + 1), false));
    }

    //create Human according to name
    players.push_back(playerFactory(name, true));
    
    // deal cards to them.
    for(auto &item : players){
        for(int i = 0; i < 7; i++)
            item->firstDraw(cardPile.deal());
    }
    lastCard = cardPile.deal();
}

void Game:: special_effect(list<Player*>::iterator& current){
    int option;
    
    //invalid input checking
    while (!(cin >> option)) {
        cin.clear(); //clear bad input flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
    }
    cout << "Player " << (*current)->getName();
    cout << ", please choose a color you want to change: \n";
    cout << Card::RED << "  " << Card::YELLOW << "  " << Card:: BLUE;
    cout << "  " << Card:: GREEN << endl;
    cout << "enter an index: ";
    cin >> option;
    lastCard = Card(Card::colorArray[option], Card:: NONE);
}

void Game:: check_restart(list<Player*>::iterator& current){
    if(current == players.end())
       current = players.begin();
}

list<Player*>::iterator Game:: judge(list<Player*>::iterator currentPlayer){
    if(lastCard == Player::nullCard){
        if(!(*currentPlayer)->getDraw()){
            (*currentPlayer)->drawCards(cardPile.deal());
            (*currentPlayer)->setDraw(true);
            
            //if the number of card isn't enough
            //shuffle the discard pile, and use it to deal cards
            if(cardPile.empty()){
                discardPile.shuffle();
                cardPile = discardPile;
            }
        }
        else{
            (*currentPlayer)->setDraw(false);
            ++currentPlayer;
            check_restart(currentPlayer);
        }
        return currentPlayer;
    }
    else if(lastCard.getFace() == Card::SKIP){
        (*currentPlayer)->setDraw(false);
        ++currentPlayer;
        check_restart(currentPlayer);
        cout << endl << (*currentPlayer)->getName() << " is skipped! \n\n";
        ++currentPlayer;
        check_restart(currentPlayer);
    }
    else if(lastCard.getFace() == Card:: REVERSE){
        (*currentPlayer)->setDraw(false);
        players.reverse();
        cout << endl << (*currentPlayer)->getName() << " uses reverse! \n\n";
        ++currentPlayer;
        check_restart(currentPlayer);
    }
    else if (lastCard.getFace() == Card:: PLUS_TWO){
        (*currentPlayer)->setDraw(false);
        ++currentPlayer;
        check_restart(currentPlayer);
        cout << endl << (*currentPlayer)->getName() << " draw two cards! \n\n";
        (*currentPlayer)->drawCards(cardPile.deal());
        (*currentPlayer)->drawCards(cardPile.deal());
        (*currentPlayer)->setDraw(true);
    }
     else if(lastCard.getFace() == Card:: WILD_4){
         (*currentPlayer)->setDraw(false);
         special_effect(currentPlayer);
         currentPlayer++;
         check_restart(currentPlayer);
         //next player draw four cards
         cout << endl << (*currentPlayer)->getName() << " draw four cards! \n\n";
         for(int i = 0; i < 4; i++){
             (*currentPlayer)->drawCards(cardPile.deal());
         }
         (*currentPlayer)->setDraw(true);
     }
     else if(lastCard.getFace() == Card:: WILD){
         (*currentPlayer)->setDraw(false);
         special_effect(currentPlayer);
         cout << endl << (*currentPlayer)->getName() << " change color to ";
         cout << lastCard.getColor() << " ! \n\n";
         currentPlayer++;
         check_restart(currentPlayer);
     }
     else{
         (*currentPlayer)->setDraw(false);
         ++currentPlayer;
         check_restart(currentPlayer);
     }
    return currentPlayer;
}

void Game:: playGame(){
    //determind the first player
    list<Player*>::iterator currentPlayer = players.begin();
    srand((int)time(NULL));
    int r = rand() % players.size();
    for(int i = 0; i < r; ++i){
        ++currentPlayer;
    }
    //start playing
    cout <<endl <<"Up Card :\n"<< lastCard <<endl;
    //use temp as a buffer
    Card temp;
    do{
        //temperorily keep the original lastCard
        temp = lastCard;
        lastCard = (*currentPlayer)->playCard(lastCard);
        //if the player doesn't play a nullCard, display what is played
        if(lastCard != Player::nullCard){
            cout << (*currentPlayer)->getName() << " played: ⬇ ";
            int size = (*currentPlayer)->getHandSize();
            for(int i = 0; i < size; ++i)
                cout << '*';
            cout << "\n\n" << lastCard << endl;
            discardPile.insert(lastCard);
        }
        else if(!(*currentPlayer)->getDraw()){
            cout <<endl << (*currentPlayer)->getName() << " chooses to draw a card.\n";
        }
        
        //warning from players
        if((*currentPlayer)->getHandSize() == 1)
            cout << endl << (*currentPlayer)->getName() << " says UNO! \n\n\n";
        else if((*currentPlayer)->getHandSize() == 0){
            cout << endl << endl << (*currentPlayer)->getName() << " win the game! \n";
            return;
        }
        currentPlayer = judge(currentPlayer);
        // restore lastCard when the player played a nullCard
        if(lastCard == Player::nullCard)
            lastCard = temp;
    }while((*currentPlayer)->getHandSize());
}

void gameInterface(){
    
}
int main(){
    Game g1;
    g1.playGame();
}