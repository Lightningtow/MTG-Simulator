//
// Created by alexw on 11/18/2022.
//

#ifndef GOLDFISH_GAMERESULT_H
#define GOLDFISH_GAMERESULT_H

#include "queue/ArrayQueue.h"
#include "queue/LinkedQueue.h"
#include "stack/LinkedStack.h"
#include "Card.h"
#include "list/LinkedList.h"

class GameResult {
/*
 * The GameResult class's purpose is to provide a container for many strings,
 *    keeping track of the object that will become the log file.
 * It also keeps track of variables for each game, such as how many turns it was won in, and in what order they were simulated.
 *
 * Its functions are limited to getters, setters, comparison overloads, and a few tools to manage the data contained within it.
 *
 * One GameResult object holds the results of one specific game. Each instance of this object corresponds to exactly one game.
 * Goldfish.h makes a linked list of GameResult objects, to keep track of all the games.
 *
 */

public:


    void log(const string&); // this adds a log entry to gameActions


    int getLength();
    bool isEmpty();
    void reset();


    // setters
    void setGameNumber(int);
    void setTurnsToWin(int);


    // incrementers
    void incCreaturesPlayed();
    void incOneshotsPlayed();
    void incMissedLandDrops();
    void incMissedTurnOneLands();


    // getters
    int getGameNumber() const;
    int getCreaturesPlayed() const;
    int getOneshotsPlayed() const;
    int getMissedLandDrops() const; // each turn, if you didn't play a land, this is incremented
    int getMissed_t1() const; // on turn 1, if you didn't play a land, this becomes 1
    int getWinturns() const;

    int getStat(int) const;

    // overloads
    bool operator>(const GameResult&) const;
    bool operator>=(const GameResult&) const;
    bool operator<(const GameResult&) const;
    bool operator<=(const GameResult&) const;
    friend ostream& operator<<(ostream& outStream, const GameResult& obj);


private:
//    int GAME_STAT_LEN = 6; // length of the gameStat array

//    int gameStats[6] = {0, 0, 0, 0, 0, 0};

    int gamenum = 0;
    int creaturesPlayed = 0;
    int oneshotsPlayed = 0;
    int missed_land_drops = 0;
    int missed_t1 = 0;
    int winturns = 0;


/*
 What gameStats refers to:
 0: game number
 1: creatures played
 2: oneshots played
 3: missed land drops (how many turns you didn't play a land)
 4: missed turn 1 land drops (if you didn't play a land on turn 1, so it's either 0 or 1)
 5: how many turns it took to win



The reason I combined these into an array instead of individual variables is so I could access by subscript, like `cout << gameStats[num]`.
In other words, I can make one function do all 6, without a bunch of checks inside like `if(selection == gameNumber)`, etc.


 Note that the GameResult class is instantiated once per game simulated, so the above variables are only for one instance of a game,
    and not a running total of accumulated stats from all games.
*/




    LinkedQueue<string> gameActions; // a list of literally everything I want to log
    // LinkedQueue so I have direct access to the end of the list, so constant time complexity to log stuff

    // GameActions is usually used for stuff like "played a Mountain,"
    //  but if debug mode is enabled, used for debugging purposes like documenting logic flow and printing variables.

    // It'd log stuff as "trying to play a mountain, no mountain played" or "paid for this mana cost using 1 dual and 1 mountain"




};


#endif //GOLDFISH_GAMERESULT_H
