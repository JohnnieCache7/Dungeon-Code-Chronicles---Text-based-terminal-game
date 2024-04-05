#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include <iostream>
#include <string>

using namespace std;

// inventory object, designed to be created at start of new playthrough
class Inventory {
private:
    //inventory size, subject to change
    const int inventorySize = 3;
    // array for unique items, inventory size is subject to change
    string* itemInventory = new string[inventorySize];
    int currSize = 0;
    // numbered inventory items, no limit, feel free to add more
    int coins;
    int lockpicks;
public:
    Inventory(): coins(0), lockpicks(0) {};
    // fields constructor for new inventory, incase we want a starting amount of items for different classes
    Inventory(int coins, int lockpicks): coins(coins), lockpicks(lockpicks) {}
    ~Inventory() {}
    //setters - probably wont use these or the getters
    void setCoins(int coins) {
        this->coins = coins;
    }
    void setLockpicks(int lockpicks) {
        this->lockpicks = lockpicks;
    }

    //getters
    int getCoins() { return coins;}
    int getLockpicks() {return lockpicks;}

    //check for coins - probably don't need to use this, call remove coins instead
    bool hasCoins(int coinAmount) {
        if (coins <= 0) {
            return 0;
        }
        else if (coins < coinAmount) {
            return 0;
        }
        else {
            return 1;
        }

    }
    //add and remove coins to/from total
    void addCoins(int coinsAdded) {
        coins = coins + coinsAdded;
    }
    void removeCoins(int coinsRemoved) {
        if (hasCoins(coinsRemoved)) {
            coins = coins - coinsRemoved;
        }
        else {
            cout << "You don't have enough coins" << endl;
        }
    }
    // check for lockpicks
    bool hasLockpicks() {
        if (lockpicks > 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    //add and remove lockpicks to/from total
    void addLockpicks(int lockpicksAdded) {
        lockpicks = lockpicks + lockpicksAdded;
    }

    // only removes one lockpick at a time
    void removeLockpick() {
        if (hasLockpicks()) {
            lockpicks--;
        }
        else {
            cout << "No lockpicks" << endl;
        }
    }

    //add unique items
    void addItem(string newItem) {
        //if inventory is not full, adds item to inventory and moves index
        if (currSize < inventorySize) {
            int emptySpot = 0;
            while(emptySpot < inventorySize) {
                if (itemInventory[emptySpot] == "") {
                    break;
                }
                else {
                    emptySpot++;
                }
            }
            itemInventory[emptySpot] = newItem;
            currSize = currSize + 1;
            cout << newItem << " added to inventory" << endl;

        }
        //if inventory is full prompts the user to remove a item
        else if (currSize >= inventorySize) {
            int tempIndex = -1;
            cout << "Inventory full, select an item to replace: " << endl;
            for (int i=0; i < inventorySize; i++) {
                cout << "Item " << i + 1 << ": " << itemInventory[i] << endl;
            }
            cout << "Drop Current item: " << inventorySize + 1 << endl;
            //user input for which item to drop
            cin >> tempIndex;
            tempIndex = tempIndex -1;
            //input validation
            while (tempIndex < 0 || tempIndex > inventorySize) {
                cout << "Invalid number, Try again: " << endl;
                cin >> tempIndex;
                tempIndex = tempIndex - 1;
            }
            //new item is not added
            if (tempIndex == inventorySize) {
                cout << "Current item dropped" << endl;
            }
            else  {
                itemInventory[tempIndex] = newItem;
                cout << newItem << " added" <<endl;
            }
        }
    }


    //removes unique items, should be used only to consume a item, no need to let the user drop items as they will be replaced when a new one is added (above method)
    //SHOULD ONLY BE CALLED IF HAS ITEM RETURNS TRUE - for convenience, consider using below method checkAndRemoveItem
    void removeItem(string discardItem) {
        // loops through inventory until item is found
        for (int i = 0; i < inventorySize; i++) {
            if (itemInventory[i] == discardItem) {
                itemInventory[i] = "";

                currSize = currSize - 1;
                cout << discardItem << " removed" << endl;
                break;
            }
        }
    }

    // use this for item checks that also remove the item - bool value so it still returns true or false
    bool checkAndRemoveItem(string item) {
        // if you have the item entered, removes it as well
        if (hasItem(item)) {
            int userInput;
            //user input for removing item
            cout << "You have a " << item << ", would you like to use it?" << endl;
            cout << "1: Yes" << endl << "2: No" << endl;
            cin >> userInput;
            // input validation
            while (userInput != 1 && userInput != 2) {
                cout << "Invalid number, please enter 1 or 2: " << endl;
                cin >> userInput;
            }
            // removes it, returns true for check
            if (userInput == 1) {
                removeItem(item);
                return true;
            }
            // if user decided not to use item, returns false
            return false;
        }
        //fails check also if you do not have the item
        return false;
    }


    // check inventory method, boolean indicates whether or not the item is in inventory - this will be used for item checks, particularly ones that dont consume the item
    bool hasItem(string itemQuery) {

        // if any array item is same as item query name, returns true and exits
        for (int i = 0; i < inventorySize; i++ ) {
            if (itemInventory[i] == itemQuery) {
                return true;
            }
        }
        //returns false if item is not found in inventory
        return false;

    }

    //display inventory method
    void display() {
        cout << endl << "===============================================" << endl;
        cout << "Current Inventory: " << endl;
        cout << "===============================================" << endl;
        cout << "Coins: " << coins << "  Lockpicks: " << lockpicks << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Unique Items: " <<endl;
        cout << "-----------------------------------------------" << endl;
        for (int i=0; i < inventorySize; i++) {
            cout << "Item " << i + 1 << ": " << itemInventory[i] << endl;
        }
        cout << "===============================================" << endl << endl;
    }
};


// vendor class
// to make a vendor, you need to give a size and create a array of pairs with the same size
// first pair value is the name of the item, to be added to your inventory, the second is the price
class Vendor {
private:
    // max size is not constant, set in constructor
    int inventorySize;
    //vendor inventory is a pair array, first value is item name, second is price
    pair<string, int>* vendorInventory;
public:
    // no default constructor, vendor must have a array
    Vendor(int size, pair<string,int> vendorInventory[]) {
        inventorySize = size;
        this->vendorInventory = vendorInventory;
    }

    // shop method, takes inventory class as argument, int type because the value returned is the total coins to be removed
    int shop(Inventory playerInventory) {
        int userInput = 0;
        int coinsSpent = 0;
        while (userInput != inventorySize + 1) {
            cout << endl << "===============================================" << endl;
            cout << "Your Coins: " << playerInventory.getCoins() << endl;
            cout << "-----------------------------------------------" << endl;
            cout << "Vendor Inventory: " << endl;
            cout << "===============================================" << endl;
            for (int i=0; i < inventorySize; i++) {
                cout << "Item " << i + 1 << ": " << vendorInventory[i].first << " Price: " << vendorInventory[i].second  << endl;
            }
            cout << "-----------------------------------------------" << endl;
            cout << "What would you like to purchase? " << inventorySize + 1  << " to quit: " << endl;
            cin >> userInput;
            if ((userInput <= inventorySize) && !(vendorInventory[userInput -1].first == "SOLD")) {
                userInput = userInput -1;
                if (playerInventory.hasCoins(vendorInventory[userInput].second)) {
                    playerInventory.addItem(vendorInventory[userInput].first);
                    playerInventory.removeCoins(vendorInventory[userInput].second);
                    coinsSpent = coinsSpent + vendorInventory[userInput].second;
                    pair<string, int> sold = {"SOLD", NULL};
                    vendorInventory[userInput] = sold;
                    cout << "Item sold!" << endl;
                }
                else {
                    cout << "Not enough coins" << endl;
                }
            }
            if (userInput == inventorySize +1) {
                cout << "Leaving shop..." << endl;
            }
        }
        return coinsSpent;
    }
    /// Put this code in your main if you want to see how it works
    /*
    //inventory created and coins added
    Inventory playerInventory;
    playerInventory.addCoins(1000);
    // pair array
    pair<string, int> vendorInventory[5] = {{"Sword", 100}, {"Rope", 75}, {"Pickaxe", 150}, {"Apple", 5}, {"Diamond", 1000}};
    // vendor created
    Vendor vendor1= Vendor(5, vendorInventory);
    //calling shop
    int coinsSpent =vendor1.shop(playerInventory);
    // make sure to update amount of coins
    playerInventory.removeCoins(coinsSpent);

    playerInventory.display();
    return 0;

    */
};

#endif // INVENTORYSYSTEM_H
