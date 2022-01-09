#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<sstream>
#include<cstdlib>
#include<math.h>
#include<cmath>
#include<vector>
#include"MyGame.h"
using namespace std;
using namespace sf;


int main()

{
    srand(time(NULL));

    RenderWindow window(VideoMode(1680, 840), "The Final Game!");
    window.setFramerateLimit(200);

    /*===========================================================//
        Init Text
    //===========================================================*/
    Font font;
    font.loadFromFile("font/Arial.ttf");

    /*===========================================================//
        Init Textures
    //===========================================================*/
    Texture playerTex;
    playerTex.loadFromFile("textures/player.png");

    Texture humanBossTex;
    humanBossTex.loadFromFile("textures/big_bird.png"); // my add

    Texture monster2Tex;
    monster2Tex.loadFromFile("textures/principal.png"); // my add

    Texture longLineEneTex;
    longLineEneTex.loadFromFile("textures/cow.png"); // my add

    Texture bumbPrincessTex;
    bumbPrincessTex.loadFromFile("textures/duck.png");

    Texture earthBossTex;
    earthBossTex.loadFromFile("textures/Boss2.png");

    Texture deadHumanBossTex;
    deadHumanBossTex.loadFromFile("textures/Boss1-2.png");

    Texture deadEarthBossTex;
    deadEarthBossTex.loadFromFile("textures/Boss2-3.png");

    Texture bulletTex;
    bulletTex.loadFromFile("textures/normalshoot.png");

    Texture bossBulletTex;
    bossBulletTex.loadFromFile("textures/enemyShoot.png");

    /*===========================================================//
        UI init
    //===========================================================*/

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(120);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(100.f, window.getSize().y / 2);
    gameOverText.setString("Game Over!!!!");

    Text youWin;
    youWin.setFont(font);
    youWin.setCharacterSize(120);
    youWin.setFillColor(Color::Red);
    youWin.setPosition(100.f, window.getSize().y / 2);
    youWin.setString("You Win!!!!");


    /*===========================================================//
        Player init
    //===========================================================*/

    int score = 0;

    Player player(&playerTex);
    int shootTimer = 20;

    // for hp ???
    RectangleShape hpBar;
    hpBar.setFillColor(Color::Red);

    // for mp ???
    RectangleShape mpBar;
    mpBar.setFillColor(Color::Blue);


    /*===========================================================//
         Boss init
    //===========================================================*/

    Boss enemy1(& monster2Tex);
    enemy1.shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    Boss enemy2(& humanBossTex);
    enemy2.shape.setPosition(window.getSize().x / 3, window.getSize().y / 3);
    Boss enemy3(&bumbPrincessTex);
    enemy3.shape.setPosition(window.getSize().x / 4, window.getSize().y / 4);

    vector<Boss> enemies;
    enemies.push_back(Boss(enemy1));
    enemies.push_back(Boss(enemy2));
    enemies.push_back(Boss(enemy3));

    int bShootTimer = 15;

    Text wHpText;
    wHpText.setFont(font);
    wHpText.setCharacterSize(12);
    wHpText.setFillColor(Color::White);

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].bHpBar.setFillColor(Color::Red);
    }

    /*===========================================================//
         Bullet init
    //===========================================================*/
    
    Bullet b1(& bulletTex);
    Bullet b2(& bossBulletTex);
    
    vector<Bullet> pBullets; // player's bullet
    // enemies' bullet
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].bullets.push_back(b2);
    }
    

    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;
    Vector2f rotateOrigin = Vector2f(1.f, 1.f);

    Vector2f bossCenter;
    Vector2f bAimDir;
    Vector2f bAimDirNorm;

    //cout << aimDirNorm.x << " " << aimDirNorm.y << endl;




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


        // check if all enemies are dead
        bool notAllEnemiesDie = 0;
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].HP >= 0)
                notAllEnemiesDie = 1;    
        }

        if (player.HP >= 0 && notAllEnemiesDie)
        {
            /*===========================================================//
               ?iUpdate?j player
            //===========================================================*/
            // movement

            if (Keyboard::isKeyPressed(Keyboard::W))
                player.shape.move(0.f, -3.f);
            if (Keyboard::isKeyPressed(Keyboard::S))
                player.shape.move(0.f, 3.f);
            if (Keyboard::isKeyPressed(Keyboard::D))
                player.shape.move(3.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::A))
                player.shape.move(-3.f, 0.f);

            // collision with window

            if (player.shape.getPosition().x <= 0) // left
                player.shape.setPosition(0.f, player.shape.getPosition().y);
            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) // right
                player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
            if (player.shape.getPosition().y <= 0) // Top
                player.shape.setPosition(player.shape.getPosition().x, 0.f);
            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) // bottom
                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

            // hp & mp Bars and Text set
            hpBar.setPosition(player.shape.getPosition().x + 10, player.shape.getPosition().y - 25.f);
            mpBar.setPosition(player.shape.getPosition().x + 9, player.shape.getPosition().y - 15.f);


            // HP & MP set

            /*===========================================================//
                Update?j controls
            //===========================================================*/

            if (shootTimer < 20)
                shootTimer++;


            /*===========================================================//
                ?iUpdate?j Bullet
            //===========================================================*/
            playerCenter = Vector2f(player.shape.getPosition().x + 100.f, player.shape.getPosition().y - 15.f);
            mousePosWindow = Vector2f(Mouse::getPosition(window));
            aimDir = mousePosWindow - playerCenter;
            aimDirNorm = Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

            //if (Keyboard::isKeyPressed(Keyboard::K) && shootTimer >= 20)
            //{
            //    b1.shape.setPosition(playerCenter);
            //    b1.currVelocity = aimDirNorm;
            //    pBullets.push_back(Bullet(b1));

            //    shootTimer = 0;
            //}

            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20)
            {
                b1.shape.setPosition(playerCenter);
                b1.currVelocity = aimDirNorm;
                pBullets.push_back(Bullet(b1));

                shootTimer = 0; // reset timer
            }


            for (size_t i = 0; i < pBullets.size(); i++)
            {

                pBullets[i].shape.move(pBullets[i].currVelocity);

                //Out of bounds
                if (pBullets[i].shape.getPosition().x < 0 || pBullets[i].shape.getPosition().x > window.getSize().x
                    || pBullets[i].shape.getPosition().y < 0 || pBullets[i].shape.getPosition().y > window.getSize().y)
                {
                    pBullets.erase(pBullets.begin() + i);

                }

                else
                {
                    //Enemy and bullet collision
                    if (!enemies.empty() and !pBullets.empty())
                    {
                        for (int i = 0; i < pBullets.size(); i++)
                        {
                            for (int j = 0; j < enemies.size(); j++)
                            {
                                if (pBullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                                {
                                    if (enemies[j].HP < 1)
                                    {
                                        enemies[j].shape.setTexture(deadHumanBossTex);
                                        enemies.erase(enemies.begin() + j);
                                    }

                                    else
                                        enemies[j].HP -= 5.3;

                                    pBullets.erase(pBullets.begin() + i);
                                    break;
                                }
                            }
                        }
                    }


                    //if (pBullets[i].shape.getGlobalBounds().intersects(weirdFace.shape.getGlobalBounds()))
                    //{
                    //    if (weirdFace.HP < 1)
                    //    {
                    //        weirdFace.shape.setTexture(deadHumanBossTex);

                    //    }

                    //    else
                    //        weirdFace.HP -= 5.3;


                    //    pBullets.erase(pBullets.begin() + i);

                    //}

                }
            }





            /*===========================================================//
                 ?iUpdate?j Enemy
            //===========================================================*/
            
            // Enemy bullets
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].bossCenter = Vector2f(enemies[i].shape.getPosition().x + 100.f, enemies[i].shape.getPosition().y + 100.f);
                enemies[i].bAimDir = playerCenter - enemies[i].bossCenter;
                enemies[i].bAimDirNorm = Vector2f(enemies[i].bAimDir.x / sqrt(pow(enemies[i].bAimDir.x, 2) + pow(enemies[i].bAimDir.y, 2)), enemies[i].bAimDir.y / sqrt(pow(enemies[i].bAimDir.x, 2) + pow(enemies[i].bAimDir.y, 2)));
            }

           if (bShootTimer >= 15)
           {
               for (int i = 0; i < enemies.size(); i++)
               {
                   b2.shape.setPosition(enemies[i].bossCenter);
                   b2.currVelocity = enemies[i].bAimDirNorm;
                   enemies[i].bullets.push_back(Bullet(b2));

                   bShootTimer = 0; // reset timer
                   enemies[i].shape.move(enemies[i].bAimDirNorm * 10.f);
               }
 
           }

            else
              bShootTimer++;

           for (int i = 0; i < enemies.size(); i++) 
           {
               for (size_t j = 0; j < enemies[i].bullets.size(); j++)
               {

                   enemies[i].bullets[j].shape.move(enemies[i].bullets[j].currVelocity);

                   //Out of bounds
                   if (enemies[i].bullets[j].shape.getPosition().x < 0 || enemies[i].bullets[j].shape.getPosition().x > window.getSize().x
                       || enemies[i].bullets[j].shape.getPosition().y < 0 || enemies[i].bullets[j].shape.getPosition().y > window.getSize().y)
                   {
                       enemies[i].bullets.erase(enemies[i].bullets.begin() + j);

                   }

                   else
                   {
                       //Enemy collision

                       if (enemies[i].bullets[j].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                       {
                           player.HP -= 0.7;
                           enemies[i].bullets.erase(enemies[i].bullets.begin() + j);

                       }
                   }
               }

               for (size_t j = 0; j < enemies[i].bullets.size(); j++)
               {

                   enemies[i].bullets[j].shape.move(enemies[i].bullets[j].currVelocity);

                   //Out of bounds
                   if (enemies[i].bullets[j].shape.getPosition().x < 0 || enemies[i].bullets[j].shape.getPosition().x > window.getSize().x
                       || enemies[i].bullets[j].shape.getPosition().y < 0 || enemies[i].bullets[j].shape.getPosition().y > window.getSize().y)
                   {
                       enemies[i].bullets.erase(enemies[i].bullets.begin() + j);

                   }

                   else
                   {
                       //Enemy collision

                       if (enemies[i].bullets[j].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                       {
                           player.HP -= 0.7;
                           enemies[i].bullets.erase(enemies[i].bullets.begin() + j);

                       }
                   }
               }
           }


           //ÃL·ì
       
           for (int i = 0; i < enemies.size(); i++)
           {
                   for (int j = 0; j < enemies.size(); j++)
                   {
                       if (enemies[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()) && i != j)
                       {
                           Vector2f vec = enemies[i].shape.getPosition() - enemies[j].shape.getPosition();
                           enemies[i].shape.move(vec * 0.3f);
                           enemies[j].shape.move(vec * -0.3f);
                       }
                   }
           }
            //for (size_t j = 0; j < enemies[i].bullets.size(); j++)
            //{

            //        enemies[i].bullets[j].shape.move(enemies[i].bullets[i].currVelocity);

            //        //Out of bounds
            //        if (bBullets[i].shape.getPosition().x < 0 || bBullets[i].shape.getPosition().x > window.getSize().x
            //        || bBullets[i].shape.getPosition().y < 0 || bBullets[i].shape.getPosition().y > window.getSize().y)
            //        {
            //            bBullets.erase(bBullets.begin() + i);

            //        }

            //        else
            //        {
            //            //Enemy collision

            //            if (bBullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            //            {
            //                player.HP -= 0.7;
            //                bBullets.erase(bBullets.begin() + i);

            //            }
            //        }
            //    }

                // for enemy collision with player

            for (int i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                {
                    player.HP -= 1.5;
                    player.shape.move(bAimDirNorm * 150.f);
                }
            }

                for (int i = 0; i < enemies.size(); i++)
                {
                    enemies[i].bHpBar.setPosition(enemies[i].shape.getPosition().x + 5.f, enemies[i].shape.getPosition().y - 25.f);
                }

                //bHpBar.setPosition(enemies[i].shape.getPosition().x + 5.f, enemies[i].shape.getPosition().y - 25.f);

            }



            //// Enemy bullets
            //Vector2f bossCenter = Vector2f(weirdFace.shape.getPosition().x + 100.f, weirdFace.shape.getPosition().y + 100.f);
            //bAimDir = playerCenter - bossCenter;
            //Vector2f bAimDirNorm = Vector2f(bAimDir.x / sqrt(pow(bAimDir.x, 2) + pow(bAimDir.y, 2)), bAimDir.y / sqrt(pow(bAimDir.x, 2) + pow(bAimDir.y, 2)));

            //if (bShootTimer >= 15)
            //{
            //    b2.shape.setPosition(bossCenter);
            //    b2.currVelocity = bAimDirNorm;
            //    bBullets.push_back(Bullet(b2));

            //    bShootTimer = 0; // reset timer
            //    weirdFace.shape.move(bAimDirNorm * 10.f);
            //}

            //else
            //    bShootTimer++;

            //for (size_t i = 0; i < bBullets.size(); i++)
            //{

            //    bBullets[i].shape.move(bBullets[i].currVelocity);

            //    //Out of bounds
            //    if (bBullets[i].shape.getPosition().x < 0 || bBullets[i].shape.getPosition().x > window.getSize().x
            //        || bBullets[i].shape.getPosition().y < 0 || bBullets[i].shape.getPosition().y > window.getSize().y)
            //    {
            //        bBullets.erase(bBullets.begin() + i);

            //    }

            //    else
            //    {
            //        //Enemy collision

            //        if (bBullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            //        {
            //            player.HP -= 0.7;
            //            bBullets.erase(bBullets.begin() + i);

            //        }
            //    }
            //}

            //// for enemy collision with player
            //if (weirdFace.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            //{
            //    player.HP -= 1.5;
            //    player.shape.move(bAimDirNorm * 150.f);
            //}


            //bHpBar.setPosition(weirdFace.shape.getPosition().x + 5.f, weirdFace.shape.getPosition().y - 25.f);

            /*===========================================================//
               ?iUpdate?j UI
            //===========================================================*/
            hpBar.setSize(Vector2f((float)player.HP * 0.45f, 10.f));
            mpBar.setSize(Vector2f((float)player.MP * 0.45f, 10.f));

            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].bHpBar.setSize(Vector2f((float)enemies[i].HP * 0.45f, 10.f));
            }

        


        /*===========================================================//
            ?iDraw?j
        //===========================================================*/
        window.clear();
        /*===========================================================//
            ?iDraw?j  player
        //===========================================================*/
        window.draw(player.shape);
        window.draw(hpBar);
        window.draw(mpBar);


        /*===========================================================//
            ?iDraw?j bullets
        //===========================================================*/
        for (size_t i = 0; i < pBullets.size(); i++)
        {
            window.draw(pBullets[i].shape);
        }

        for (int i = 0; i < enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].bullets.size(); j++)
            {
                window.draw(enemies[i].bullets[j].shape);
            }
        }



        /*===========================================================//
            ?iDraw?j Boss
        //===========================================================*/
        for (int i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i].bHpBar);
        }

        //window.draw(bHpBar);

        for (int i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i].shape);
        }

        //for (int i = 0; i < bBullets.size(); i++)
        //{
        //    window.draw(bBullets[i].shape);
        //}

        /*===========================================================//
             ?iDraw?j UI
        //===========================================================*/
        if (player.HP <= 0)
        {
            window.draw(gameOverText);
        }
        

        if (!notAllEnemiesDie)
        {
            window.draw(youWin);
        }


        window.draw(player.shape);
        window.display();

    }
}
