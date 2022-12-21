


# Magic: The Gathering Simulator  
## Introduction
Magic: The Gathering is a tabletop card game where two people play against each other using 60-card decks. Each player starts
at 20 life and tries to reduce the other player to 0 life as quickly as possible. 
Much of the challenge of Magic is constructing the best deck, since there are literally thousands of possible cards to play, 
and changing a few cards out for others can have a tremendous impact on how well your deck works. 
Some players test their decks by drawing hands and playing against an empty opponent, seeing how quickly and consistently your deck can win.
This is known as "goldfishing" and helps you determine whether your deck is balanced properly.  

The problem with this, though, is that it takes a very long time, and is very boring. My program solves this problem, by goldfishing for you,
hundreds or even thousands of times, all within just a few seconds. It shows you the results of each game, and can even show you
every single card played and in what order, for each and every one of the games. It can also write those results to a file, 
to be saved and viewed later.

Please note: I've included a file, `crash_couse_magic.md`, which provides the information needed to understand how my program works.

## Overview
The user interface is text-based and straightforward. It prompts you to choose which deck you want to run 
(I provide sample decks), asks you how many times you want to simulate it, and then simulates it that many times for you. Afterwards,
it provides different options for displaying and sorting those results, as well as writing them to files.

I have created three classes: Goldfish, Card, and GameResult. Additionally, I have created a LinkedStack class, located in the `stack` folder. 

Below is a brief overview on the purpose and usages of each class. 
More detailed descriptions can be found in the class documentation, found in the header files.

### GameResult  
The GameResult's purpose is to provide a container for a thousands of strings, holding the object that will later be written to the log file. 
There's also variables for each game, such as how many turns it was won in, and in what order they were simulated. 


### Card  
The main use of the Card class is to create and access Card objects, with each Card representing exactly one Magic: The Gathering card instance. 
The other use for is as an to store multiple related variables, in a container that's easy to pass between functions. 


Note: when I say 'Card', capitalized, in documentation or files like this one, it always refers to a a Card object. If I say 'card', lowercase,
it's usually a more broad reference to Magic: The Gathering cards in general.

### Goldfish  
Far and away the bulk of the code is within the Goldfish class. This class provides all of the infrastructure for simulating Magic games, as well
as all the user interfaces, file reading, file writing, and administrative functions. 
It also holds many variables for keeping track of all of the numerous things that need to be kept track of.   


## Instructions for Professor

1) Set up the program using Makefile by creating a `build` folder and calling `cmake ..` and then `make` from within it, like we did for class.

2) Load up the program via `./goldfish`. It will prompt you to choose a deck. See below for a description of the sample decks that I've included.

3) Enter how many games you'd like to simulate. 

4) The program will simulate that many games for you. Afterwards, it will give you various ways to display and sort the results, 
   as well as allow you to log it to the `results/results.txt` file.

5) You can dump the contents of the results file to your console by navigating to the `results` folder and running `cat results.txt`. However, 
   it may be more convenient to open it manually, using an external application such as Notepad.


From an end-user standpoint, that's pretty much it. All of the complexities are found behind the scenes.
Feel free to create your own deck and try it out! Ensure that it is exactly 60 cards, with at least 10 land cards and 10 nonland cards.
You can find all valid cards and their stats in the function `readCardData()`, located in `goldfish_cardData.cpp`. 
Put the cards you want to run in a text file, one card per line, and put the file in the `decks` folder.



## Sample decks:

I've provided several sample decks, found in the `decks` folder. Decks are formatted one card per line, need to be exactly 60 cards,
and can't contain any unrecognized cards. Note that as of right now, all card names and data are hardcoded into my program, so
there are real Magic cards that my program won't recognize. You can insert comments into deck files by starting the line with `#`.
My program will also completely ignores any file that doesn't have the extension `.txt`.


1) Four decks named `bolt_XX`, where XX is the amount of the card 'Lightning Bolt' it contains.  
   These are designed to show how much important the ratio of
   land to nonland cards is. Lightning Bolt is a classic Magic spell (often referred to as just "Bolt") that
   costs just one red mana and simply deals 3 damage to the enemy. The rest of the deck is filled with the land Mountain.
   For example, `bolt_10` and `bolt_50` will perform very poorly, because they have too many and too few lands,
   respectively. `bolt_30` will perform better, and `bolt_40` is in fact a very powerful deck, and many people actually competed with it in
   Magic: The Gathering tournaments, back in the day.

