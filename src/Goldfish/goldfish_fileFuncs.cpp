//
// Created by alexw on 12/5/2022.
//

#include "Goldfish.h"
// the functions that read from and write to files

bool Goldfish::readDeckFromFile() {
/* Return values: if deck read successfully, true, if read unsuccessfully, false
 *
 *
 * This function prompts user for file and tries to read it
 * If invalid deck, returns false (instead of crashing) so the function that called it can see the false return value
 *  and prompt the user to choose a new deck
 *
 * Time complexity: O(n), where n is number of lines in the file to be read
 *
 */

    namespace fs = std::filesystem;
//    cout << fs::current_path() << endl;


    // directory_iterator can be iterated using a range-for loop
    string deckpath = "decks";
    string fancypath;
    int i = 0;
    for (const auto& index: fs::directory_iterator(deckpath)) { // list all decks
        if(index.path().extension() != ".txt") continue; // skip files that don't have a .txt extension
//        fancypath = index.path().stem();
        i++;
        cout << i << ") " << index.path().stem() << endl; // cout just the filename, no extension or `/deck/`

    }
    cout << " " << endl;
    int selectedDeck = askInt("What deck would you like to run? ", 1, i); // index of selected deck
    // needs to query after, so it knows how many entries it has
    int j = 0;
    int found = false;
    string filepath;
    selectedDeck--; // compensate for displaying thing 1 higher
    for (const auto& index: fs::directory_iterator(deckpath)) { // this loop finds the right deck
        if(j == selectedDeck) {
            found = true;
            deckname = '"' + index.path().stem().string() + '"'; // wrap deckname with quotes to make it more clear it's a user-inputted value
            filepath = index.path().string();                    // in case they make it obscene or something lol
        }
        j++;
    }

    if(!found) crash("invalid deck filepath, couldn't find file");
    ifstream fileInput;

    fileInput.open(filepath, ios::in);
    string displaypath;
    cout << "opening deck from " << filepath << endl << endl;
    string line;
    int currline = 0;

    int lands = 0;
    int nonlands = 0;

    if(fileInput.is_open()) {
        Card curr;
        while (getline(fileInput, line)) {

            if(currline == 60) {
                // There should always be exactly 60 cards in deck

                cout << "Deck error: Too many cards in deck, should be " << to_string(60) << endl;
                return false; // return, to give the user a chance to use a new deck

            }
            if(line[0] == '#') continue; // ignore comments in deck file
            if(line == "") continue; // ignore blank lines
            try {
                curr = readCardData(line); // this func will throw() if it gets passed an invalid card name
            }
            catch(...) {
                return false; // so this try/catch ensures that it will be caught and prompt the user to choose another deck
            }


            if(curr.type == Card::land) lands++;
            else nonlands++; // if it's not a land, its a nonland

            deck[currline] = curr; // add card name to the deck object

            currline++;


        }
        if(currline != 60) {
            cout << "Deck error: Too few cards in deck, should be " << to_string(60) << endl;
            return false;
        }



        else if(nonlands < 10) {
            cout << "Deck error: Too few nonlands in deck, should be minimum 10" << endl;
            return false;
        }

        // Each deck needs to have at least 10 lands and 10 nonlands
        // this isn't a requirement for paper magic, but this helps ensure that unwinnable decks don't accidentally get tested

        else if(lands < 10) {
            cout << "Deck error: Too few lands in deck, should be minimum 10" << endl;
            return false;
        }



        fileInput.close();
        return true;
    }
    else {
        cout << "unable to open file" << endl;
        return false;
    }
}

