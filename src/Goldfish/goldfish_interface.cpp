//
// Created by alexw on 11/19/2022.
//

#include "Goldfish.h"
// note that not every function that displays text or asks for input is here
// this is just where much of it is

bool Goldfish::askYN(const string& query) {
/* Arguments: query (string message to prompt the user with)
 * Return value: true or false depending on whether the user entered true or falce
 *
 * This function gets user input, wants boolean answer, y/Y/1, n/N/0
 * If invalid input, asks again and reprompts
 *
 * Time complexities:
 *  Minimum (and likely average): constant, if the user enters valid input first try
 *  Maximum: O(n) where n is the amount of times the user enters invalid input
 *
 *
 */
    string inputcstr;
    cout << query;
    while(true) {
        getline(cin, inputcstr);
        string input(inputcstr);
        if(input == "FORCEQUIT") {
            cout << "Force quitting" << endl;
            exit(1);
        }

        if(input == "y" || input == "Y" || input == "1") return true;

        else if (input == "n" || input == "N" || input == "0") return false;

        else {
            cout << "invalid input, please enter any of: y, Y, n, N, 1, 0  ";
        }
    }


}
int Goldfish::askInt(const string& query) {
/* Arguments: query (string message to prompt the user with)
 * Return value: the user-inputted integer
 *
 * Gets user input, any valid int works
 * If the user enters invalid input, shows error and asks again
 *
 *
 * Time complexities:
 *  Minimum (and likely average): constant, if the user enters valid input first try
 *  Maximum: O(n) where n is the amount of times the user enters invalid input
 *
 *
 */
    string inputcstr;
    cout << query;
    int newint;
    while(true) {
        getline(cin, inputcstr);
        string input(inputcstr);
        if(input == "FORCEQUIT") {
            cout << "Force quitting" << endl;
            exit(1);
        }

        if((input.find_first_not_of( "0123456789" ) == std::string::npos)) { // if has only digits
            newint = stoi(input);
        }
        else {
            cout << "Invalid input, please enter a positive integer" <<  endl;
            continue;
        }

        return newint;
    }







}
int Goldfish::askInt(const string& query, const int& low, const int& high) {
/*
 * Arguments: query (string message to prompt the user with), low (minimum accepted value), high (maximum accepted value)
 * Return value: the user-inputted int
 *
 * Asks for and returns user input, an integer between `low` and `high`
 * asks for user input and reprompts if the user enters invalid input
 *
 * Time complexities:
 *  Minimum (and likely average): constant, if the user enters valid input first try
 *  Maximum: O(n) where n is the amount of times the user enters invalid input
 *
 *
 */
    string inputcstr;
    cout << query;
    int newint;
    while(true) {
        getline(cin, inputcstr);
        string input(inputcstr);
        if(input == "FORCEQUIT") {
            cout << "Force quitting" << endl;
            exit(1);
        }


        if((input.find_first_not_of( "0123456789" ) == std::string::npos)) { // if has only digits
            newint = stoi(input);
        }
        else {
            cout << "Invalid input, please enter a positive integer" <<  endl;
            continue;
        }


        if(newint < low || newint > high) { // this includes low and high
            cout << "Please enter an integer between " << low << " and " << high << ": ";
        }
        else return newint;

    }





}

