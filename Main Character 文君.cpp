#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<sstream>
#include<cstdlib>
#include<math.h>
#include<cmath>
#include<vector>


using namespace std;
using namespace sf;

void Update(int &keyTime, Sprite &player, RenderWindow &window, RectangleShape &hpBar);
void Draw(RenderWindow &window, Sprite &player, RectangleShape &hpBar);



int main()
{
    srand(time(NULL));

    int keyTime = 8;
    RenderWindow window(VideoMode(1500, 900), "My Game");
    window.setFramerateLimit(200);


    //----------Player----------//
   
    Texture playerTex;
    Sprite player;
    int hp = 10;

    if (!playerTex.loadFromFile("Texture/8702.png_300 .png"))
        throw "Couldn't load";

    //將圖片放進去
    player.setTexture(playerTex); 
    //設Player大小
    player.setScale(Vector2f(0.15f,0.15f));
    //設Player起始位置
    player.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    
    RectangleShape hpBar;
    hpBar.setSize(Vector2f(hp * 20.f, 20.f));
    hpBar.setFillColor(Color::Red);
    hpBar.setPosition(Vector2f(player.getPosition().x, player.getPosition().y - 50));

    //----------Main While Loop----------//
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
                window.close();
        }
     
        Update(keyTime, player , window, hpBar);
        Draw(window,player, hpBar);
    }

    return 0;
}

void Update(int &keyTime, Sprite &player, RenderWindow &window, RectangleShape &hpBar)
{
    if(keyTime<5)
       keyTime++;


    if (Keyboard::isKeyPressed(Keyboard::A) && keyTime >= 5 && player.getPosition().x> 0)
    {
        keyTime = 0;
        player.move(-15.f, 0.f);
        
    }  
    if (Keyboard::isKeyPressed(Keyboard::W) && keyTime >= 5 && player.getPosition().y >0)
    {
        keyTime = 0;
        player.move(0.f, -15.f);
    } 
    if (Keyboard::isKeyPressed(Keyboard::S) && keyTime >= 5 && player.getPosition().y + player.getGlobalBounds().height < window.getSize().y)
    {
        keyTime = 0;
        player.move(0.f, 15.f);
    }  
    if (Keyboard::isKeyPressed(Keyboard::D) && keyTime >= 5 && player.getPosition().x+player.getGlobalBounds().width < window.getSize().x)
    {
        keyTime = 0;
        player.move(15.f, 0.f);
    }

    hpBar.setPosition(Vector2f(player.getPosition().x, player.getPosition().y - 50));

}


void Draw(RenderWindow& window, Sprite &player, RectangleShape &hpBar)
{
    //Clear
    window.clear(Color::White);
    //Draw
    window.draw(player);
    window.draw(hpBar);

    //Display
    window.display();
}