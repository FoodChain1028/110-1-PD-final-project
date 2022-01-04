#include"MyGame.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Bullet::Bullet(Texture* texture) : currVelocity(0.f, 0.f), maxSpeed(10.f)
{
    this->shape.setTexture(*texture);
    this->shape.setScale(Vector2f(0.03f, 0.03f));
    this->shape.rotate(90);
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

    this->shape.setScale(Vector2f(0.15f, 0.15f));
}

Boss::Boss(Texture* texture)
{
    this->HPMax = 500;
    this->HP = this->HPMax;

    this->shape.setTexture(*texture);

    this->shape.setScale(0.5f, 0.5f);

}