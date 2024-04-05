#ifndef ENEMYSTATS_H
#define ENEMYSTATS_H
class entity {
public:
    int Speed;
    int Strength;
    int Dextarity;
    int Defence;
    int Health;
    int Turn;

    int getHP(){return Health;}
};
class guard :public entity{
public:
    int gSpeed = 8;
    int gStrength = 5;
    int gDextarity = 25;
    int gDefence = 5;
    int gHealth = 15;
    guard() {
        Speed = gSpeed;
        Strength = gStrength;
        Dextarity = gDextarity;
        Defence = gDefence;
        Health = gHealth;
    }
};
class armoredGuard :public entity{
public:
    int agSpeed = 8;
    int agStrength = 10;
    int agDextarity = 25;
    int agDefence = 10;
    int agHealth = 20;
    armoredGuard() {
        Speed = agSpeed;
        Strength = agStrength;
        Dextarity = agDextarity;
        Defence = agDefence;
        Health = agHealth;
    }
};
class dog :public entity{
public:
    int dSpeed = 14;
    int dStrength = 5;
    int dDextarity = 75;
    int dDefence = 2;
    int dHealth = 8;
    dog() {
        Speed = dSpeed;
        Strength = dStrength;
        Dextarity = dDextarity;
        Defence = dDefence;
        Health = dHealth;
    }
};
class rat :public entity{
public:
    int rSpeed = 20;
    int rStrength = 1;
    int rDextarity = 80;
    int rDefence = 0;
    int rHealth = 1;
    rat() {
        Speed = rSpeed;
        Strength = rStrength;
        Dextarity = rDextarity;
        Defence = rDefence;
        Health = rHealth;
    }
};
class warden :public entity{
public:
    int wSpeed = 2;
    int wStrength = 8;
    int wDextarity = 10;
    int wDefence = 12;
    int wHealth = 100;
    warden() {
        Speed = wSpeed;
        Strength = wStrength;
        Dextarity = wDextarity;
        Defence = wDefence;
        Health = wHealth;
    }
};
class prisoner :public entity{
public:
    int pSpeed = 6;
    int pStrength = 1;
    int pDextarity = 20;
    int pDefence = 0;
    int pHealth = 4;
    prisoner() {
        Speed = pSpeed;
        Strength = pStrength;
        Dextarity = pDextarity;
        Defence = pDefence;
        Health = pHealth;
    }
};
class swordGuard :public entity{
public:
    int sgSpeed = 8;
    int sgStrength = 25;
    int sgDextarity = 25;
    int sgDefence = 0;
    int sgHealth = 6;
    swordGuard() {
        Speed = sgSpeed;
        Strength = sgStrength;
        Dextarity = sgDextarity;
        Defence = sgDefence;
        Health = sgHealth;
    }

};
#endif // ENEMYSTATS_H
