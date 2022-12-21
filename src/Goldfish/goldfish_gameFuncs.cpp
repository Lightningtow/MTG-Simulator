//
// Created by alexw on 11/18/2022.
//

#include "Goldfish.h"
// functions that are normal stuff that you'd do in a normal game of Magic

void Goldfish::untapStep() {
/* Updates the `tapped` variables to their partner variable of "all of X objects, regardless of whether they're tapped"
 *
 * Time complexity: constant
 */
    untappedLands = landsout;
    wUntapped = wLandsOut;
    rUntapped = rLandsOut;
    dualsUntapped = dualsOut;
}
void Goldfish::combatStep() {
/* This function simulates the combat phase of MTG.
 *
 * This function deals damage to your opponent equal to the power of all creatures you have on the field
 *
 * This function assumes you have already played creatures
 *
 * Time complexity: O(n) where n is number of creatures on battlefield
 */



    int totaldamage = 0;

    string creatures = "";
    int len = fieldCreatures.getLength();
    Card curr;
    for(int i = 0; i < len-1; i++) { // leaves one left
        curr = fieldCreatures.peek();

        creatures += curr.name + ", ";
        totaldamage += curr.power;
        fieldCreatures.rotate(Stack<Card>::RIGHT);
    }
    curr = fieldCreatures.peek();
    creatures += curr.name;  // reason we skip the last one creature and use it out of the loop
    totaldamage += curr.power; // is to not have a comma against the last one for the log message


    string attackmsg = "\tCombat: " + to_string(totaldamage) + " with " + creatures;
    if(logging) thisgame.log(attackmsg);


    enemylife -= totaldamage;
//    for(int i = 0; i < battlefield.getLength(); i++) {
//        battlefield.peek()
//    }
}


void Goldfish::drawCard() {
/* Return value: a fully formed, playable Card object, taken straight off the top of your library.
 *
 * Draws a card from the top of your library and puts it in your hand
 *
 *
 * Time complexity: constant
 *
 */

    if(library->isEmpty()) {
        // In Magic: The Gathering, if you would draw a card when your library is empty,
        //  you instead just lose the game.
        string e = "Ending program due to drawing card from empty library. This program assumes the decks you run are valid decks that work."
                   "\nUnfortunately, even if a deck makes it past the input validation, it might still fail. \nFor example, "
                   "if it's all lands, or all spells with no lands, there's no way to win a game. \nLater on I'll implement "
                   "a way to handle and sort game losses, but for now, it assumes that the deck you want to test is actually "
                   "a valid, usable deck, since there's no point in using my program if it isn't. "
                   "\nIf the deck can't beat an opponent doing nothing, it will certainly "
                   "lose to an opponent that's actively destroying your stuff and trying to win as well. ";
        crash(e);

    }

    Card c = library->peek(); // take card from your library
    library->pop(); // and put it
    hand.append(c); // in your hand
    if(logging) thisgame.log("Drew " + c.name);


    // update variables depending on which card you drew
    if(c.type == Card::creature) {
        creaturesInHand++;
        spellsInHand++;
    }
    else if(c.type == Card::instant || c.type == Card::sorcery) {
        oneshotsInHand++;
        spellsInHand++;
    }
    else if(c.type == Card::land) {
        landsInHand++;

        if(c.isMountain) {
            mountainsInHand++;
            mountainsInLibrary--; // you just drew a card, so there's one less mountain in your library
        }
        else if(c.isPlains) {
            plainsInHand++;
            plainsInLibrary--;
        }
        else if(c.isFetch) {
            fetchesInHand++;
        }
        else if(c.isDual) {
            dualsInHand++;
            dualsInLibrary--;
        }
    }




}
void Goldfish::discardCard() {
/* Discards a card from your hand according to AI.
 * The most common case is if you're discarding back down to 7 cards at the end of your turn.
 * In my program, the only time that'll really happen is if you get mana screwed (or color screwed).
 *      Mana screwed means you don't have any/enough lands to cast your stuff.
 *      Color screwed means you have the wrong color lands.
 *          For example, if you have a bunch of plains, but no mountains, so you can't cast your red cards, that'd be called color screwed.
 *
 * This function just discards the card in your hand with the highest mana value.
 * That way when you eventually draw a land, you'll be able to play more stuff faster with it.
 *      As opposed to if you discarded the cheapest cost cards, you might draw a land but still have that one land be inadequate, because the stuff
 *       in your hand costs a bunch of mana to cast.
 * Whereas if you keep the cheapest card, you're far more likely to be able to cast it immediately.
 *
 * Time complexity: O(n), where n is the amount of cards in your hand
 */
    int highIndex = -1; // index of card with highest mana value
    int highestMV = -42; // finds the highest mana value of cards in your hand
    Card c;
    for(int i = 0; i < hand.getLength(); i++) { // find card with highest mana value and remember where it was
        c = hand.getElement(i);
        if(c.mana_value > highestMV) {
            highIndex = i;
            highestMV = c.mana_value;
        }
    }

    for(int i = 0; i < hand.getLength(); i++) { // then discard that card
        if(i == highIndex) {
            Card discard = hand.getElement(i);
            graveyard.push(discard);
            hand.remove(i); // remove() is remove by index

            if(logging) thisgame.log("Discard " + discard.name);
        }
    }

}


