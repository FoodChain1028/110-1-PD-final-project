#include"MyGame.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;


const double PI = 3.14159;
const int height = 1600;
const int width = 800;
Bullet::Bullet()
{
    maxSpeed = 10.f;
    size = 0.02f;
};

Bullet::Bullet(Texture& texture)
{
    this->shape.setTexture(texture);
    this->shape.setScale(Vector2f(0.02f, 0.02f));
    currVelocity = Vector2f(0.f, 0.f);
    maxSpeed = 10.f;
    size = 0.02f;
}

Shield::Shield(Texture* texture, Vector2f pos)
{
    this->shape.setTexture(*texture);
    this->shape.setScale(0.1f, 0.1f);
    this->shape.setPosition(pos);
}

Player::Player(Texture* texture)
{
    this->HPMax = this->lvl * 103 + 53;
    this->HP = this->HPMax;

    this->MPMax = this->lvl * 103 + 53;
    this->MP = this->MPMax;

    this->texture = texture;
    this->shape.setTexture(*texture);

    this->shape.setScale(Vector2f(0.5f, 0.5f));

    this->playerSpeed = 3.f;
}

Boss::Boss(Texture* texture, int round)
{
    if (round == 1)
    {
        this->HPMax = 300;
    }

    else if (round == 2)
    {
        this->HPMax = 1000;
    }

    this->HP = this->HPMax;

    this->shape.setTexture(*texture);

    this->shape.setScale(0.5f, 0.5f);

}
//-------------------------------------------
Vector2f rolldice()
{
    float x = 50.0;
    float y = 50.0;
    x += static_cast<float>(rand() % (height - 50));
    y += static_cast<float>(rand() & (width - 50));
    return Vector2f(x, y);
}

Vector2f rotaionMatrix(Vector2f v, int angle)
{
    float x = v.x * cos(angle * (PI / 180)) - v.y * sin(angle * (PI / 180));
    float y = v.x * sin(angle * (PI / 180)) + v.y * cos(angle * (PI / 180));
    return Vector2f(x, y);
}

Weapon::Weapon(Texture& tex, Vector2f n, int t)
{
    this->type = t;
    this->shape.setTexture(tex);
    this->shape.setScale(Vector2f(0.2f, 0.2f));
    this->shape.setPosition(n);
}
