//
// Created by alexw on 11/22/2022.
//

#include "Goldfish.h"
// the functions that interact with lands, whether by tapping them to pay for costs, or playing them, or providing logic for playing

bool Goldfish::payMana(string cost) {
/* Return value: true if you were able to pay the mana, false if not (determined by payMana() Card overload)
 * Argument: this func is overloaded so you can also pass a string of a full cost (like '2RRW')
 *
 * payMana() is overloaded so you can call it with either a Card object, or just a string of the full cost.
 * If passed by a string (so this func version), it takes the cost and splits it into the different variables needed.
 * The reason the main function is the Card argument and not string, is so you have easier access to all the sub-variables
 *  like mana value, red pips, white pips, etc
 *
 * See payMana(Card) for more info the Card-argument version of the func, since the above only explained this instance of the overload
 *
 *
 * Time complexity: constant
*/
    Card c;
    c.displaycost = cost; // update the newly-created object with the argument
    genManaData(c);   // and then use it to get info on the mana. see genManaData description for more info

    return payMana(c);
}
bool Goldfish::payMana(Card c) { // do NOT make this passed by reference, it must stay an independent copy
/* Return value: true if you were able to pay the mana, false if not
 * Argument: the card you want to pay for.
 *
 * First, this function tests if you're able to pay for the specified mana cost, which is passed within the Card argument.
 *
 * If you are able to pay, it taps your lands accordingly and returns true.
 * If you can't pay, it returns false without tapping anything.
 *

 *
 * This function ONLY taps your lands according to what mana needs to be paid.
 * It does not play the card or care about your hand at all.
 *
 *
 *
 *
 * Time complexity: constant
*/

    int dtaps = 0; // so the whole func can use thsi

    if(untappedLands < c.mana_value) {
        if(debugging) thisgame.log("\tpayMana(): returning due to too few lands");
        return false;
    }



    if(debugging) thisgame.log("\t\t  cost is " + c.displaycost + ", "
              "with untapped: " + to_string(dualsUntapped) + " duals, " + to_string(rUntapped) +
              " mountains, " + to_string(wUntapped) + " plains");

    if(wUntapped < c.whiteneeded) {
        if(debugging) thisgame.log("\tpayMana(): returning due to too few plains");
        return false; // ensure you have enough of each color you need
    }
    else if((rUntapped + dualsUntapped) < (c.redneeded + c.genericNeeded)) {
        if(debugging) thisgame.log("\tpayMana(): returning due to too few red lands");

        return false;
    }
        // These decks have way more red lands than white lands. For now, I'll just pay all generic costs with red mana.
        // This is harmless, as very few spells in this deck even have generic mana.
        // Figuring out the logic of "which color to pay generic with" is exponentially more difficult than I had originally imagined, and I don't
        //  have the time to teach myself the proper way of doing this, using game trees.



    else {

        if(dualsUntapped == 0) {
            dtaps = 0;
        }
        int diff = (rUntapped - c.redneeded - c.genericNeeded); // the difference between available red mana and all the red mana costs
        // if diff is positive, means there's enough red. Else, you need to tap duals
        if (diff >= 0) {
            if(debugging) thisgame.log("\t\t\t\tNo need to tap duals");
        }
        else {
            diff *= -1;
//        if(debugging) thisgame.log("\t\t\tpayMana(): diff is " + to_string(diff) + ", "
//            "with " + to_string(dualsUntapped) + " duals untapped, and " + to_string(rUntapped) + " mountains untapped, " +
//            to_string(c.redneeded) + " R needed, with " + to_string(c.genericNeeded) + " generic needed");


            dtaps = dualsUntapped; // gets how many duals were tapped by checking before and after


                if (diff <=
                    dualsUntapped) { // if the difference between "mana needed" and "mana available from basics"
                    // can be made up with duals, tap the duals

//            if(debugging) thisgame.log("tapped " + to_string((dualsUntapped -= diff)) + " duals");

                    dualsUntapped -= diff;  // tap duals according to pay for the difference between red mana needed and mountains available
                    dtaps -= dualsUntapped; // `dtaps` now holds how many duals were tapped to pay for mana

                    c.redneeded -= dtaps; // communicate to the lower half of this function that it needs to pay less, b/c duals already paid some
                    // this would mess up the card for future use, BUT this card is copied, not passed by reference, so it's fine

                }
                    // This means that duals will only tap for red mana.
                    // Similar to playLand, the logic here is way crazier than I anticipated,
                    //  because in real life, knowing what land to play is very easy.

                    // I figured I'd just pseudocode my internal thought processes and then code them, but
                    //  it turns out, there's way more factors and things to consider than is represented
                    //  in a thought process so simple IRL you don't even need to think about it.

                    // It would violate the project specs to use data structures that haven't been taught in class.



                else crash("error in payMana(): `diff` dual paying went wrong");
                // If the difference can't be made up with duals, something went wrong in the logic/math above.
                // This shouldn't ever happen but provides a failsafe.
                // Much better for a bug to just crash it outright and simultaneously pinpoint the problem,
                //      than to silently malfunction while you think it's working


        }

        int wtaps = wUntapped; // these vars keep track of how many of each type you've tapped
        int rtaps = rUntapped;

        rUntapped -= c.redneeded;    // these tap your lands according to how much of each color needed
        wUntapped -= c.whiteneeded;  //  and are harmless if you need zero of that color
        rUntapped -= c.genericNeeded;


        wtaps -= wUntapped; // these vars now contain the amount of lands of that type you've tapped
        rtaps -= rUntapped;


        if(debugging) thisgame.log("\t\t\ttapped " + to_string(dtaps) + " duals, " + to_string(rtaps) +
                                                   " mountains, and " + to_string(wtaps) + " plains ");

        untappedLands = wUntapped + rUntapped; // update how many total lands are untapped
        return true;
    }

}


