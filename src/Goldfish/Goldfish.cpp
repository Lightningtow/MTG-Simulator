//
// Created by alexw on 11/15/2022.
//

#include "Goldfish.h"
// the "master" functions, so to speak
// imagine run() as the main() of this program, handling UI and file I/O etc, as well as starting the simulation process
// normalGame() is the main() in regards to any given game simulation. Every game action or game logic funcion stems from there.

// reset() is here because it fits best here


void Goldfish::run() {
/* this is the main() function, basically. This is the only public function, and what you use to get the goldfishing process going
 * first it reads your deck from the file and loads it into a Deck object, which is treated as const.
 * It then fills your library using the deck object.
 * It asks some starter info on how to execute the program.
 * Then simulates it that many times. Afterwards, it calls resultsMenu(), which is the func responsible
 *      for managing all the text after the simulation, like "do you want to see results" and "would you like me to dump everything into a file"
 *
 * time complexities:
 * avg/min/max complexity is O(n)
 * normalGame() func is O(n^2). That func is called x times, where x is how many games the user specifies.
 * So it'd total out to O((n^2)*x), which just rounds down to O(n^2)
 *
 *
*/

    std::filesystem::current_path("../");
//    cout << fs::current_path() << endl;
    std::filesystem::create_directories("./results"); // create `results` folder if it doesn't already exist


    bool flag = false;
    while(!flag) {
        flag = readDeckFromFile();
        // this is in a loop for input validation. If the user submits an invalid deck, it'll prompt again
    } // readDeckFromFile() linear, where n is number of lines in file




    for(int i = 0; i < 60; i++) {  // fill library, for the first game
        Card curr = deck[i];                // this later happens in reset();
        library->push(curr); //
    } // linear


//    cout << *library << endl;
    //    q = "Would you like to enable logging?   y/n  "; // we'll just assume that yes they want to log
//    logging = askYN(q);


    debugging = askYN("Would you like to enable extra debug messages?   y/n  ");
    // we'll treat askYN as constant, because it only runs again if the user provided invalid input

    if(!debugging) thisgame.log("        Debugging was disabled, some extra info was not collected");

    float totalturns = 0;
    int runCount = askInt("How many times would you like to run the simulation? ", 1, 1000);
    // get how many times to run the simulation. 1k is around where it starts taking a few seconds to simulate it all

    /* if(runCount > 100) */ cout << "\nSimulating..." << endl; // high numbers can cause a noticeable delay



    GAMENUMWIDTH = (to_string(runCount).length()); // this is the only place this is set. Formats 'overview' strings to have correct width

    float winturn;
    for(int i = 0; i < runCount; i++) { // simulate the game a few hundred times (or whatever the user inputs)
        winturn = normalGame(); // normal game is O(n^2), where n is the amount of cards in your library (60)
        totalturns += winturn;
        thisgame.setGameNumber(i+1); // +1 so it starts at correct number
        thisgame.setTurnsToWin(winturn);

        if(winturn >= 10) TURNWIDTH = 2; // if game won in double-digit turncount, add an extra space to 'overview' strings
        reset();
    }


    cout << "\ntotal turns: " << totalturns << endl;
    cout << "average win turn: " << totalturns/runCount << endl; //yes this is a decimal. It's a feature, not a bug


    if(logging) {
        resultsMenu();
    }


}

