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
    float size;

    Bullet();
    Bullet(Texture& texture);

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
    float playerSpeed;
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

    vector<Bullet> bullets;
    Vector2f currVelocity;
    Vector2f bAimDirNorm;
    Vector2f bossCenter;
    Vector2f bAimDir;

    Boss(Texture* texture, int round);
    ~Boss() {}

};
//-------------------------------
Vector2f rolldice();

Vector2f rotaionMatrix(Vector2f v, int angle);

class Weapon
{
public:
    Sprite shape;
    int type; // type1 = normal gun ; type2 = machine gun; type3 = ?;
    Weapon(Texture& tex, float n, int t);
};
