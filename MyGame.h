#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;



class Bullet
{

public:
    Sprite shape;
    Vector2f currVelocity;
    float maxSpeed;


    Bullet(Texture* texture);
    ~Bullet() {}
};

class Shield
{
public:
    Sprite shape;

    Shield(Texture* texture, Vector2f pos);
    ~Shield() {}

};

class Player
{
public:
    Sprite shape;
    Texture* texture;

    int lvl = 1;
    int exp = 0;

    int HP;
    int HPMax;

    int MP;
    int MPMax;

    // for bullets
    vector<Bullet> bullets;
    Vector2f currVelocity;
    float maxSpeed;

    // for shield 
    vector<Shield> shield;

    Player(Texture* texture);
    ~Player() {}

};

class Boss
{
public:
    Sprite shape;

    int HP;
    int HPMax;
    RectangleShape bHpBar;
    Vector2f bAimDirNorm;

    vector<Bullet> bullets;
    Vector2f currVelocity;

    Boss(Texture* texture);
    ~Boss() {}

};