int Goldfish::normalGame() {
/* returns how many turns it took the program to win this game
 *
 *
 * This is the 'main' function, for gameplay logic. It's where the all of the simulation logic starts from.
 *
 * First off, it untaps all your stuff and draws a card.
 * It play as many creatures as possible, and then plays as many oneshots as possible.
 * Assuming there's a creature on the battlefield, it'll run combat.
 * At the end of its turn, it will discard cards back down to 7 cards in hand, if necessary.
 *
 * time complexity:
 * average, min and max O(n^2): where n is the number of cards in your library, due to shuffleLibrary()
 *
 * shuffleLibrary() is exponential, and everything else is linear.
 *
 * shuffleLibrary() is called exactly once for each call of this function, so:

 *
*/


    shuffleLibrary();
    // shuffling is necessary because at first, the library is in the same order as the file reads it in
    // and the func needs to be inside the playGame func so the order is different every game


    for(int i = 0; i < 7; i++) drawCard();  // draw seven cards, for your opening hand


    int currentTurn = 0;
    bool flag;

    while(true) { // each iteration is one turn. This loop continues until you win the game.
        // If you would lose, instead crash() is called, since there's no reason you would lose, so it's a bug

        currentTurn++;
        // increment currentTurn at beginning and not end of loop, so it starts at 1 and don't have to compensate later

        if(logging) thisgame.log("\nTurn " + to_string(currentTurn) + ") "); // log the beginning of each turn

        untapStep(); // untap everything on the battlefield
        // both untap and drawcard are constant
        drawCard(); // draw a card at the beginning of your turn

        // post project: upkeep and mainOne


        if(debugging) logHand(); // log your hand at the beginning of every turn.
        // Probably unnecessary for normal use but good for debugging




        /** main phase start */
        // in magic, the first thing you do on your turn is play a land, if possible
        bool playedland = landLogic(); // try to play a land.

        // landlogic and updateLandvars are both linear

        if(playedland) {
            updateLandvars();  // update your land variables if you played a land
        }

        else { // if you weren't able to play a land, log extra stuff
            if(logging) {
                thisgame.incMissedLandDrops();
                if(currentTurn == 1) thisgame.incMissedTurnOneLands();
            }

        }


//        if(debugging)thisgame.log("Lands out: " + to_string(rLandsOut) + "|" + to_string(wLandsOut));

        flag = true;
        while(flag) { // cast creatures until there's no more creatures to cast or mana runs out, whichever happens first
            flag = tryCreature();
            if(untappedLands == 0) flag = false;
            // if you don't have any untapped lands, you have no way of paying for cards
            // this check keeps you from fruitlessly traverse your entire hand looking for another card to play
        }

        // tryCreature and tryOneshot are both linear

        flag = true;
        while(flag) { // and then cast as many oneshots as possible.
            flag = tryOneshot();
            if(debugging && flag) thisgame.log("oneshot played");
            if(debugging && !flag) thisgame.log("no oneshot played");

            if(untappedLands == 0 || enemylife <= 0) flag = false;
            // similar check for if you're out of mana
            // also, if enemy is dead, no point to running all the function calls required to keep dealing damage to a already-dead enemy
            // this particular enemyLife check only breaks out of this loop, logging result exiting this func happens below

//            if(flag && logging) thisgame.log("\t\t" + to_string(enemylife) + " ");

        }
        /** main phase ends */

        if(enemylife <= 0) {
            // check if enemy is beat. I do this once here, before combat,
            // because an unnecessary combat takes longer than one conditional check

            if(logging) thisgame.log("WON ON TURN " + to_string(currentTurn));
            // no need to set thisgame.turnsToWin, that is done up a level using this func's return level
            return currentTurn; // return how many turns you won in

        }


        if(!fieldCreatures.isEmpty()) combatStep(); // if there's no creatures on the battlefield, skip combat step
        // combat phase is linear


        if(logging) thisgame.log("\t\tEnemy life: " + to_string(enemylife)); // log enemy life at end of turn


        if(enemylife <= 0) { // if enemy is at or below 0 life, congrats! you win


            if(logging) thisgame.log("WON ON TURN " + to_string(currentTurn));
            // no need to set thisgame.turnsToWin, that is done up a level using this func's return level

            return currentTurn; // return how many turns you won in

        }

//        crash("test");

        // in MTG, the maximum hand size is seven
        // the way it works is that you can have any amount of cards in your hand during your turn
        // but at the emd of your turn, you need to discard back down to seven cards in your hand
        // so this loop discards you back down to seven
        if(hand.getLength() > 7) {
            int cardsToDiscard = hand.getLength()-7;
            if(debugging) thisgame.log("Hand size is " +to_string(hand.getLength()) + ""
                                      ", needs to discard " +to_string(cardsToDiscard)+ "cards");

            if(logging) thisgame.log("Hand size over 7, discarding " +to_string(cardsToDiscard) + " cards");
            // the names of discarded cards are logged within the discardCard() function, not here
            for(int i = 0; i < cardsToDiscard; i++) {
                discardCard();
            }
        } // right now, this loop is only linear, because even worst case scenario where you couldn't play a single card, you're
        // only going to have to discard one card.


    }


    string e = "error in normalGame(), logic is flawed somehow \n"
               "the function didn't terminate like it was supposed to \n"
               "it somehow made it past a while(true) loop....?        Kinda impressive ngl";
    crash(e);

    return 42;  // yay for life, the universe, and everything

}

void Goldfish::reset() {
/* resets all variables and clears all list structures
 *
 * time complexity:
 * avg/min/max: O(n) where n is every element in all lists that needs to be cleared
 */


    if(!thisgame.isEmpty()) { // if there's stored game data
        allGamesResults.enqueue(thisgame); // push results to allGamesResults
        thisgame.reset();
    }

    // reset everything
    hand.clear();
    library->clear();
    graveyard.clear();
    fieldLands.clear();
    fieldCreatures.clear();

    landsInHand = 0;
    plainsInHand = 0;
    fetchesInHand = 0;
    mountainsInHand = 0;

    updateLandvars(); // reset land variables


    for(int i = 0; i < 60; i++) { // refill library from the [treated as] const Deck object
        Card curr = deck[i];
        library->push(curr);
    }


    // reset current count of lands in library, to total amount of lands in unedited deck
    dualsInLibrary = TOTALDUALS;
    plainsInLibrary = TOTALPLAINS;
    mountainsInLibrary = TOTALMOUNTAINS;


    enemylife = 20;


}