void Goldfish::playLand(Card targetcard, bool tapped) {
/* Arguments: the card to be played, in the form of a Card object. A bool for whether the land should enter the battlefield tapped
 *          (note for that for my project, `tapped` will always be `false` but later on, that might not be the case. I wanted to have
 *          the infrastructure in place to support it for the future).
 *
 * This function is passed the name of a land, and then plays the named land from your hand.
 * This assumes you have the card in question in your hand, and calls crash() if it's not there
 * Note that this Card have to be a fully fleshed out object, it just needs to have the relevant land info
 *
 *
 * Time complexity: O(n) where n is the amount of cards in your hand
*/

    Card c;

    // You cannot just play the card passed as an argument,
    //  because that argument could just be holding the name and nothing else.
    // That's why you need to iterate and get the right card from your hand (also so you know the correct index to discard)

    for(int i = 0; i < hand.getLength(); i++) {
        c = hand.getElement(i);
        if(c.name == targetcard.name) { // if the target card is found in your hand
            if (logging) thisgame.log("\t--> " + c.name);

            // land variables are updated in main game loop

            c.tapped = tapped; // set card `tapped` state to argument passed

            fieldLands.append(c);
            hand.remove(i);
            return;
//            updateLandvars() is called after landlogic() back in main game func;
        }
    }

    crash("error in playLand(): card not found"); // this func intentionally assumes you have the right card in your hand

}
void Goldfish::playLand(string cardname, bool tapped) {
/* Arguments: card name, passed as string. Whether the land should enter the battlefield tapped, passed by bool
 *
 * This is an overload for playLand, so you can play via string and not just Card object
 *
 * Time complexity: O(n). See playLand(Card) overload for more details
*/
    Card c;
    c.name = cardname;
    playLand(c, tapped);
}


bool Goldfish::tryPlains() {
/* Return value: true if you were able to play a Plains, else false
 *
 * tryPlains() and tryMountain() are identical, except one plays Plains and the other plays Mountains.
 * I could combine them, but I'd have to insert so many `if Plains do this, if Mountain do that`
 *    that it becomes far more efficient to make it two functions.
 *
 * These functions do NOT assume that you have the right card in your hand.
 * They iterate through and play a land if possible, and if they play it, return true.
 * If they're not able to find the required plains/mountain, returns false.
 *
 * Time complexities:
 *  Minimum: constant, if no plains in hand (this is why the variables like `plainsInHand` exist)
 *  Average and maximum: O(n), where n is the amount of cards in your hand
 *  The difference between avg and max is where the first plains is located
 *
*/

//    if(debugging) thisgame.log("TRYPLAINS ");
    if(plainsInHand == 0) return false; // first check if you even have one in hand. If not, return false
    Card c;

    // else, you do have one in hand. Iterate through till you find it, then play it
    for (int i = 0; i < hand.getLength(); i++) { // iterate through your hand
        c = hand.getElement(i);
//        if(debugging) thisgame.log("Curr - " + c.name);

        if (c.isPlains) {
            playLand(c, false);
            return true; // if played successfully, return true

        }
    }
    return false; // if no plains found, return false

}
bool Goldfish::tryMountain() {
/* Return value: true if you were able to play a Mountain, else false
 *
 * This func is exactly the same as tryPlains(), except it's for Mountains. See tryPlains for more info
 *
 * Minimum: constant, if no mountains in hand
 * Average and maximum: O(n), where n is the amount of cards in your hand
 *  The difference between avg and max is where the first mountain is located
*/


//    if(debugging) thisgame.log("TRYMOUNTAIN");
    if(mountainsInHand == 0) return false;
    Card c;

    for (int i = 0; i < hand.getLength(); i++) {
        c = hand.getElement(i);
        if (c.isMountain) {

            playLand(c, false);

            return true; // if played successfully, return true

        }
    }
    return false; // if no mountain found, return false

}


