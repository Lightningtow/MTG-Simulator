//
// Created by alexw on 11/15/2022.
//
#include "Card.h"
using namespace std;


/// all time complexities are constant



Card::Card() = default;

// printing a Card object just prints its title
// Time complexity: constant
ostream& operator<<(ostream& outStream, const Card& obj) {
    outStream << obj.name;
    return outStream;
}



// The operator + overloads are for appending the card title to strings, using the Card object
// So you can run `string cardstring = "hello to " + Cardobject;
// Time complexity: constant
string Card::operator+(const string& appendto) const {
    string newstr = appendto + this->name;
    return newstr;
}
string Card::operator+(const char * appendto) const {
    string newstr = appendto + this->name;
    return newstr;
}




// All of these comparison overloads just compare card types
// Lands are greater than cards that aren't lands
// Time complexities for all overload funcs are constant
bool Card::operator>(const Card& comp) const {
    // greater than, but not equal to
    if (this->type == land && comp.type != land) return true;
    else return false;

}
bool Card::operator>=(const Card& comp) const {
    // greater than, or equal to
    if(this->type == comp.type) return true; // equal to
    else if (this->type == land && comp.type != land) return true;
    else return false;
    return false;
}
bool Card::operator<(const Card& comp) const {
    // less than, but not equal to
    if (this->type != land && comp.type == land) return true;
    else return false;
}
bool Card::operator<=(const Card& comp) const {
    // less than, or equal to
    if(this->type == comp.type) return true; // equal to
    else if (this->type != land && comp.type == land) return true;
    else return false;
}
bool Card::operator==(const Card& rightobj) const {
    return (this->name == rightobj.name);
}

