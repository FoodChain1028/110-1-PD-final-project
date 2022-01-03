#include<iostream>
#include <sstream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<cmath>
#include<vector>
using namespace std;
using namespace sf;

class Bullet
{
public:
    Sprite shape;
    Vector2f currVelocity;
    float maxSpeed;
    Bullet(Texture &tex)
    {   
        this->shape.setTexture(tex);
        this->shape.setScale(Vector2f(0.02f, 0.02f));
        currVelocity = Vector2f(0.f, 0.f);
        maxSpeed = 10.f;
    };
};


int main()
{   
    RenderWindow window(VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);

    // player
    Sprite player;
    Texture playerTex;
    playerTex.loadFromFile("textures/player.png");
    player.setTexture(playerTex);
    player.setScale(Vector2f(0.5f, 0.5f));
    bool haveGun = false;

    // weapon
    Sprite gun;
    Texture gunTex;
    gunTex.loadFromFile("textures/gun.png");
    gun.setTexture(gunTex);
    gun.setScale(Vector2f(0.2f, 0.2f));
    gun.setPosition(400.f, 400.f);

    // vector
    Vector2f gunCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;

    // bullet
    Texture gunBulletTex;
    gunBulletTex.loadFromFile("textures/gunBullet.png");
    Bullet b1(gunBulletTex);
    vector<Bullet> bullets;
 
    // text
    Font font;
    font.loadFromFile("font/Arial.ttf");
    int cnt = 100;


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        //-------------- update------------------------

        // player
        if (Keyboard::isKeyPressed(Keyboard::W))
            player.move(0.f, -3.f);
        if (Keyboard::isKeyPressed(Keyboard::S))
            player.move(0.f, 3.f);
        if (Keyboard::isKeyPressed(Keyboard::D))
            player.move(3.f, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::A))
            player.move(-3.f, 0.f);

        // vector
        gunCenter = Vector2f(gun.getPosition().x, gun.getPosition().y);
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDir = mousePosWindow - gunCenter;
        aimDirNorm = Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

        // take gun
        
        if (player.getGlobalBounds().intersects(gun.getGlobalBounds()) && haveGun == false)
        {
            haveGun = true;
        }
        else if (haveGun == true)
        {
            gun.setPosition(player.getPosition().x + 85.f, player.getPosition().y - 20.f);
        }

        if (cnt <= 0)
            haveGun = false;

        // shooting
        if (Mouse::isButtonPressed(Mouse::Left) && haveGun == true)
        {   
            b1.shape.setPosition(gunCenter);
            b1.currVelocity = aimDirNorm * b1.maxSpeed;
            bullets.push_back(Bullet(b1));
            cnt--;
        }
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].shape.move(bullets[i].currVelocity);
            //Out of bounds
            if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
                || bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
            {
                bullets.erase(bullets.begin() + i);
            }
        }
        // bullet count
        Text bulletCnt(to_string(cnt), font);
        if (haveGun == true)
        {
            bulletCnt.setPosition(Vector2f(750.f, 550.f));
            bulletCnt.setCharacterSize(30);
            bulletCnt.setStyle(Text::Bold);
            bulletCnt.setFillColor(Color::Red);
        }

        //------------ draw----------------------------
        window.clear();
        
        window.draw(player);
        window.draw(gun);
        if(haveGun == true)
            window.draw(bulletCnt);
        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i].shape);
        }
        //------------- finish drawing--------------------------
		window.display();
	}
    return 0;
}
