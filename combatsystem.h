#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H
#include<iostream>
#include<cstdlib>
using namespace std;
/// Speed defines the order of combat, Strength is the base damage and can be improved with tools,
/// Dextarity is a range from 0 to 100 and is the percent chance for a crit, Health is how many hit points an aponent or charecter has
/// Defence is a buffer that reduces damage

/// Blocks with Stats need to be made for oponents
/// combat functions need to made to work with everything working properly
/// ballence will be made later as charecter stats are being made seperate
/// make crits have a set value does it double damage or is there a dependent variable

/// Asumed base (character with 20 health 5 Strength 25 Dextarity 5 Defence(or 40/100) 10 speed)
/// Gaurd with 15 Health(3*base Strength) 5 Strength(1/4*Base Health) 25 Dextarity 5 Defence(or 40/100) and 8 Speed (Below base speed) (Assumed base)
/// Dog with 8 Health(under 2*base Strength ~ 1.5*base stregth) 5 Strength(1/4*Base Health) 75 Dextarity 2 Defence(or 25/100) and 14 Speed (Above base Speed) (Assumed base)
/// Prisoner with 4 Health(below base Strenth)  1 Strength (Minimum damadge) 20 Dextarity 0 Defence(or 10/100) and 6 Speed(almost half base speed) (Assumed base)
/// A higher level Gaurd with 20 Health(4*base Strength) 10 Strength(1/2*base Health) 25 Dextarity 10 Defence(or 75/100) and 8 Speed (Below base speed) (Assumed base)
/// A boss with 100 Health(20*base strength) 8 Strength(2/5*base health) 10 Dextarity 12 Defence(or 50/100) and 2 Speed (2 speed) (Assumed base)
/// rats with 1 Health(min health) 1 Strength(min strength) 80 Dextarity 0 Defence(or 10/100) and 20 Speed(2* base speed) (Assumed base)
/// A Recless Aponent with 6 Health(slightly above base strength) 25 Strength(5/4* base health) 25 Dextarity 0 Defence(or 0/100) and 12 Speed(slightly above base speed) (Assumed base)

/// Use Player stats to influence events based on asumed base Dextarity to unlock things Strength to move/destroy stuff ~speed to move faster
#include<iostream>
#include<cstdlib>
#include "playerStats.h"
#include "enemyStats.h"
using namespace std;
/// Speed defines the order of combat, Strength is the base damage and can be improved with tools,
/// Dextarity is a range from 0 to 100 and is the percent chance for a crit, Health is how many hit points an aponent or charecter has
/// Defence is a buffer that reduces damage

/// Blocks with Stats need to be made for oponents
/// combat functions need to made to work with everything working properly
/// ballence will be made later as charecter stats are being made seperate
/// make crits have a set value does it double damage or is there a dependent variable

/// Asumed base (character with 20 health 5 Strength 25 Dextarity 5 Defence(or 40/100) 10 speed)
/// Gaurd with 15 Health(3*base Strength) 5 Strength(1/4*Base Health) 25 Dextarity 5 Defence(or 40/100) and 8 Speed (Below base speed) (Assumed base)
/// Dog with 8 Health(under 2*base Strength ~ 1.5*base stregth) 5 Strength(1/4*Base Health) 75 Dextarity 2 Defence(or 25/100) and 14 Speed (Above base Speed) (Assumed base)
/// Prisoner with 4 Health(below base Strenth)  1 Strength (Minimum damadge) 20 Dextarity 0 Defence(or 10/100) and 6 Speed(almost half base speed) (Assumed base)
/// A higher level Gaurd with 20 Health(4*base Strength) 10 Strength(1/2*base Health) 25 Dextarity 10 Defence(or 75/100) and 8 Speed (Below base speed) (Assumed base)
/// A boss with 100 Health(20*base strength) 8 Strength(2/5*base health) 10 Dextarity 12 Defence(or 50/100) and 2 Speed (2 speed) (Assumed base)
/// rats with 1 Health(min health) 1 Strength(min strength) 80 Dextarity 0 Defence(or 10/100) and 20 Speed(2* base speed) (Assumed base)
/// A Recless Aponent with 6 Health(slightly above base strength) 25 Strength(5/4* base health) 25 Dextarity 0 Defence(or 0/100) and 12 Speed(slightly above base speed) (Assumed base)

/// Use Player stats to influence events based on asumed base Dextarity to unlock things Strength to move/destroy stuff ~speed to move faster

/// Class combat is more polished however still needs to be set to change with entitys in combat
class Combat{
public:
    int playerHP;
    int enemyHP;
    bool playerTurn;
    int crit = 0;
    int damage= 0;
    int round=0;
    bool combat = false;
    bool block = false;
    // true - player first, false - enemy first
    void Initate(PlayerStats player, entity enemy){
        if (combat == false){
            if (player.getSpeed() > enemy.Speed){
                playerTurn = true;
            }
            else{
                playerTurn = false;
            }
        }
        else {
            throw invalid_argument("Error: Already in Combat");
        }

    }