bool Goldfish::landLogic() {
/* return value: bool corresponding to whether you were able to play a land or not
 *
 * This function is the beginning of what I hope will grow into an actual AI.
 * Basically, it tries to play them in a certain order according to logic
 *    but what really matters is that a land gets played.
 * I've structured the logic so that no matter what, if you have a land in your hand, it'll play it.
 * Most of these are just `if`s and not `else/if`s. This is intentional.
 * The just-if (excluding the one beginning the else/if chain) statements are intentionally not if/elses
 *    to ensure that every possible logic pathway is followed. In other words, it tries to play lands in a specific order according to priorities.
 * Each 'if' represents trying to play a different priority card (or the same card for a different reason)
 *
 * Time complexities:
 *  Minimum: constant, if no cards in hand
 *  Average and maximum: O(n), where n is the amount of cards in your hand
 *  The difference between average and max is how far it has to traverse before it finds a valid land play.
 *      Well I guess maximum would be the maximum scenario for fetch() because that's the longest,
 *              (which would be O(n) where n is cards in hand + cards in library)
 *
 * Even though this particular function doesn't have loops, the functions it calls are linear, so that makes this linear
 *      (specifically, tryMountain and tryPlains iterate through your hand to see if you have the requested card)
*/

    Card c;
    if(landsInHand == 0)  { // if you have no lands in hand, no point continuing on
        if(debugging) thisgame.log("No lands in hand, skipping playLand step");
        return false;
    }


    if(fetchesInHand > 0) { // first play a fetch if you can
        if(debugging) thisgame.log("Fetches in hand: " + to_string(fetchesInHand) + ", calling fetch()");
        return fetch();
    }

//    if (debugging) thisgame.log("Testing for duals in hand: currently " + to_string(dualsInHand) );

    if(dualsInHand > 0) { // then check if you have a dual, if so play it
        if (debugging) thisgame.log("Duals in hand: " + to_string(dualsInHand) + ", calling dual()");
        playLand("Plateau", false);
        // playLand is intentionally designed to crash() if it tries to play an invalid card, so if it doesn't crash(),
        // it's safe to assume a land has been successfully played, and thus can just return true
        return true;
    }

    if(plainsInHand == 0) { // if you have no plains in your hand, try a mountain
        if(debugging) thisgame.log("No plains in hand, trying mountain");
        if(tryMountain()) return true;
    }

    if(mountainsInHand == 0) { // if no mountains in hand, try plains
        if(debugging) thisgame.log("No mountains in hand, trying plains");
        if(tryPlains()) return true;
    }
    if(landsout == 0) {
        // If you have no lands out, try to play a mountain.
        // All my white spells cost two mana, which means that you won't be able to cast anything on turn one with just one plains
        // So it's better to play a mountain that way you can cast something this turn
        // However, if you have no mountains in hand, play your plains, because it's better than nothing
        if(debugging) thisgame.log("No lands out, trying mountain");

        if(tryMountain()) return true;
        else if (tryPlains()) {
            return true;
        }
        crash("landLogic(): According to above conditionals, no duals, fetches, mountains, or plains, but still have lands in hand");
    }


    if(wLandsOut == 0) { // wLandsOut doesn't count duals

        // If you have lands out but none of them are white, try to play a plains
        // This is to get one plains on the battlefield. It's hard to try to play a land depending on what cards are in your hand
        // I probably should be using a game tree anyways, so this is an example of "not perfect but good enough" I talked about in the report
        if(debugging) thisgame.log("No plains out, trying plains");


        if(tryPlains()) return true;
//        else if (tryMountain()) return true;
    }
    else {
        // Once you have a plains out, only play mountains
        // (until you only have plains lands in your hand, in which case play a plains, covered in earlier `if`)
        // Any more logic (especially trying to determine which lands to play based on cards in hand) is extremely hard, way more than I expected

        if(debugging) thisgame.log("Plains out, trying mountain");
        if(tryMountain()) {
            return true;
        }
        else if (tryPlains()) {
            return true;
        }
        else return false;
    }

    // You should only ever reach this point if you have no lands in hand.
    // Except, we've checked if you have no lands in hand. So if it gets to this point, it means the logic is flawed somewhere

    crash("landLogic() flawed: all ifs passed but still have cards in hand");
    return false; // this won't ever execute, I just put it to make the "non-void control path" warning go away


}

