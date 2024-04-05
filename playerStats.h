#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <iostream>
using namespace std;

class PlayerStats{
private:
    string className;
    int strength;
    int hp;
    int defense;
    int speed;
    int dextarity;
public:
    //getters
    string getClassName() { return className; }
    int getStrength() { return strength; }
    int getHP() { return hp; }
    int getDefense() { return defense; }
    int getSpeed() { return speed; }
    int getDextarity() { return dextarity; }

    //increase stats - similar to a setter
    void incStrength(int addStrength) {strength += addStrength;}
    void incHP(int addHP) {hp += addHP;}
    void incDefense(int addDefense) {defense += addDefense;}
    void incSpeed(int addSpeed) {speed += addSpeed;}
    void incDextarity(int addDextarity) {dextarity += addDextarity;}

    //construcor
    PlayerStats(string _className, int _strength, int _hp, int _defense, int _speed, int _dextarity){
        className = _className;
        strength = _strength;
        hp = _hp;
        defense = _defense;
        speed = _speed;
        dextarity = _dextarity;
    }
    PlayerStats() {}
    //retrieve player stats based on chosen player ID
    void getPlayerStats(int classID){
        switch(classID){
        case 1:
            //warrior stats
            className = "warrior";
            strength = 15;
            hp = 30;
            defense = 8;
            speed = 8;
            dextarity = 22;
            break;
        case 2:
            //ranger stats
            className = "ranger";
            strength = 10;
            hp = 25;
            defense = 6;
            speed = 13;
            dextarity = 55;
            break;
        case 3:
            //sorcerer stats
            className = "sorcerer";
            strength = 20;
            hp = 20;
            defense = 3;
            speed = 10;
            dextarity = 40;
            break;
        case 4:
            //rouge stats
            className = "rouge";
            strength = 7;
            hp = 16;
            defense = 5;
            speed = 16;
            dextarity = 75;
            break;
        }

    }
};



#endif // PLAYERSTATS_H
