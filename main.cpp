#include "enemyStats.h"
#include "combatsystem.h"
#include "inventorysystem.h"
#include <ctime>
#include "playerStats.h"

// temp battle function
void battle()
{
    cout << "You encounter an enemy!\n";
    // Simulating battle logic here
    // For simplicity, determining a random outcome
    srand(time(nullptr));              // Seed the random number generator
    bool playerWins = rand() % 2 == 0; // 50% chance of winning
    if (playerWins)
    {
        cout << "You defeated the enemy!\n";
    }
    else
    {
        cout << "You were defeated by the enemy!\n";
    }
}

int main()
{
    cout << "Welcome to the Adventure Game!\n";

    // Character creation
    string playerName;
    cout << "Enter your character's name: ";
    getline(cin, playerName);

    // class selection
    int classID = 0;
    PlayerStats player;

    cout << "Please select a battle class for your player(warrior = 1, ranger = 2, sorcerer = 3, rouge = 4):";
    cin >> classID;
    while (classID > 4 || classID < 1)
    {
        cout << "Please enter a valid ID (1 - 4):";
        cin >> classID;
    }
    player.getPlayerStats(classID);

    cout << "\n";
    cout << "Welcome, " << playerName << " the " << player.getClassName() << "!\n";
    cout << "Let's begin your adventure...\n";

    // inventory created
    Inventory playerInventory;
    // bag attempts value for route 1
    int bagAttempts = 3;
    // Main game loop
    while (true)
    {
        cout << "\nYou wake up, head throbbing, in a unfamiliar prison cell. You have no recollection of how you got here. \n"
                "Dazed, you try to gather your surroundings. Immediately grabbing your attention, the cell bars seem to be made \n"
                "of metal. They are thoroughly rusted, how long have you been here? The stone walls around you are decaying, \n"
                "perhaps warranting further inspection. \n";
        cout << "1. Check the walls\n";
        cout << "2. Check the door\n";
        cout << "3. quit game\n";
        cout << "Enter your choice (1-3): ";

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nWalking closer to the walls, you notice a cool breeze coming from it. Looking more closely,\n"
                    "you realize that not only is there a hole in the wall, but there is something on the other side of the \n"
                    "wall. You check behind you to make sure no one is watching, and then begin to frantically remove the stone \n"
                    "bricks that make up the area around the hole in the wall. After a short while, you step through the opening \n"
                    "you have created and find yourself in a cavern behind the dungeon. \n";
            cout << "\nThe cave splits two different directions, but the faint light from the hole in the wall is nowhere near\n"
                    "enough to illuminate your journey. Luckily, you spot the remnants of a spelunkers supplies, with an extinguished\n"
                    "torch among them.\n";
            playerInventory.addItem("Extinguished Torch");
            cout << "\nBefore continuing on, you need to find a way to light the torch, what would you like to do?\n";

            // torch is required to continue
            // variable declared here is used for option 1
            while (!playerInventory.hasItem("Torch"))
            {
                bool canCraftTorch = (playerInventory.hasItem("Steel Pickaxe Head") && playerInventory.hasItem("Stone"));
                cout << "\n1. Search through the spelunkers bag\n"
                        "2. Grab a stone\n"
                        "3. Check Inventory \n";
                if (canCraftTorch)
                {
                    cout << "4. Strike pickaxe head and stone to light torch\n";
                }
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
                // first bag draw is always pickaxe head
                if (choice == 1 && bagAttempts == 3)
                {
                    cout << "Continuing to rummage through the spelunkers belongings, you find an old steel pickaxe head.\n";
                    playerInventory.addItem("Steel Pickaxe Head");
                    cout << "The bag seems to still have something in it, you may continue looking through it if you wish \n";
                    bagAttempts--;
                }
                // subsequent bag draws are randomized for variety
                else if ((choice == 1) && (0 < bagAttempts) && (bagAttempts < 3))
                {
                    srand(time(nullptr));
                    int randCase = rand() % 2 + 1;
                    switch (randCase)
                    {
                    case 1:
                        cout << "You find 50 coins!\n";
                        playerInventory.addCoins(50);
                        break;
                    case 2:
                        cout << "You find a lockpick!\n";
                        playerInventory.addLockpicks(1);
                        break;
                    }
                    bagAttempts--;
                    if (bagAttempts > 0)
                    {
                        cout << "The bag still appears to have something in it\n";
                    }
                }
                // bag attempts exhausted
                else if ((choice == 1) && (bagAttempts == 0))
                {
                    cout << "The bag is empty \n";
                }
                // grabbing a stone
                else if (choice == 2 && (!playerInventory.hasItem("Stone")))
                {
                    cout << "You grab a loose stone off the cavern floor. What could you use this for?\n";
                    playerInventory.addItem("Stone");
                }
                // prevents grabbing more than one stone
                else if (choice == 2)
                {
                    cout << "You probably don't need another stone... \n";
                }
                // check inventory
                else if (choice == 3)
                {
                    playerInventory.display();
                }
                //
                else if (choice == 4 && canCraftTorch)
                {
                    cout << "You place the torch on the ground, then promptly begin to strike the stone along the side of \n"
                            "the pickaxe head. Just as you are about to give up, a spark catches on the torch!\n";
                    playerInventory.removeItem("Steel Pickaxe Head");
                    playerInventory.removeItem("Extinguished Torch");
                    playerInventory.removeItem("Stone");
                    playerInventory.addItem("Torch");
                }
                else
                {
                    cout << "Invalid input, please enter a number within range\n";
                }
            }

            // continue - implemented to break long walls of text if the user misses a event
            cout << "1. Continue\n"
                    "2. Check inventory\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
            while (choice != 1 && choice != 2)
            {
                cout << "Please enter 1 or 2\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
            }
            if (choice == 2)
            {
                playerInventory.display();
                cout << "Continuing...\n";
            }

            cout << "Now that you have a torch, the route ahead is open to you. Looking to your right, you notice the \n"
                    "light from your torch has been reflected by something metallic. You also hear some faint skittering noises, \n"
                    "what could it be? On the left, your torchlight fades quickly, leaving only darkness.\n"
                    "You hear only silence, perhaps the lack of noise is reassuring to you. \n";
            cout << "\nWhich way would you like to go?\n"
                    "1. Right\n"
                    "2. Left\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
            while (choice != 1 && choice != 2)
            {
                cout << "Please enter 1 or 2\n";
                cin >> choice;
                cout << "\n";
            }
            if (choice == 1)
            {
                cout << "As you approach the reflection, you realize it to be a pile of gold coins!\n"
                        "You pocket 150 gold\n";
                playerInventory.addCoins(150);
                cout << "While looting the coins, a rat emerges from the darkness! It has a feral look in its eyes, \n"
                        "You have no choice but to fight.\n";
                rat rat1;
                bool resultsFight1 = battle(player, rat1);
                if (!resultsFight1)
                {
                    return 0;
                }
                cout << "It seems this corridor was a dead end, leaving you no option but to retrace your steps and go left. \n\n";
                // continue - implemented to break long walls of text if the user misses a event
                cout << "1. Continue\n"
                        "2. Check inventory\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
                while (choice != 1 && choice != 2)
                {
                    cout << "Please enter 1 or 2\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cout << "\n";
                }
                if (choice == 2)
                {
                    playerInventory.display();
                    cout << "Continuing...\n\n";
                    ;
                }
            }
            cout << "As you go down the left corridor, you come across an old chest on the ground. Looking more closely, \n"
                    "you realize it's locked. If you have a lockpick, you may use it here. \n";
            // gives option for user to use lockpicks if they have them
            if (playerInventory.hasLockpicks())
            {
                cout << "You have a lockpick, would you like to use it here?\n"
                        "1. Yes\n"
                        "2. No\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
                while (choice != 1 && choice != 2)
                {
                    cout << "Please enter 1 or 2\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cout << "\n";
                }
                if (choice == 1)
                {
                    cout << "You found 100 coins \n\n"
                         << endl;
                    playerInventory.addCoins(100);
                }
                else if (choice == 2)
                {
                    cout << "You decide not to open the chest, time to move one. \n\n";
                }
            }
            // no lockpicks
            else
            {
                cout << "Unfortunately, you don't, leaving no option but to give up \n"
                        "on the chest.\n";
            }
            // continue - implemented to break long walls of text if the user misses a event
            cout << "1. Continue\n"
                    "2. Check inventory\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
            while (choice != 1 && choice != 2)
            {
                cout << "Please enter 1 or 2\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
            }
            if (choice == 2)
            {
                playerInventory.display();
                cout << "Continuing...\n";
            }

            cout << "Carrying on, you see light coming from the right side of the cavern \n"
                    "closing in on it, you realize it to be a hole in a brick wall similar \n"
                    "to the walls of your cell. It looks like an entrance to a different part of \n"
                    "the dungeon. Good timing, because the cave comes to a stop shortly after \n"
                    "Entering the dungeon, a guard immediately notices you. He quickly takes a \n"
                    "look at your apparel, and in response readies his weapon. There's no \n"
                    "escaping a fight.\n";
            // fight function goes here
            if (choice == 1 || choice == 2)
            {
                guard guard;
                bool results = battle(player, guard);
                if (!results)
                {
                    return 0;
                }
            }
            // continue - implemented to break long walls of text if the user misses a event
            cout << "\n1. Continue\n"
                    "2. Check inventory\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
            while (choice != 1 && choice != 2)
            {
                cout << "Please enter 1 or 2\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
            }
            if (choice == 2)
            {
                playerInventory.display();
                cout << "Continuing...\n";
            }
            cout << "You notice that, watching the whole time, was some sort of trader. He \n"
                    "seems unabashed by you emerging victorious from the fight, \n"
                    "indicating perhaps he held little regard for the guard you dispatched. \n\n"
                    "Traveling Merchant: What, you think I'm gonna to run screaming? That guard had no \n"
                    "coin to barter with, so he was hardly worth my time anyway. Warden's office and the exits just up ahead. \n"
                    "Right now yer in no shape to beat him, but with my supplies maybe you'll stand a chance. \n";
            cout << "\nWould you like to barter? \n"
                    "1. Yes\n"
                    "2. No\n";
            cout << "Enter your choice: ";
            cin >> choice;
            while (choice != 1 && choice != 2)
            {
                cout << "\nPlease enter 1 or 2\n";
                cout << "Enter your choice: ";
                cin >> choice;
            }
            if (choice == 1)
            {
                pair<string, int> vendorInventory[3] = {{"Mythril Chainmail", 100}, {"Max HP+ Potion", 50}, {"Stat+ Potion", 100}};
                Vendor travellingMerchant = Vendor(3, vendorInventory);
                int coinsSpent = travellingMerchant.shop(playerInventory);
                playerInventory.removeCoins(coinsSpent);
            }
            if (playerInventory.checkAndRemoveItem("Max HP+ Potion"))
            {
                cout << "\nUsing max HP potion...\n";
                player.incHP(10);
                cout << "Player HP increased by 10\n";
            }
            if (playerInventory.checkAndRemoveItem("Stat+ Potion"))
            {
                cout << "\n Using Stat+ Potion...\n";
                player.incDefense(3);
                player.incDextarity(3);
                player.incSpeed(3);
                player.incStrength(3);
                cout << "All stats but HP increased by 3\n";
            }
            // continue - implemented to break long walls of text if the user misses a event
            cout << "\n1. Continue\n"
                    "2. Check inventory\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << "\n";
            while (choice != 1 && choice != 2)
            {
                cout << "Please enter 1 or 2\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cout << "\n";
            }
            if (choice == 2)
            {
                playerInventory.display();
                cout << "Continuing...\n";
            }
            cout << "\nLike the merchant said, the wardens office is up ahead, but so is the exit. You gather your wits, \n"
                    "and step through the doorway. The warden, a tall armored individual, immediately takes notice and \n"
                    "grabs the weapon leaning against his desk. Get ready for a fight!! \n";
            // final boss fight will go here
            if (choice == 1 || choice == 2)
            {
                warden warden;
                bool results = battle(player, warden);
                while (!results && playerInventory.hasItem("Mythril Chainmail"))
                {
                    cout << "...Or so you think, but you realize the fatal blow was stopped by your mythril chainmail,\n"
                            "however it won't be able to take another hit like that.\n";
                    playerInventory.removeItem("Mythril ChainMail");
                    cout << "you gather your breath, but so too does the warden, both of your HP's have refilled!\n";
                    class warden warden2;
                    results = battle(player, warden2);
                }
                if (!results)
                {
                    return 0;
                }
            }
            cout << "\nCatching your breath, you watch as the warden plummets to the ground. You are victorious! \n"
                    "You begin to stagger towards the exit, its been so long since you've seen sunlight that the\n"
                    "light emanating from the doorway nearly blinds you. As you step through the doorway, fresh \n"
                    "air fills your lungs. Congratulations, you're free!\n";
            cout << "\nThanks for playing!!\n";
            return 0;
            break;

        case 2:
            cout << "You walk up to the cell bars, checking the area outside your cell. No signs of human life around you, all \n"
                    "the cells adjacent and opposing you are empty. \n";
            cout << "1. Check the door \n";
            cout << "2. Rattle the bars \n";
            cin >> choice;
            while (choice != 1 && choice != 2)
            {
                cout << "invalid choice, try again \n";
                cin >> choice;
            }
            while (choice == 2)
            {
                cout << "You rattle the bars violently, rusty as they are, the bars show no sign of giving \n";
                cout << "1. Check the door \n";
                cout << "2. Rattle the bars \n";
                cin >> choice;
            }
            cout << "The door easily swings open, it seems the lock has long since been defunct. Stepping out you have the option to go right or left in the dungeon \n";
            // Johnnie's route
            break;
        case 3:
            cout << "Exiting game. Goodbye, " << playerName << "!\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }

    return 0;
}
