//
// Created by alexw on 11/16/2022.
//

#include "Goldfish.h"
// the functions that directly have to do with obtaining mana data and returning it

Card Goldfish::splitCost(string cost) {
/* Return value: multiple variables packaged within a Card object
 * Arguments: the 'cost' string to be split up, like '2RW' or 'R'
 *
 * This takes a cost string and splits it into multiple variables like mana value, amount of red pips, etc.
 * Then returns those variables, packaged up in a Card object but it's just a package.
 * That card is incomplete, and trying to play it would cause bugs.
 * This simply functions as a way to easily split the display cost into easy to access variables.
 *
 * Time complexity: constant
 *
*/
    Card c;
    genManaData(c);
    return c;
}

void Goldfish::genManaData(Card& c) {
/* Data returned: multiple variables providing info on mana costs. Returned via the argument, which is passed by reference
 * Variables returned: redneeded, whiteneeded, genericNeeded, and mana_value
 * Arguments: a Card object containing a full cost string like '3W' or 'R'
 *
 * Time complexity: constant
 *
 * More details on the logic behind this, below

 First off, to understand this, you need to understand how mana costs work. See crash_course_magic.md for a description of mana costs
  I won't describe mana costs here. Markdown and pictures make for better explanations than plain text.

 Function usage: this function is a little bit weird, because it's called and used for two different things.
 Both usages take a card by reference as the argument, and then update variables within the card.

1) Usage one is called in readCardData.
    readCardData only provides info that differs from card to card, in order to minimize as much hardcoding as possible.
    Mana costs work the same for each and every card, so there's no point to putting additional info in readCardData.
    The only mana-related thing that readCardData provides is the full cost .It then calls this function to flesh out the card and
     provide more necessary information. In this case only, is the resulting card complete, and safe to play


2) The second usage is to take a display cost string like 1RR, and break it into variables.
 For example:
 Upon receiving '2RW' as an argument it would fill the card object with:
    mana value: 4
    generic mana: 2
    red pips: 1
    white pips: 1

 For a more relevant example, most cards in this deck just cost 'R'
 In that case, it would populate these variables with the data:
    mana value:1
    generic: 0
    red pips: 1
    white pips: 0

 The object's variables are not filled out beyond those listed above.
 This means that if you tried to play that card, you'd mess things up and would it crash or misbehave.
 It won't even have a card name, much less a creature/land/oneshot type or any of that.
 This function's sole purpose is to slice up the display cost into its smaller chunks and return them via reference,
    to be accessed by whatever calls this.



 The function does exactly the same thing regardless of which 'usage' you're doing, but
  the point is that depending on the situation in which it's called, results vary as to whether the returned card object is safe to play.

 It rarely is btw, any call outside of this file is most likely just used as
  "hey I have a displaycost of XYZ, I'm gonna send it to genManaData to get how many red pips are needed."

 Time complexity: constant
*/


    string edit = c.displaycost; // a string for the display cost, so you can iterate through it
    int len = c.displaycost.length();
    int total = 0;


    for(int i = 0; i < len; i++) {
        if(edit[i] == 'R') {
            c.redneeded++;
        }
        else if (edit[i] == 'W') {
            c.whiteneeded++;
        }
        else {
            try {
                char j = int(edit[i] - '0'); // get generic value from displaycost string
                total *= 10;
                total += j; // generic costs in the double digits do exist (although they're extremely rare)
                // so it's good to have multi-digit support
            }
            catch(...) {
                crash("error in genCardData: mana cost included invalid digits");

            }
        }
    }
    c.genericNeeded = total;
    c.mana_value = c.redneeded+ c.whiteneeded + c.genericNeeded; // set the mana value

}

Card Goldfish::readCardData(const string& nametest) {
/* Argument: a string of a cardname, such as "Lightning Bolt" or "Mountain"
 * Returns: details of the card, returned in a Card object.
 *
 * If passed a string that isn't a valid card name, it will throw() an error, but not crash() it.
 * That way, the function that calls this func can wrap it with a try(), to provide input validation for the deck file being read.
 *
 * This function is passed a string. It takes that string and returns a Card object, with info
 *  that this function provides. This function only provides data that is impossible to get elsewhere.
 * It then calls genManaData to break the displaycosts into their separate variables.
 *
 * Time complexity: constant
 */



    string name(nametest); // throws weird errors if I don't do this
    Card c;
    c.name = name;

    if(name == "Ghitu Lavarunner") {
        c.type = Card::creature;


        c.displaycost = "R";

        c.power = 2;
    }
    else if (name == "Monastery Swiftspear") {
        c.type = Card::creature;


        c.displaycost = "R";

        c.power = 2;
    }
    else if (name == "Goblin Guide") {
        c.type = Card::creature;


        c.displaycost = "R";

        c.power = 2;
    }
    else if (name == "Chain Lightning") {
        c.type = Card::sorcery;
        c.damage = 3;


        c.displaycost = "R";

    }
    else if (name == "Lava Spike") {
        c.type = Card::sorcery;
        c.damage = 3;

        c.displaycost = "R";

    }
    else if (name == "Lightning Bolt") {
        c.type = Card::instant;
        c.damage = 3;

        c.displaycost = "R";


    }
    else if (name == "Needle Drop") {
        c.type = Card::instant;
        c.damage = 2;

        c.displaycost = "R";

    }
    else if (name == "Searing Blaze") {
        c.type = Card::instant;
        c.damage = 3;

        c.displaycost = "RR";

    }
    else if (name == "Rift Bolt") {
        c.type = Card::sorcery;
        c.damage = 3;

        c.displaycost = "R";
        c.mana_value =  1;
        c.redneeded = 1;

    }
    else if (name == "Skewer the Critics") {
        c.type = Card::sorcery;
        c.damage = 3;

        c.displaycost = "R";

    }
    else if (name == "Lightning Helix") {
        c.type = Card::sorcery;
        c.damage = 3;

        c.displaycost = "WR";


    }
    else if (name == "Boros Charm") {
        c.type = Card::instant;
        c.damage = 4;

        c.displaycost = "WR";


    }
    else if (name == "Skullcrack") {
        c.type = Card::sorcery;
        c.damage = 3;

        c.displaycost = "1R";


    }
    else if (name == "Fireblast") {
        c.type = Card::instant;
        c.damage = 4;

        c.displaycost = "1RR";


    }
    else if (name == "Mountain") {
        c.type = Card::land;
        c.isMountain = true;
        c.mana_value =  -1;
        mountainsInLibrary++;
        TOTALMOUNTAINS++;
    }
    else if (name == "Plains") {
        c.type = Card::land;
        c.isPlains = true;
        c.mana_value =  -1;
        plainsInLibrary++;
        TOTALPLAINS++;

    }
    else if (name == "Arid Mesa") {
        c.type = Card::land;
        c.isFetch = true;
        c.mana_value =  -1;
//        fetchesInLibrary++; // unneeded atm
//        TOTALFETCHES++;
    }
    else if (name == "Plateau") {
        c.type = Card::land;
        c.isDual = true;
        c.mana_value =  -1;
        dualsInLibrary++;
        TOTALDUALS++;
    }

    else {
        string e = "error reading card, invalid name";
        cout << e << " \"" << name << '"' << endl;
        throw(e); // in this function, you actually want a throw(), so it can be caught by input validation.
    }

    if(c.mana_value != -1) genManaData(c); // lands have a mana value of -1, so this calls genManaData on all nonland cards

    return c;
}