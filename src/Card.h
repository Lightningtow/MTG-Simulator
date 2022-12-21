//
// Created by alexw on 11/15/2022.
//

#ifndef GOLDFISH_CARD_H
#define GOLDFISH_CARD_H
#include <iostream>
using namespace std;

class Card {
/*
 * The Card class is used to create, move around, and access Card objects,
 *  with each Card representing exactly one Magic: The Gathering card instance.
 *
 * For example, your library is completely made up of Card objects, and so is your hand, and most data structures in the program use Card objects.
 * Most functions responsible for running Magic: The Gathering
 *  games do so by accessing and moving around Card objects, as one would if playing in real life.
 *
 * The other use for the Card object is as a container to store relevant variables in a package that's easy to access and pass between functions.
 * Any given Card object doesn't necessarily have to have every single stat filled out, and many instances of Card objects simply
 *  serve as a consolidated way of passing half a dozen variables to a function.
 *
 *
 * Note: when I say 'Card', capitalized, in documentation or code files like this one, it always refers to a a Card object.
 * If I say 'card', lowercase, it's meant as a more broad reference to Magic: The Gathering cards in general.
 *
 *
 */
public:
    enum evalidtypes { // all card types
        land,
        creature,
        instant, // when playing against a goldfish opponent
        sorcery, // instants and sorceries are identical

    };

/* All cards have stats. These are all initialized to the most likely stat
 * For example, a Mountain. type is land, title is Mountain, and the bool `mountain` is true
 *  and all of the other possible variable combinations shouldn't change from the values below
 *
 * I set everything closest to how it should be here, that way in the getCardData function,
 *  I don't need to waste time setting all the other fields to their default values */



    string defaultname = "DEFAULT CARD NAME ==============================================================================";
    string name = defaultname;
    // Some Card objects are used internally to transfer card content data
    //  in which case it doesn't need a name, the Card is just the box the info is shipped in.
    // But then it shouldn't be displayed to the user, that's why I have the default name obnoxious and very noticeable
    //  to make it obvious if it accidentally gets printed while testing

    evalidtypes type; // all cards have a type, and all cards have a name, no matter what


/** mana cost variables, for creatures/oneshots */

    int mana_value = 0; // a mana value of -1 means its a land but shouldn't rely on this
    string displaycost; // displaycost is a mana cost like '1R', also referred to as 'full cost'


    int redneeded = 0;
    int whiteneeded = 0; // meaning, "how much mana of each type do you need to cast this spell"
    int genericNeeded = 0;


/** creatures variables */
    int power = -1; // how much damage creatures do


/** oneshot variables */
    int damage = -1; // for damage spells; this is different than "power"




/** land variables */
    bool isDual = false;
    bool isFetch = false;
    bool isPlains = false;
    bool isMountain = false; // used for easier card identification

    bool tapped; // Cards should only be tapped while on the battlefield, never while in hand/library/graveyard


/** functions */

    Card(); // default constructor

    // All of these comparison overloads just compare types
    // Lands are greater than cards that aren't lands
    bool operator>(const Card&) const;
    bool operator>=(const Card&) const;
    bool operator<(const Card&) const;
    bool operator<=(const Card&) const;
    bool operator==(const Card&) const;


    // These overloads append the card name to the end of the string
    // So you can do stuff like `cout << "I just drew the card " + Cardobject + "!" << endl;
    string operator+(const char[]) const;
    string operator+(const string&) const;

    // Outstream overload just prints the name of the card as a string
    friend ostream& operator<<(ostream&, const Card&);
};


#endif //GOLDFISH_CARD_H