void Goldfish::resultsMenu() {
/* ResultsMenu (and the funcs it calls, for sub-menus) is responsible for all the text menus after the simulation has finished.
 * This can be considered the main() for after you're done simulating. All sub-menus return to this one.
 *
 *
 * Time complexities:
 *  case 0: constant
 *  case 1: O(n) where n is number of games simulated
 *  case 2: O(n) where n is size of allGamesResults, plus amount of games to dequeue till the chosen one is at the front
 *  case 3: see exportToFile(). Summary: all cases are linear
 *  case 4: see sortResultsMenu(). Summary: cases are minimum O(n), and average and maximum O(n^2)
 *
*/
    while(true) {
        string menu = //"How would you like to view your results? \n"
                "\n<1> View overview \n"
                "<2> View specific game \n"
                "<3> Log results to file \n"
                "<4> Sort results \n"
                "<0> Exit Program \n"
                "Enter your selection: ";

        int menuSelection = askInt(menu, 0, 4);
        int gameToView;
        int len = allGamesResults.getLength();
        LinkedQueue<GameResult> temp; // declared here so it can be initalized later
        bool found = false;
        switch (menuSelection) {
            case (1): {
                printOverview(); // O(n) where n is number of games simulated
                break;

            }
            case (2):
                gameToView = askInt("which game would you like to view? ", 1, allGamesResults.getLength());
                cout << "Displaying game " << gameToView << endl; // var is the "display" game number, so no -1

                if(gameToView == 1) { // no need to make a temp array if you're not gonna dequeue anything
                    cout << "\n" << allGamesResults.front() << endl;
                    break;
                }

                temp = allGamesResults; // this and loop both linear


                for(int i = 0; i < len; i++) { // traverse through the whole list
                    temp.dequeue();

                    if(temp.front().getGameNumber() == gameToView) { // cant rely on it being in any particular order, due to sorting
                        cout << "\n" << temp.front() << endl;
                        found = true;
                        break;
                    }
                }
                if(!found) crash("error in resultsMenu() case 2: game not found"); // should have been found by end of loop, if not, bugged
                break;


            case(3):
//               // if called multiple times, exportToFile() overwrites old files
                exportToFile(); // all cases are O(n), excluding the 'return to function that called this' case
                break;

            case(4):
                sortResultsMenu(); // has multiple cases but average is O(n^2)
                break;

            case (0):
                exit(0);

            default:
                crash("error in showResults(): invalid input from menu, hit default switch case");

        }

    }

}
void Goldfish::sortResultsMenu() {
/*
 * this just sorts the allGamesResults list, doesn't display anything
 *
 * all switchcases that sort stuff are identical, except for what they compare
 *
 * Time complexities:
 *  case 0: constant
 *  all other cases are insertion sorts, so:
 *       best case: already sorted, O(n)
 *       average and worst case, O(n^2)
 *
*/

    string menu =    "\nHow would you like to sort your games? \n"
                     "<1> Sort by chronological order \n"
                     "<2> Sort by how many turns it took to win \n"
                     "<3> Sort by creatures played \n"
                     "<4> Sort by oneshots played \n"
                     "<5> missed total drops \n"
                     "<6> missed turn 1 drops \n"
                     "<0> Return \n"
                     "Enter your selection: ";

    int sortmode = askInt(menu, 0, 6);

    int arrIndex = 42; // which array index to access for gameActions array
/*
what getStat refers to
 1: gamenum
 2: winturns
 3: cs played
 4: oneshots played
 5: missed total drops
 6: missed t1 drops
*/
    bool reversed = false;
    // Necessary because for chronological, we want game 1 -> game 100, but for
    //    creatures played, we want most creatures played -> least creatures played
    // If not for this bool, some would be sorted backwards, which is suboptimal
    switch(sortmode) {
        case 0: return;
        case 1: arrIndex = 1; reversed = true; break; // gamenum
        case 2: arrIndex = 2; reversed = true; break; // winturns
        case 3: arrIndex = 3; break; // creatures
        case 4: arrIndex = 4; break; // oneshots
        case 5: arrIndex = 5; break; // all missed land drops
        case 6: arrIndex = 6; break; // whether missed t1 drop, max value 1
        default: crash("error in sortResultsMenu(): invalid input obtained, hit default switchcase");
    }

    int len = allGamesResults.getLength();

    LinkedQueue<GameResult> temp = allGamesResults;

    vector<GameResult> vec; // using a vector so it has dynamic size and direct access

    for(int i = 0; i < len; i++) {
        vec.push_back(temp.front()); // copy allGamesResults to vector, via a temp stack
        temp.dequeue();
    }

    int t = 0;
    GameResult swaptemp;
    GameResult curr;



    for(int i = 0; i < len-1; i++) { // insertion sort
        t = i;
        for(int j = len-1; j > i; j--) {
            if(!reversed) {
                if(vec[j].getStat(arrIndex) > vec[t].getStat(arrIndex)) t = j; // sort in normal order

            }
            else {
                if(vec[j].getStat(arrIndex) < vec[t].getStat(arrIndex)) t = j; // else sort in reversed order
            }
        }
        if(i != t) {

//            if(debugging) cout << "swapping " << i << " & " << t << endl; // log doesn't work, since no current goldfish object
            swaptemp = vec[i];
            vec[i] = vec[t];
            vec[t] = swaptemp;

        }
    }


    allGamesResults.clear();
    for(int i = 0; i < len; i++) { // copy temporary vector back to allGamesResults
        allGamesResults.enqueue(vec[i]);
    }


}

void Goldfish::logHand() {
/* Enters your current hand into the log.
 * It logs as one big entry, instead of one entry per card, to save on overhead.
 *
 * Time complexity: O(n) where n is number of cards in hand7
 *
 */
    string s = "Hand:";
    for(int i = 0; i < hand.getLength(); i++) {
        s += "\n\t ";
        s += hand.getElement(i).name;
//                cout << hand.getElement(i).name << endl;

    }
    thisgame.log(s); // so your whole hand is one log entry, not N entries
}

void Goldfish::printOverview() {
/* Prints a one-line overview of each game, and doesn't print any details beyond gameNum and winTurns.
 *
 * Time complexity: O(n) where n is the number of games played
 *
 */
    cout << "\nOverview of all games: \n" << endl;
//    cout << left;
    int turns, gamenum, cplays, oplays, misses, t1m;
    int len = allGamesResults.getLength();
    LinkedQueue<GameResult> temp = allGamesResults;
    float totalturns = 0; // so it can show a decimal
    cout << " GameNum      Turns     Creatures    Oneshots    MissedDrops " << endl;
    for (int i = 0; i < len; i++) { // display all games and their results

        gamenum = temp.front().getGameNumber();
        turns = temp.front().getWinturns();
        cplays = temp.front().getCreaturesPlayed();
        oplays = temp.front().getOneshotsPlayed();
        misses = temp.front().getMissedLandDrops();
        t1m = temp.front().getMissed_t1();





        totalturns += turns;
        temp.dequeue();


        cout << setw(6) << right <<
        gamenum << setw(12) <<  turns  << setw(12) << cplays << setw(12) << oplays << setw(12) << misses <<endl;

    }   cout << " GameNum      Turns     Creatures    Oneshots    MissedLands " << endl;

//    cout << setw(6) << right << "gamenum" << setw(12) << right << "winturns" << setw(12) << "creatures" << setw(12) << "oneshots" << endl;
    cout << "\ntotal turns: " << totalturns << endl;
    cout << "average win turn: " << totalturns/len << endl;

}