    //true player turn, false enemy first
    bool turn() {
        if (playerTurn) {
            playerTurn = false;
            return true;
        }
        else {
            playerTurn = true;
            return false;
        }

    }
    //constructor sets player hp, since hp will be fully regained outside of combat
    Combat(PlayerStats player, entity enemy) {
        playerHP = player.getHP();
        Initate(player, enemy);
        enemyHP = enemy.Health;
    }
    //player attack - if it returns false, enemy is dead
    bool pAttack(PlayerStats player, entity enemy){
        if(block == true){
            int chance = 1+rand()%100;
            if (chance <= 50){
                crit = 1+rand()%100;
                if(crit <= player.getDextarity()){
                    cout << "Critical Hit" << endl;
                    damage = (3*player.getStrength()) - enemy.Defence;
                    if (damage > 0){
                        enemyHP = enemyHP - damage;
                    }
                    if (enemyHP <= 0){
                        cout << "Enemy has died" << endl;
                        return false;
                    }
                    else{
                        cout <<"Enemy Health: "  << enemyHP<< endl;
                        return true;
                    }
                }
                else{
                    damage = (1.25*player.getStrength())-enemy.Defence;
                    if (damage > 0){
                        enemyHP = enemyHP - damage;
                    }
                    if (enemyHP <= 0){
                        cout <<  "Enemy has died" << endl;
                        return false;
                    }
                    else{
                        cout <<"Enemy Health: " << enemyHP << endl;
                        return true;
                    }
                }
                block = false;
            }
            else{
                cout << "miss" << endl;
                return true;
                block = false;
            }
        }
        else{
            crit = 1+rand()%100;
            if(crit <= player.getDextarity()){
                cout << "Critical Hit" << endl;
                damage = (3*player.getStrength()) - enemy.Defence;
                if (damage > 0){
                    enemyHP = enemyHP - damage;
                }
                if (enemyHP <= 0){
                    cout <<"Enemy has died" << endl;
                    return false;
                }
                else{
                    cout <<"Enemy Health: " << enemyHP << endl;
                    return true;
                }
            }
            else{
                damage = (1.25*player.getStrength())-enemy.Defence;
                if (damage > 0){
                    enemyHP = enemyHP - damage;
                }
                if (enemyHP <= 0){
                    cout << "Enemy has died" << endl;
                    return false;
                }
                else{
                    cout <<"Enemy Health: " <<  enemyHP << endl;
                    return true;
                }
            }
        }
    }

    //enemy attack, if it returns false, player is dead
    bool eAttack(PlayerStats player, entity enemy){
        if(block == true){
            int chance = 1+rand()%100;
            if (chance <= 50){
                crit = 1+rand()%100;
                if(crit <= enemy.Dextarity){
                    cout << "Critical Hit" << endl;
                    damage = (2*enemy.Strength) - player.getDefense();
                    if (damage > 0){
                        playerHP = playerHP - damage;
                    }
                    if (playerHP <= 0){
                        cout << "You have died..." << endl;
                        return false;
                    }
                    else{
                        cout << "Your health: " << playerHP << endl;
                        return true;
                    }
                }
                else{
                    damage = (enemy.Strength) - player.getDefense();
                    if (damage > 0){
                        playerHP = playerHP - damage;

                    }
                    if (playerHP <= 0){
                        cout << "You have died..." << endl;
                        return false;
                    }
                    else{
                        cout << "Your health: " << playerHP << endl;
                        return true;
                    }
                }
                block = false;
            }
            else{
                cout << "miss" << endl;
                block = false;
                return true;
            }
        }
        else{
            crit = 1+rand()%100;
            if(crit <= player.getDextarity()){
                cout << "Critical Hit" << endl;
                damage = (5*enemy.Strength) - player.getDefense();
                if (damage > 0){
                    playerHP = playerHP - damage;
                }
                if (playerHP <= 0){
                    cout << "You have died..." << endl;
                    return false;
                }
                else{
                    cout << "Your health: " << playerHP << endl;
                    return true;
                }
            }
            else{
                damage = (3*enemy.Strength) - player.getDefense();
                if (damage > 0){
                    playerHP = playerHP - damage;
                }
                if (playerHP <= 0){
                    cout << "You have died..." << endl;
                    return false;
                }
                else{
                    cout << "Your health: " << playerHP << endl;
                    return true;
                }
            }
        }
    }

    void Block(){
        block = true;
        /// Set Block value to an entiy so block does not cary to opponents or gets canceled early
        cout << "You brace yourself for an incoming attack" << endl;
    }
    void Flee(PlayerStats player){
        int fChance = 1+rand()%100;
        if (fChance <= player.getDextarity()){
            combat = false;
            cout << "You get away" << endl;
        }
        else{
            cout << "You fail to get away" << endl;
        }

    }
};

// call this function for combat in story
// if true player wins
bool battle(PlayerStats player, entity enemy) {
    Combat inCombat = Combat(player, enemy);
    // status of both enemy and player
    bool playerStatus = true;
    bool enemyStatus = true;
    //initiate combat
    while (playerStatus && enemyStatus) {
        // if players turn
        bool playerUp = inCombat.turn();
        if (playerUp) {
            //user input
            int userInput;
            cout << endl << "Choose your action! " << endl;
            cout << "1. Attack" << endl <<"2. Block" << endl << "3. Flee" << endl;
            cout <<"Enter Action: ";
            cin >> userInput;
            cout << endl;
            // input validation
            while (userInput < 1 || userInput > 3) {
                cout << "Invalid input (1-3): " << endl;
                cin >> userInput;
            }
            // attack
            if (userInput == 1) {
                bool results = inCombat.pAttack(player, enemy);
                if (!results) {
                    enemyStatus = false;
                }
            }
            // block
            else if (userInput == 2) {
                inCombat.Block();
            }
            //flee
            else if (userInput == 3) {
                inCombat.Flee(player);
                if (!inCombat.combat) {
                    enemyStatus = false;
                }
            }
        }
        //enemies turn - always attacks
        else {
            cout << "Enemy attacks!" << endl;
            bool results = inCombat.eAttack(player, enemy);
            if (!results) {
                playerStatus = false;
            }
        }
    }
    if (!playerStatus) {
        cout << "Game over!" << endl;
        return false;
    }
    else {
        return true;
    }
}
#endif // COMBATSYSTEM_H