bool Goldfish::fetch() {//, Card::landtypes) {
/* Return value: true if this fetched a land and put it on the field, false if it didn't
 *
 * This function discards an Arid Mesa from your hand, searches your library for a land, and puts the land on the field.
 * It linear searches for a Plateau, then searches for a Plains, and then a Mountain. When it finds one, it plays it.
 *
 * Even though this function contains 3 individual linear searches, only one will run per function call.
 *
 * if you've somehow played every single land card in your library and still haven't won, the Arid Mesa is just discarded
 *      and no card is put on the battlefield
 *
 *
 * Reasoning behind fetch logic:
 *  I prioritize duals then mountains then plains.
 *      Duals first becauase they're objectively better than both the other two, since they do the job of either and are better overall.
 *      Then Mountains, because my decks use way more red than they do white.
 *      Then Plains, if there are no duals or Mountains.
 *
 *
 * Time complexities:
 *  Minimum: O(n) where n is the amount of cards in your hand (but not library).
 *      Although this only happens if for some reason you don't have the required card in your hand, in which case it's designed to crash.
 *
 * So really the minimum time complexity, assuming it functions correctly, is just the cards in your hand + 1 card in library (still linear)
 *      (if the first card you check happens to be the target)
 *
 *  Average and maximum: O(n) where n is the amount of cards in your library. (plus cards in hand, but that's a negligible number)
 *
 * The difference between average and maximum is how many cards you iterate over before you hit the card you need, but it
 *      only ever runs once per card, so it remains linear
 *
 */


// I considered discarding the Arid Mesa via the function that calls this one, but I don't like splitting stuff up like that
// I'd rather keep stuff self-contained so there's less of a chance of breaking stuff when shuffling logic paths around
    if(hand.isEmpty()) crash("error in fetch(): called with empty hand");
    Card c;
    bool discardedAridMesa = false;
    for(int i = 0; i < hand.getLength(); i++) { // search your hand for an Arid Mesa and then discard it
        c = hand.getElement(i);
        if(c.name == "Arid Mesa") {
            graveyard.push(c); // I can't call playLand because this goes directly to the graveyard, not to the battlefield
            hand.remove(i);
            fetchesInHand--;
            if(logging) thisgame.log("\t--> " + c.name + " (to graveyard)");

            discardedAridMesa = true;
            break; // without a break, if you have multiple fetches in hand, this loop will discard them all
        }
    }            // land variables are updated in main game loop


    if(!discardedAridMesa) crash("error in fetch(): no Arid Mesa in hand, even though there should be");
    // There's no reason this function should be called if you're not actively trying to play a fetch land
    // And if you are playing a fetch, then you should have discarded it before. So if you still have one, the logic is invalid


    // logic for fetching duals
    if(dualsInLibrary > 0) {
        if(debugging) thisgame.log("Duals in library: " + to_string(dualsInLibrary) + ", searching for Plateau");
        for(int i = 0; i < library->getLength(); i++) { // search for a Plateau
            c = library->peek();
            if(c.name == "Plateau") {
                library->pop(); // if found, remove from library, then put it on the field
                dualsInLibrary--;
                fieldLands.append(c); // CANNOT use playLand because it tries to remove the card from your hand

                if(logging) thisgame.log("\t--> " + c.name);

                shuffleLibrary(); // shuffle your library after searching it
                return true;
            }
            else library->rotate(Stack<Card>::RIGHT);
        }
        crash("Plateau not found despite dualsInLibrary being true"); // I'm basically using landtypeInLibrary as a bool
    } else if(debugging) thisgame.log("Fetch() skipped searching for Plateau, dualsInLibrary: " + to_string(dualsInLibrary));


    // logic for fetching mountains
    if(mountainsInLibrary > 0) {
        if(debugging) thisgame.log("Mountains in library: " + to_string(mountainsInLibrary) + ", searching for Mountain");
        for(int i = 0; i < library->getLength(); i++) { // and then search for a Mountain
            c = library->peek();
            if(c.name == "Mountain") {
                library->pop(); // if found, remove from library,
                mountainsInLibrary--;
                fieldLands.append(c); // then add to battlefield

                if(logging) thisgame.log("\t--> " + c.name);

                shuffleLibrary();
                return true;
            }
            else library->rotate(Stack<Card>::RIGHT);
        }
        crash("Mountain not found despite mountainInLibrary being true");

    } else if (debugging) thisgame.log("Fetch() skipped searching for Mountain, mountainsInLibrary: " + to_string(mountainsInLibrary));


    // logic for fetching plains
    if(plainsInLibrary > 0) {
        if(debugging) thisgame.log("Plains in library: " + to_string(plainsInLibrary) + ", searching for Plains");
        for(int i = 0; i < library->getLength(); i++) {
            c = library->peek();
            if(c.name == "Plains") {
                library->pop();
                plainsInLibrary--;
                fieldLands.append(c);

                if(logging) thisgame.log("\t--> " + c.name);

                shuffleLibrary();
                return true;
            }
            else library->rotate(Stack<Card>::RIGHT);
        }
        crash("Plains not found despite plainsInLibrary being true");

    } else if (debugging) thisgame.log("Fetch() skipped searching for Plains, plainsInLibrary: " + to_string(plainsInLibrary));





    if(debugging) thisgame.log("Somehow didn't find a single valid land to fetch, this is likely a logic ERROR----------------------------");
    // It's not *necessarily* a logic error, and there's no easy way to tell, which is why I just continue instead of crashing
    // Epecially cause things will continue just fine without it. The fetch land is discarded,
    //  you don't play a land this turn, and your turn continues on.



    shuffleLibrary();
    // Even though you didn't take anything out of it, you still looked through your deck of cards, so you need to shuffle it afterwards

    return false;
}

