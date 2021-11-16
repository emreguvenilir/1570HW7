#ifndef FS2021_CS1570_HW6_CONTESTANT_H
#define FS2021_CS1570_HW6_CONTESTANT_H

#include "Codemon.h"
#include "Item.h"

const int POCKET_SIZE = 10;
const int BACKPACK_SIZE = 20;

class Contestant{
public:
    Contestant();
    Contestant(string name);
    //Pre: code should be valid and declared
    //Post: returns bool
    //Desc: Adds code to the codemonPocket
    bool insertNewCodemon(const Codemon& newCodemon);
    //Pre: itemForBP is valid and declared
    //Post: return type bool
    //Desc: Adds itemForBP to the backpack
    bool insertNewItem(const Item& newItem);
    //Pre: None
    //Post: None
    //Desc: updates the backpack, and the pocket with Codemon and Item objects based on user inputs
    void prepare(); // populate contestant info
    //Pre: None
    //Post: None
    //Desc: Prints all info of the given Contestant
    void print() const;
    //Pre: signedUp and all its values are declared, SIZE > 0
    //Post: None
    //Desc: friend func to the Contestant class, checks if a skill is present and outputs to which users and codemon
    friend void skillLookUp(const Contestant contestants[], const int SIZE);
    //Pre: None
    //Post: string return type
    //Desc: Getter func for name
    string getName(){return m_name;}

    //Pre: opponent is valid
    //Post: Contestant return type
    //Desc: Battle function, returns the winner
    Contestant & operator *(Contestant & opponent);
    //Pre: newCodemon is valid
    //Post: Contestant return type
    //Desc: overload of + operator to add a Codemon obj to the Contestant
    Contestant & operator +(const Codemon & newCodemon);
    //Pre: newCodemon is valid
    //Post: Contestant return type
    //Desc: overload of += operator to add a Codemon obj to the Contestant
    Contestant & operator +=(const Codemon & newCodemon);
    //Pre: newCodemon is valid
    //Post: Contestant return type
    //Desc: overload of - operator to remove a Codemon obj to the Contestant
    Contestant & operator -(const Codemon & newCodemon);
    //Pre: newCodemon is valid
    //Post: Contestant return type
    //Desc: overload of -= operator to remove a Codemon obj to the Contestant
    Contestant & operator -=(const Codemon & newCodemon);

    //Pre: newItem is valid
    //Post: Contestant return type
    //Desc: overload of + operator to remove a Codemon obj to the Contestant
    Contestant & operator +(const Item & newItem);
    //Pre: newItem is valid
    //Post: Contestant return type
    //Desc: overload of += operator to remove a Codemon obj to the Contestant
    Contestant & operator +=(const Item & newItem);
    //Pre: newItem is valid
    //Post: Contestant return type
    //Desc: overload of - operator to remove a Codemon obj to the Contestant
    Contestant & operator -(const Item & newItem);
    //Pre: newItem is valid
    //Post: Contestant return type
    //Desc: overload of -= operator to remove a Codemon obj to the Contestant
    Contestant & operator -=(const Item & newItem);

    Contestant & operator()(const string healed);

    void shuffle();
private:
    string m_name;
    int m_numCodemonsOwned;
    int m_numItemsOwned;
    int m_openPocketIndex;
    int m_openBackpackIndex;
    Codemon m_pocket[POCKET_SIZE];
    Item m_backpack[BACKPACK_SIZE];

    int m_volume;
};

/*
 * Desc: This function looks up a skill for the user among all the contestants' codemons
 * Pre: None
 * Post: If a matching skill is found, relevant info will be printed out. The user is allowed to look up skills as many
 *          times they want.
 */
void skillLookUp(const Contestant contestants[], const int SIZE);

#endif //FS2021_CS1570_HW6_CONTESTANT_H
