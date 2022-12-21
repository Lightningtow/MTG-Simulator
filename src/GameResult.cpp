//
// Created by alexw on 11/18/2022.
//

#include "GameResult.h"



// reset() wipes all the data
// Time complexity: O(n), where n is amount of actions to clear from gameActions
void GameResult::reset() {

    gamenum = 0;
    creaturesPlayed = 0;
    oneshotsPlayed = 0;
    missed_land_drops = 0;
    missed_t1 = 0;
    winturns = 0;

    gameActions.clear();

}

// Time complexity O(n), where n is the amount of strings the user has logged
ostream& operator<<(ostream &outStream, const GameResult& obj) {
//    outStream << "This game won in " << obj.gameStats[5] << " turns " << endl; // duplicate, similar line printed where this obj is printed
    outStream << "Creatures played: " << obj.creaturesPlayed << endl;
    outStream << "Oneshots played:  " << obj.oneshotsPlayed << endl;
    outStream << "Missed total land drops: " << obj.missed_land_drops << endl;

    bool missedT1 = (obj.missed_t1 == 1);
    outStream << "Missed turn one land drop: " << boolalpha << missedT1 << endl << endl;

    outStream << "All game actions:\n\n" << obj.gameActions;
    return outStream;
}



/// Everything below this line has a constant time complexity



void GameResult::log(const string& input) { // takes the string and adds it as an entry to gameActions
    gameActions.enqueue(input);
}// enqueue is constant time complexity, which is why I use a queue

int GameResult::getLength() { // get how many strings are within the gameActions object
    return gameActions.getLength();
} // in other words, +1 'length' for each time `thisgame.log("msg")` has been called

bool GameResult::isEmpty() {
    return gameActions.isEmpty();
}




// These variables should only ever be incremented by one at a time, and not just set to some random number.
// This is why they're increased via 'incrementers' and not full-blown setters. Provides encapsulation and helps prevent errors.
void GameResult::incCreaturesPlayed() {
    creaturesPlayed++;
}
void GameResult::incOneshotsPlayed() {
    oneshotsPlayed++;
}
void GameResult::incMissedLandDrops() {
    missed_land_drops++;
}
void GameResult::incMissedTurnOneLands() {
    missed_t1++;
}




// setters

void GameResult::setTurnsToWin(int input) {
    if(input <= 0) {
        string e = "error in GameResult::setTurnsToWin(): invalid input, must be greater than zero";
        cout << e << endl;
        exit(2);
    }
    winturns = input;
}
void GameResult::setGameNumber(int input) { // set the number for chronological order in which the games were simulated
    if(input <= 0) {
        string e = "error in GameResult::setGameNumber(): invalid input, must be greater than zero";
        cout << e << endl;
        exit(2);
    }
    gamenum = input;
}


// getters
int GameResult::getGameNumber() const {
    return gamenum;
}
int GameResult::getWinturns() const {
    return winturns;
}
int GameResult::getCreaturesPlayed() const {
    return creaturesPlayed;
}
int GameResult::getOneshotsPlayed() const {
    return oneshotsPlayed;
}
int GameResult::getMissedLandDrops() const {
    return missed_land_drops;
}
int GameResult::getMissed_t1() const {
    return missed_t1;
}

// getStat() exists to give code easier access to a GameResult object.
// Specifically, this was created for use in the sorting algorithm, so the same code can sort by multiple things, without
//    any need for duplicate sorting algorithms, or polluting the code with conditionals checking for 6 different stats.
//

/*
what getStat refers to
 1: gamenum
 2: winturns
 3: cs played
 4: oneshots played
 5: missed total drops
 6: missed t1 drops
*/

int GameResult::getStat(int input) const {
    if(input > 6 || input < 1) {
        string e = "error in GameResult::getStat: invalid input, must be between 1 and 6, inclusive";
        cout << e << endl;
        exit(2);
    }
    switch(input) {
        case 1: return gamenum;
        case 2: return winturns;
        case 3: return creaturesPlayed;
        case 4: return oneshotsPlayed;
        case 5: return missed_land_drops;
        case 6: return missed_t1;
        default: {
            string e = "error in GameResult::getStat(): invalid input obtained, hit default switchcase";
            cout << e << endl;
            exit(2);
        }
    }
}




// All of these comparison overloads just compare the amount of turns it took to win the game
// For example, if game A won in 10 turns and game B won in 5, game A is greater than game B
bool GameResult::operator>(const GameResult& obj) const {
    return (this->winturns > obj.winturns);
}
bool GameResult::operator>=(const GameResult& obj) const {
    return (this->winturns >= obj.winturns);
}
bool GameResult::operator<(const GameResult& obj) const {
    return (this->winturns < obj.winturns);
}
bool GameResult::operator<=(const GameResult& obj) const {
    return (this->winturns <= obj.winturns);
}