void Goldfish::exportToFile() {
/* Exports data of the user's choice to the export file. File is named `results.txt` and located in the folder `/results/`
 * Overwrites the old content of the file, and creates a new file if no matching file is found.
 *
 *
 * Time complexities:
 * case 1: O(n) where n is amount of games played
 * case 2: O(n) where n is distance traversed in gamesPlayed list to get to the game to print
 * case 3: O(n) where n is amount of messages logged
 * case 0 and default case: constant
 *
 */


    string menu =
            "\nWhat data would you like to write to the log file? \n"
            "<1> Log overview \n"
            "<2> Log specific game \n"
            "<3> Log everything \n"
            "<0> Return \n"
            "Enter your selection: ";

    int menuSelection = askInt(menu, 0, 3);

    ofstream fileOutput;
    string filepath = "results/results.txt";
    fileOutput.open(filepath, ios::out);
    int turns, gamenum, cplays, oplays, misses, t1m;

    int var = 0; // for stuff inside the switchcase to use
    string q;
    int len = allGamesResults.getLength();
    LinkedQueue<GameResult> temp = allGamesResults; // linear time complexity of allGamesResults length
    bool found = false;
    float totalturns = 0; // so it shows a decimal
    if(fileOutput.is_open()) {
        switch(menuSelection) {
            case(1): // write overview to file

            cout << "Logging overview to file" << endl;

                fileOutput << "Deck used: " << deckname << endl;
                fileOutput << "Overview of games:" << endl;
                fileOutput << " GameNum      Turns     Creatures    Oneshots    MissedLands " << endl;
                for (int i = 0; i < len; i++) { // display all games and their results

                    gamenum = temp.front().getGameNumber();
                    turns = temp.front().getWinturns();
                    cplays = temp.front().getCreaturesPlayed();
                    oplays = temp.front().getOneshotsPlayed();
                    misses = temp.front().getMissedLandDrops();
                    t1m = temp.front().getMissed_t1();





                    totalturns += turns;
                    temp.dequeue();


                    fileOutput << setw(6) << right <<
                         gamenum << setw(12) <<  turns  << setw(12) << cplays << setw(12) << oplays << setw(12) << misses <<endl;

                }
                fileOutput << " GameNum      Turns     Creatures    Oneshots    MissedLands " << endl;
                fileOutput << "\ntotal turns: " << totalturns << endl;
                fileOutput << "average win turn: " << totalturns/len << endl;





//                // linear for however many games it has to iterate thru to log desired file
//                for (int i = 0; i < len; i++) { // display all games and their results
//                    turns = temp.front().getWinturns();
//                    gamenum = temp.front().getGameNumber();
//                    temp.dequeue();
//
//                    fileOutput << "Game " << setw(GAMENUMWIDTH) << gamenum << " won in " << setw(TURNWIDTH) << turns << " turns" << endl;
//                }


                break;

            case(2):
                var = askInt("which game would you like to log? ", 1, allGamesResults.getLength()); // 'var' is which game to view
                fileOutput << "Deck used: " << deckname << endl;
                fileOutput << "Logged only game " << var << endl; // var is the "display" game number, so no -1

                if(var == 1) { // no need to make a temp array if you're not gonna dequeue anything
                    fileOutput << "\n" << allGamesResults.front() << endl;
                    break;
                }

                temp = allGamesResults;

                for(int i = 0; i < len; i++) { // traverse through list until you find the right game
                    temp.dequeue();

                    if(temp.front().getGameNumber() == var) { // you can't rely on it being in any particular order
                        fileOutput << "\n" << temp.front();
                        found = true;
                        break;
                    }
                }
                if (!found) crash("resultsMenu() case 2: game not found"); // should have found, if not, bugged
                break;

            case(3): // log everything
                cout << "Logging everything to file" << endl;
                fileOutput << "Logging overview + all games to file" << endl;
                fileOutput << "Deck used: " << deckname << endl;
                fileOutput << "Overview of games:" << endl;
                fileOutput << " GameNum      Turns     Creatures    Oneshots    MissedLands " << endl;
                for (int i = 0; i < len; i++) {
                    gamenum = temp.front().getGameNumber();
                    turns = temp.front().getWinturns();
                    cplays = temp.front().getCreaturesPlayed();
                    oplays = temp.front().getOneshotsPlayed(); // THIS LOOP LOGS THE
                    misses = temp.front().getMissedLandDrops();
                    totalturns += turns;
                    temp.dequeue();
                    fileOutput << setw(6) << right <<
                         gamenum << setw(12) <<  turns  << setw(12) << cplays << setw(12) << oplays << setw(12) << misses <<endl;
                }
                fileOutput << " GameNum      Turns     Creatures    Oneshots    MissedLands " << endl;
                fileOutput << "\ntotal turns: " << totalturns << endl;
                fileOutput << "average win turn: " << totalturns/len << endl;


                temp = allGamesResults;
                fileOutput << "\n\n\n\n" << endl;

                // Time complexity: O(n) where n is the total amount of all strings logged so far
                for(int i = 0; i < len; i++) {
                    turns = temp.front().getWinturns();
                    gamenum = temp.front().getGameNumber(); // WRITE ALL GAMES' FULL DETAILS TO FILE
                    fileOutput << "\n\n===========================================================================\n";
                    fileOutput << "\t\t\t\t\t   GAME " << gamenum << " won in " << turns << " turns" << endl;
                    fileOutput << temp.front() << "\n"; // printing a GameResult object prints the whole game
                    temp.dequeue();
                }
                break;

            case(0):
                fileOutput.close();
                return;

            default:
                fileOutput.close();
                crash("error in exportToFile(): invalid input acquired, hit default switchcase");
        }



        fileOutput.close();
        cout << "\nResults successfully logged to file" << endl;
        return;
    }

    cout << "unable to open log file" << endl;


}

void Goldfish::crash(string errorMsg) {
/* Arguments: error message. Displayed to console, as well as added to the log file
 *
 * ahh you've gotta love when you make a function specifically for crashing your entire program
 * Everywhere I call this, there used to be `string e = error message; cout << e; throw(e);`
 * but that ended the program too fast and didn't let me see all the log files stored up, so I made this
 *
 * This spits every log present into a dump file, and then crashes the program.
 * It overwrites old dump file, if present, and creates a new dump file if one isn't found.
 * Dump file named '_dumpthread.txt' and located in /results/.
 *
 * Time complexity:
 * O(n) where n is total amount of log entries
 *
*/


    string bar = "  =====================  ";
    string header = "\n\n\n" + bar + "CRASHING" + bar; // this was surprisingly fun to code
    thisgame.log(header);

    thisgame.log(errorMsg); // log the error message
    allGamesResults.enqueue(thisgame); // add the last game to the allGamesResults list

    ofstream fileOutput;
    string filepath = "results/dumpthread.txt";
    fileOutput.open(filepath, ios::out);

    int len = allGamesResults.getLength();

    if(fileOutput.is_open()) {
        for(int i = 0; i < len; i++) {
            fileOutput << allGamesResults.front() << "\n";
            allGamesResults.dequeue();
            // dumps every single game message from every single game you simulated into the output file

        }


        fileOutput.close();

    }
    else {
        cout << "unable to open dump file" << endl;
    }
    cout << errorMsg << endl; // print error message to console
    exit(3);
}