bool Goldfish::tryCreature() {
/* Return value: true if successfully played creature, false if didn't
 *
 * This function tries to play a creature.
 * This function does not assume you have the mana to pay for one, or even have a creature in your hand at all
 * If you're able to, though, it will play a creature and pay costs associated with it
 *
 * This function could be combined with tryOneshot, but there'd be so many conditionals, it'd be messy and slow. It's far neater to separate them
 *
 * Time complexities:
 *  Minimum: constant, if no creatures in hand or no untapped lands
 *  Average and maximum: O(n), where n is amount of cards in your hand
 */

    if(creaturesInHand == 0 || untappedLands == 0) return false;
    // if you have no creatures to play, return false
    // or, if you have creatures in hand but no lands with which to cast them, return false;


    Card c;
    for(int i = 0; i < hand.getLength(); i++) { //iterate over your whole hand
        c = hand.getElement(i);

        if(c.type == Card::creature) { // if your current iteration is a creature


            if(untappedLands >= c.mana_value) {
                // Do you have enough TOTAL mana for the card?
                // Even if the colors aren't necessarily right? if so, you're halfway there

                if(debugging) thisgame.log("  Trying to cast " + c.name);

                bool paid = payMana(c.displaycost);
                updateLandvars(); // linear

                if(!paid) {
                    continue; // if you can't pay the cost, skip past this card
                }
                // See payMana func description for why this might happen
                // But if flow hits here, all checks are complete, so the card is able to be played. Play it!


                if(logging) thisgame.log("\t--> " + c.name);
                if(logging) thisgame.incCreaturesPlayed(); // increment creaturesPlayed
                // payMana pays the cost, if able. So no need to tap any lands here

                fieldCreatures.push(c); // put the creature on the battlefield
                hand.remove(i);
                return true; // return "yes, you did play a spell"
            }
        }   // Many of these ifs could be combined into if(check && check && check) but that's super hard to interpret
    }       // I prefer to have nested or sequential ifs, instead
    return false;
}
bool Goldfish::tryOneshot() {
/* Return value: true if successfully played oneshot, false if didn't
 *
 *
 * This function tries to play a oneshot.
 * This function does not assume you have the mana to pay for one, or even have one in your hand at all
 * If you're able to, though, it will play a creature and pay costs associated with it
 *
 * Time complexities:
 *  Minimum: constant, if no oneshots in hand or no untapped lands
 *  Average and maximum: O(n), where n is amount of cards in your hand
 */




//    if(debugging) thisgame.log("ONESHOT, " + to_string(untappedLands) + " untapped");
//    if(creaturesInHand == 0 || untappedLands == 0) return false;

    Card c;
    // attempt to cast one one-shot
    for(int i = 0; i < hand.getLength(); i++) { // iterate through hand
        c = hand.getElement(i);

        if(c.type == Card::instant || c.type == Card::sorcery) { // if card is a oneshot

            if(untappedLands >= c.mana_value) { // do you have enough TOTAL mana for the card?
            // even if the colors aren't necessarily right? if so, you're halfway there

            if(debugging) thisgame.log("  Trying to cast " + c.name);

            if(!payMana(c.displaycost)) continue; // if can't pay, continue to next card. See payMana()
            if(logging) thisgame.log("\t--> " + c.name + ":  -" + to_string(c.damage) + " ");
            if(logging) thisgame.incOneshotsPlayed(); // increment oneshots played variable

            enemylife -= c.damage; // deals X damage to enemy, where X is the amount of damage the oneshot does

            graveyard.push(c); // add card to your discard pile
            hand.remove(i); // discard the used card from your hand
            return true;
            }
        }
    }
    return false;
}


void Goldfish::shuffleLibrary() {
/* Shuffles your library
 *
 * Time complexities:
 * Time complexity is a little weird because it rotates a random number between 0 and n times,
 * The minimum complexity is fully linear, if it randomly chose "rotate 1 time" for each element
 * The maximum complexity is fully O(n^2), if it randomly chooses "rotate maximum times" for each element
 * So the average complexity lies somewhere between those two ranges. O(n^1.5)?
 *
 * I'll treat average complexity as the worst-case scenario of O(n^2), for purposes of determining time complexities of functions that call this
 *
 */

    int len = library->getLength(); // original length of library

    random_device rd;
    mt19937 gen(rd()); // get randomness factor
    uniform_int_distribution<> distr(0, len);



    auto* temp = new ArrayStack<Card>(len);
    for(int i = 0; i < len; i++) { // for entire array

        for(int j = 0; j < distr(gen); j++) { // rotate a random amount
            library->rotate(Stack<Card>::Direction::RIGHT);
        }

        temp->push(library->peek());// move top card from library to temp
        library->pop();
    }


    // Temp is now shuffled and library is empty, so move elements from temp back to library
    for(int i = 0; i < len; i++) {
        library->push(temp->peek());
        temp->pop();
        // This reverses the order, but it doesn't matter because it's shuffled anyway
        // I could rotate to have it copy in the same order, but that needlessly adds more execution time

    }

    delete temp;

}

