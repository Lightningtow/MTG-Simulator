//
// Created by alexw on 11/15/2022.
//

#ifndef GOLDFISH_GOLDFISH_H
#define GOLDFISH_GOLDFISH_H

#include "../Card.h"
#include "../GameResult.h"

#include "../stack/ArrayStack.h"
#include "../list/LinkedList.h"
#include "../stack/LinkedStack.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>


class Goldfish {

/*

 Far and away the bulk of the code is within the Goldfish class.
 This class houses all of the infrastructure and logic for simulating Magic games,
     as well as all the functions relating to user interfaces, file reading, and file writing.

 It also holds many variables for keeping track of all of the numerous things that need to be kept track of, such as life totals,
     what lands you have played, what turn it is, how many lands are untapped, etc.

 All functions and variables are private, with the exception of `run()`, which is instantiated to initiate the Goldfish application.

 To use this class, simply instantiate a Goldfish object and call `run()` with it.


 */


public:

    // the true main() of my program. Found in Goldfish.cpp
    void run();

private:


    // Only used for `setw` in a few places
    int GAMENUMWIDTH = -1;

    // If maximum simulated turncount is >=10, this becomes '2' to add an extra space in overviews.
    int TURNWIDTH = 1;

    // Display name of the deck you're using, for output file
    string deckname;


/** program ADTs */
    // `deck` holds all the cards read from the file. After that, it never changes.
    // The ONLY way it is used is to copy it over to the library at the beginning of every new game instance
    Card deck [60];

    // All lands and creatures on battlefield, respectively. Lands are a list for direct access and Creatures, for constant push() time.
    LinkedList<Card> fieldLands;
    LinkedStack<Card> fieldCreatures;

    // Cards in your hand. List, for access to getElement()
    LinkedList<Card> hand;

    // The draw pile. ArrayStack because it's always going to be near or at 60 but not exceeding it
    ArrayStack<Card>* library = new ArrayStack<Card>(60);

    // The discard pile. Stack because it's a stack of cards, and so logging is constant
    LinkedStack<Card> graveyard;


    // List of the logs of all games ran. Queue so logging is constant, and double-ended access
    LinkedQueue<GameResult> allGamesResults;

    // The object holding logs of one game. every reset(), `thisgame`  is added to allGamesResults, then wiped clean to use again.
    GameResult thisgame;


//    int creaturesPlayed = 0;
//    int oneshotsPlayed = 0; // these are found in GameResult



/** variables for use ingame */
    // whether it's recording the results. Always true
    bool logging = true;

    // whether it's logging debugging stuff such as logic flow
    bool debugging = true;


    // total amount of lands your deck runs. Treated as consts. Don't decrement, ever. Used to reset landsInLibrary vars in reset()
    int TOTALDUALS = 0;
    int TOTALPLAINS = 0;
    int TOTALMOUNTAINS = 0;


    // once this hits zero, you win, and onto the next game of the simulation
    int enemylife = 20;


/* Yes, these are a lot of variables
 * Most of these can be (and is, in updateLandVars) counted by traversing your hand with an accumulator
 * However, keeping independent variables brings many functions from O(n) to constant time complexity
 *      as well as having code be far more easy to read and absorb
 * The alternative is traversing the whole thing every time you want to find a specific variable, which is suboptimal to say the least
*/

    // all of these are incremented in drawCard func and decremented when you play them
    int spellsInHand = 0;
    int oneshotsInHand = 0;
    int creaturesInHand = 0;


    // these are set in readCardData(), decremented in drawCard(), and used in fetch() to check if looping is necessary,
    //      because for example if there's no duals in the library, no need to search for a dual
    int dualsInLibrary = 0;
    int plainsInLibrary = 0;
    int mountainsInLibrary = 0;




/** NEVER CHANGE THESE BELOW MANUALLY */


    // total lands of each type on the battlefield, regardless of tapped status
    int landsout = 0;
    int dualsOut = 0;
    int rLandsOut = 0; // never change these manually
    int wLandsOut = 0;

    // total lands of each type in your hand
    int landsInHand = 0;
    int dualsInHand = 0;
    int plainsInHand = 0; // never change these manually
    int fetchesInHand = 0;
    int mountainsInHand = 0;

/** NEVER CHANGE THESE ABOVE ABOVE MANUALLY */ // They're ONLY updated in the updateLandVars() function


    // untapped lands (lands that can still produce mana). In other words, these vars determine how many more creatures and oneshots I can cast
    int rUntapped = 0;
    int wUntapped = 0;
    int dualsUntapped = 0;
    int untappedLands = 0;

/** 'xUntapped' vars are decremented manually only to pay for mana costs, and ONLY incremented or set directly in updateLandVars function */


/** Goldfish.cpp */
    // run() is public, at the top of the file

    // reset game state for a new game
    void reset();

    // run one instance of a Magic game. Every game action or game logic func originates from here, or a func normalGame called.
    int normalGame();



/** goldfish_cardData */
    // splits a full cost like `1RR` into component variables
    Card splitCost(string);

    // genCardData() takes some variables and splits them into sub-variables. Directly updates the card passed in the argument
    void genManaData(Card& cardname);

    // readCardData takes the name of the card you want, and returns all the relevant data
    Card readCardData(const string& cardname);



/** goldfish_fileFuncs */
    // read a deck from file and turn it into a Library object
    bool readDeckFromFile();

    // export your stashed log strings and output them to a file
    void exportToFile();

    // dumps all current logs to a dump thread and then calls exit()
    void crash(string);


/** goldfish_gameFuncs */
    // removes top card of your Library and adds it to Hand
    void drawCard();

    // update variables "X tapped" ints to their counterpart of "all of X, tapped and untapped"
    void untapStep();

    // simulate combat (all creatures deal damage equal to their power to the opponent)
    void combatStep();

    // randomize your library order
    void shuffleLibrary();

    // discard a card according to logic (which card is least useful)
    void discardCard();

    // try to play a creature or oneshot, respectively. Returns whether successful
    bool tryCreature();
    bool tryOneshot();



/** goldfish_interface */
    // get and return a user-inputted bool value
    bool askYN(const string&);

    // get and return a user-inputted int
    int askInt(const string&);

    // get user input between low and high
    int askInt(const string&, const int& low, const int& high);

    // log your Hand to the log object
    void logHand();

    // display menu after simulation finished
    void resultsMenu();

    // display menu for sorting your results
    void sortResultsMenu();

    // couts an overview of all games played, one game per line
    void printOverview();



/** goldfish_landFuncs */
    // tries to play a Plains or Mountain, respectively. Returns whether successful
    bool tryPlains();
    bool tryMountain();

    // traverse all lands you've played and update all the land variables
    void updateLandvars();

    // return whether you can pay the specified mana cost
    bool payMana(string manaToPay);
    bool payMana(Card);

    // search your library and get a land depending on logic. Returns whether successful
    bool fetch();

    // runs logic of "which land should I play?" Returns whether a land got played
    bool landLogic();

    // play a specified card. Assumes you have it in your hand and calls crash() if you don't
    void playLand(Card, bool);
    void playLand(string, bool);


};


#endif //GOLDFISH_GOLDFISH_H
