#ifndef CARD//.H
#define CARD//.H

#include <iostream>
#include <cassert>
#include <string>
using namespace std;
class Card{
private:
    string color;
    string face;
public:
    //color
    static const char* RED;
    static const char* YELLOW;
    static const char* BLUE;
    static const char* GREEN;
    static const char* NONE;
    //face
    static const char* ZERO;
    static const char* ONE;
    static const char* TWO;
    static const char* THREE;
    static const char* FOUR;
    static const char* FIVE;
    static const char* SIX;
    static const char* SEVEN;
    static const char* EIGHT;
    static const char* NINE;
    static const char* SKIP;
    static const char* REVERSE;
    static const char* PLUS_TWO;
    static const char* WILD;
    static const char* WILD_4;
    
    static const char *faceArray[];
    static const char *colorArray[];
    //functions
    Card(){}
    Card(string color_in, string face_in);
    string getColor() const;
    string getFace() const;
    bool match(const Card&) const;
    bool operator==(const Card&);
    bool operator!=(const Card&);
};
const char* Card:: RED = "❤️";
const char* Card:: YELLOW = "💛";
const char* Card:: BLUE = "💙";
const char* Card:: GREEN = "💚";
const char* Card:: NONE = "❓";
const char* Card:: ZERO = "0";
const char* Card:: ONE = "1";
const char* Card:: TWO = "2";
const char* Card:: THREE = "3";
const char* Card:: FOUR = "4";
const char* Card:: FIVE = "5";
const char* Card:: SIX = "6";
const char* Card:: SEVEN = "7";
const char* Card:: EIGHT = "8";
const char* Card:: NINE = "9";
const char* Card:: SKIP = "🚫";
const char* Card:: REVERSE = "♻️";
const char* Card:: PLUS_TWO = "+2";
const char* Card:: WILD = "🌟";
const char* Card:: WILD_4 = "🌟 +4";
const char* Card:: faceArray[] =
{ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SKIP, REVERSE
    ,PLUS_TWO};
const char* Card:: colorArray[] = {RED, YELLOW, BLUE, GREEN};
// construtor
//requires: color_in and face_in cannor both be "none"
Card:: Card(string color_in, string face_in) :
color(color_in), face(face_in){}
// --- end constructor
string Card:: getColor() const{
    return color;
}
string Card:: getFace() const{
    return face;
}
//requires: input card has to have a color
//effect: return whether two cards match. That is:
//        either the face is the same or the color
//        is the same.
bool Card:: match(const Card &rhs) const{
    //assert(rhs.color != NONE);
    if(rhs.face == WILD || rhs.face == WILD_4)
        return true;
    return color == rhs.color || face == rhs.face;
}
//effects: print the input card with the standard
//         interface according to its color and face
ostream& operator<<(ostream& os, const Card& rhs){
    os << "|"<< rhs.getColor() <<"  " << rhs.getColor()<<" |\n";
    os << "\n   " <<rhs.getFace() << "\n\n";
    os << "|"<< rhs.getColor() << "  " << rhs.getColor()<<" |\n";
    return os;
}

//overloaded operator
bool Card:: operator==(const Card& rhs){
    return face == rhs.face && color == rhs.color;
}
bool Card:: operator!=(const Card& rhs){
    return face != rhs.face || color != rhs.color;
}
#endif