2) The `bolt_XX` decks only include red cards and lands. To demonstrate multicolor support, I've included `redwhite_sample` which has Bolts,
   as well as Boros Charms. A Boros Charm costs 'RW' and deals 4 damage to the enemy. This deck also includes Arid Mesas,
   which runs the search algorithm when played. `boros_burn` also contains white cards.

3) I also have two full-fledged Magic: The Gathering decks, both of which I'm actually considering making in real life. In fact, my whole
   inspiration for this program comes from wanting to figure out which variation of the deck performs better, before putting money into a deck.
   `boros_burn` is a red and white deck. ("Boros" is a Magic term for "having both red and white colors.") `pauper_monored` is a red-only deck
   without any white in it. ("Pauper" is a certain format of Magic decks, and "monored" means "only red.") These two decks have many different
   card names, and it'd be unreasonable for me to expect you to memorize all of them, which was why I created the sample decks.

4) I've included four invalid test files, to demonstrate my input validation.  
   `_invalid_test_file_1` contains too few cards, `_invalid_test_file_2` contains too many cards, and `_invalid_test_file_3` has an
   invalid card names in the file. All of these decks, if selected within the program to test, 
   will get caught during validation and prompt the user to choose a new deck.
   `very_invalid_test_file.png` is included to show that the file won't be shown in the list of decks to choose from, 
   since it doesn't have a `.txt` extension.






### Other miscellaneous notes:

In all "please enter a value" prompts, entering `FORCEQUIT` will immediately exit the program.

I use C++ 17, to have access to the `filesystem` C++ library, by changing the `CMAKE_CXX_STANDARD` line in `CMakeLists.txt`.


When instructed by the user to do so, the program outputs its logs to `results/results.txt`. Note that the file may be _very_ large. As in,
tens of thousands of lines.

For debugging purposes, if the program logic somehow hits somewhere it's not supposed to, my program will call a function called `crash()`.
The `crash()` function dumps all current log files to `results/dumpthread.txt` and then exits the program.
This is for debugging purposes, and won't happen during normal execution. I wanted a way to detect if the logic was misbehaving, and
simply calling `throw()` or `exit()` didn't work for my purposes, because it didn't allow me to read the logs I had written.

If the `results` folder or the `dumpthread.txt` or `results.txt` files are deleted, the program will generate new ones.

Exit codes:  
0: Successful exit  
1: Manually force stopped by user via entering `FORCEQUIT` as input anywhere  
2: Exited via `exit(2)`   
3: Exited via `crash()`  
Note that both exit codes 2 and 3 will not happen during normal use of my program.
They are only for bugtesting, and are only called in places where the logic flow should not reach, to assist with pinpointing bugs.


### How my program fulfills the project requirements:
Search algorithm: used by fetch lands. See `Goldfish::fetch()`  
Sorting algorithm: used to sort the results. See `Goldfish::sortResultsMenu()`  

Implementation from class: Many ADTs from class are used by my program. The most common is the generic LinkedList, which is used everywhere.  
Recursive implementation: ArrayStack is a recursive implementation of Lab 8. Used for the Library object.  
Different implementation: LinkedStack is a custom stack class using linked lists. Used for the graveyard,
and to keep track of what creatures you've played this game (`fieldCreatures`).

I have over a thousand lines of code in the Goldfish class alone. 
The Card and GameResult classes serve primarily as containers, and are a few dozen lines each.  
The Goldfish class is split into many implementation files, located within the folder `Goldifish`. 
`Goldfish.h` lists what functions are found in each file.   
Additionally, the many ADT class files are sorted into `list`, `queue`, and `stack` folders.

The final report is named `final_report.pdf` and located in the `final-project-Lightningtow` root folder.

All functions in the Card, GameResult, and Goldfish classes are documented with time complexities, as well as return values 
and arguments, if applicable. There are inline comments describing loops and conditionals that may not be obvious at first glance.  
Class-level documentation can be found in `Goldfish.h`, `GameResult.h`, and `Card.h`.


I've also included my attempt at a custom sorting algorithm.  
Halfway through writing the custom algorithm, I realized that the object I was planning on sorting with it wasn't a good object to attempt
to keep sorted, so I scrapped the algorithm. I write about this more in the final report.  
Even though I didn't end up using the sorting algorithm, I think it was a clever way of sorting for collections with only two values, 
and I'm proud of it. I kept a copy in of the algorithm in `sortLibrary.txt`, for potential brownie points.  