void Goldfish::updateLandvars() {
/* Updates all of the land variables
 * Most of these variables don't need to exist, and can be found just by traversing with an iterator
 *      (which is exactly what this func does)
 *      but I've put these into variables to reduce time complexity for anything that calls `rLandsOut` for example
 * It also drastically increases readability for code that uses it; it references a single variable, vs having a whole loop each time
 *
 * Time complexities:
 *  Minimum: constant, if hand is empty and no lands on the battlefield
 *  Average and maximum: O(n) where n is the amount of lands in hand + on battlefield
 *
 *  The average will usually be maximum, since it by necessity has to traverse everything
 *
 */

    // reset all land variables
    landsInHand = 0;
    dualsInHand = 0;
    plainsInHand = 0;
    fetchesInHand = 0;
    mountainsInHand = 0;

    rUntapped = 0;
    wUntapped = 0;
    dualsUntapped = 0;
    untappedLands = 0;

    dualsOut = 0;
    rLandsOut = 0;
    wLandsOut = 0;
    landsout = fieldLands.getLength(); // set landsout to correct length


    if(fieldLands.isEmpty() && hand.isEmpty()) return;
    // If both these are true, everything is past this should be zero and the previous part makes them zero
    //      so there's no reason to loop a bunch of empty objects

    Card c;
    for(int i = 0; i < hand.getLength(); i++) { // traverse hand and update "lands in hand" variables
        c = hand.getElement(i);
        if(c.type != Card::land) continue; // skip nonland cards
        else {
            landsInHand++;
            if(c.isPlains) plainsInHand++;
            else if (c.isDual) dualsInHand++; // if correct type, update the variable
            else if(c.isFetch) fetchesInHand++;
            else if (c.isMountain) mountainsInHand++;

        }
    }

    if(fieldLands.isEmpty()) return; // if no lands on field, return updated hand vars but keep field variables zero


    for(int i = 0; i < fieldLands.getLength(); i++) { // update all variables for lands on the battlefield
        c = fieldLands.getElement(i);


        if(c.isPlains && !c.tapped) { // untapped plains
            wLandsOut++;
            wUntapped++;
            untappedLands++;
        }
        else if (c.isPlains && c.tapped) {    // tapped plains
            wLandsOut++;
        }
        else if (c.isMountain && !c.tapped) { // untapped mountain
            rLandsOut++;
            rUntapped++;
            untappedLands++;
        }
        else if(c.isMountain && c.tapped) { // tapped mountain
            rLandsOut++;
        }

        else if(c.isDual && !c.tapped) { // untapped dual
            dualsOut++;
            dualsUntapped++;
            untappedLands++;
        }
        else if(c.isDual && c.tapped) { // tapped dual
            dualsOut++;
        }
        // fetches are not counted because they don't go to the battlefield. They are instead are discarded immediately
    }

}

