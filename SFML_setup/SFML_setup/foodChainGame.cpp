//
//#include<iostream>
//#include<SFML\Graphics.hpp>
//#include<SFML\Window.hpp>
//#include<SFML\System.hpp>
//#include<sstream>
//#include<cstdlib>
//#include<math.h>
//#include<cmath>
//#include<vector>
//#include"MyGame.h"
//using namespace std;
//using namespace sf;
//
//
//int main()
//
//{
//    srand(time(NULL));
//
//    RenderWindow window(VideoMode(1680, 840), "The Final Game!");
//    window.setFramerateLimit(200);
//
//    /*===========================================================//
//        Init Text
//    //===========================================================*/
//    Font font;
//    font.loadFromFile("font/Arial.ttf");
//
//    /*===========================================================//
//        Init Textures
//    //===========================================================*/
//    Texture playerTex;
//    playerTex.loadFromFile("textures/FinnAdventureTime.png");
//
//    Texture humanBossTex;
//    humanBossTex.loadFromFile("textures/JAKE_THE_DOG.png"); // my add
//
//    Texture monster2Tex;
//    monster2Tex.loadFromFile("textures/Original_Ice_King.png"); // my add
//
//    Texture longLineEneTex;
//    longLineEneTex.loadFromFile("textures/longLineEne.png"); // my add
//
//    Texture earthBossTex;
//    earthBossTex.loadFromFile("textures/Boss2.png");
//
//    Texture deadHumanBossTex;
//    deadHumanBossTex.loadFromFile("textures/Boss1-2.png");
//
//    Texture deadEarthBossTex;
//    deadEarthBossTex.loadFromFile("textures/Boss2-3.png");
//
//    Texture bulletTex;
//    bulletTex.loadFromFile("textures/normalshoot.png");
//
//    Texture bossBulletTex;
//    bossBulletTex.loadFromFile("textures/enemyShoot.png");
//
//    /*===========================================================//
//        UI init
//    //===========================================================*/
//
//    Text gameOverText;
//    gameOverText.setFont(font);
//    gameOverText.setCharacterSize(120);
//    gameOverText.setFillColor(Color::Red);
//    gameOverText.setPosition(100.f, window.getSize().y / 2);
//    gameOverText.setString("Game Over!!!!");
//
//    Text youWin;
//    youWin.setFont(font);
//    youWin.setCharacterSize(120);
//    youWin.setFillColor(Color::Red);
//    youWin.setPosition(100.f, window.getSize().y / 2);
//    youWin.setString("You Win!!!!");
//
//
//    /*===========================================================//
//        Player init
//    //===========================================================*/
//
//    int score = 0;
//
//    Player player(&playerTex);
//    int shootTimer = 20;
//
//    // for hp ???
//    RectangleShape hpBar;
//    hpBar.setFillColor(Color::Red);
//
//    // for mp ???
//    RectangleShape mpBar;
//    mpBar.setFillColor(Color::Blue);
//
//
//    /*===========================================================//
//         Boss init
//    //===========================================================*/
//    Boss weirdFace(&humanBossTex);
//    weirdFace.shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
//
//    Boss monster2(&monster2Tex);
//    monster2.shape.setPosition(window.getSize().x / 3, window.getSize().y / 3); // my add
//
//    Boss longLineEne(&longLineEneTex);
//    longLineEne.shape.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2)); // my add
//
//    vector<Boss> enemies;
//
//    int bShootTimer = 15;
//
//    Text wHpText;
//    wHpText.setFont(font);
//    wHpText.setCharacterSize(12);
//    wHpText.setFillColor(Color::White);
//
//    RectangleShape bHpBar;
//    bHpBar.setFillColor(Color::Red);
//
//    /*===========================================================//
//         Bullet init
//    //===========================================================*/
//    Bullet b1(&bulletTex);
//    Bullet b2(&bossBulletTex);
//    vector<Bullet> pBullets;
//    vector<Bullet> bBullets;
//
//    Vector2f playerCenter;
//    Vector2f mousePosWindow;
//    Vector2f aimDir;
//    Vector2f aimDirNorm;
//    Vector2f rotateOrigin = Vector2f(1.f, 1.f);
//
//    Vector2f bossCenter;
//    Vector2f bAimDir;
//    Vector2f bAimDirNorm;
//
//    Vector2f boss2Center;
//    Vector2f bAimDir2;
//    Vector2f bAimDirNorm2;
//
//    //cout << aimDirNorm.x << " " << aimDirNorm.y << endl;
//
//
//
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//
//            if (event.type == Event::Closed)
//                window.close();
//
//            if (Keyboard::isKeyPressed(Keyboard::Escape))
//                window.close();
//        }
//
//        if (player.HP >= 0 && weirdFace.HP >= 0)
//        {
//            /*===========================================================//
//               ?iUpdate?j player
//            //===========================================================*/
//            // movement
//
//            if (Keyboard::isKeyPressed(Keyboard::W))
//                player.shape.move(0.f, -3.f);
//            if (Keyboard::isKeyPressed(Keyboard::S))
//                player.shape.move(0.f, 3.f);
//            if (Keyboard::isKeyPressed(Keyboard::D))
//                player.shape.move(3.f, 0.f);
//            if (Keyboard::isKeyPressed(Keyboard::A))
//                player.shape.move(-3.f, 0.f);
//
//            // collision with window
//
//            if (player.shape.getPosition().x <= 0) // left
//                player.shape.setPosition(0.f, player.shape.getPosition().y);
//            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) // right
//                player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
//            if (player.shape.getPosition().y <= 0) // Top
//                player.shape.setPosition(player.shape.getPosition().x, 0.f);
//            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) // bottom
//                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
//
//            // hp & mp Bars and Text set
//
//
//            hpBar.setPosition(player.shape.getPosition().x + 10, player.shape.getPosition().y - 25.f);
//            mpBar.setPosition(player.shape.getPosition().x + 9, player.shape.getPosition().y - 15.f);
//
//
//            // HP & MP set
//
//            /*===========================================================//
//                Update?j controls
//            //===========================================================*/
//
//            if (shootTimer < 20)
//                shootTimer++;
//
//
//            /*===========================================================//
//                ?iUpdate?j Bullet
//            //===========================================================*/
//            playerCenter = Vector2f(player.shape.getPosition().x + 100.f, player.shape.getPosition().y - 15.f);
//            mousePosWindow = Vector2f(Mouse::getPosition(window));
//            aimDir = mousePosWindow - playerCenter;
//            aimDirNorm = Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
//
//            if (Keyboard::isKeyPressed(Keyboard::K) && shootTimer >= 20) 
//            {
//                b1.shape.setPosition(playerCenter);
//                b1.currVelocity = aimDirNorm;
//                pBullets.push_back(Bullet(b1));
//
//                shootTimer = 0;
//            }
//
//
//            
//            //if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20)
//            //{
//            //    b1.shape.setPosition(playerCenter);
//            //    b1.currVelocity = aimDirNorm;
//            //    pBullets.push_back(Bullet(b1));
//
//            //    shootTimer = 0; // reset timer
//            //}
//
//            
//            for (size_t i = 0; i < pBullets.size(); i++)
//            {
//
//                pBullets[i].shape.move(pBullets[i].currVelocity);
//
//                //Out of bounds
//                if (pBullets[i].shape.getPosition().x < 0 || pBullets[i].shape.getPosition().x > window.getSize().x
//                    || pBullets[i].shape.getPosition().y < 0 || pBullets[i].shape.getPosition().y > window.getSize().y)
//                {
//                    pBullets.erase(pBullets.begin() + i);
//
//                }
//
//                else
//                {
//                    //Enemy collision 1
//
//                    if (pBullets[i].shape.getGlobalBounds().intersects(weirdFace.shape.getGlobalBounds()))
//                    {
//                        if (weirdFace.HP < 1)
//                        {
//                            weirdFace.shape.setTexture(deadHumanBossTex);
//
//                        }
//
//                        else
//                            weirdFace.HP -= 5.3;
//
//
//                        pBullets.erase(pBullets.begin() + i);
//
//                    }
//
//                    // Enemy collision 2
//
//                    if (pBullets[i].shape.getGlobalBounds().intersects(monster2.shape.getGlobalBounds()))
//                    {
//                        if (monster2.HP < 1)
//                        {
//                            monster2.shape.setTexture(deadHumanBossTex); // need change
//
//                        }
//
//                        else
//                            monster2.HP -= 5.3;
//
//
//                        pBullets.erase(pBullets.begin() + i);
//
//                    }
//                }
//            }
//
//
//
//
//
//            /*===========================================================//
//                 ?iUpdate?j Enemy
//            //===========================================================*/
//
//            // Enemy bullets 1
//            Vector2f bossCenter = Vector2f(weirdFace.shape.getPosition().x + 100.f, weirdFace.shape.getPosition().y + 100.f);
//            bAimDir = playerCenter - bossCenter;
//            Vector2f bAimDirNorm = Vector2f(bAimDir.x / sqrt(pow(bAimDir.x, 2) + pow(bAimDir.y, 2)), bAimDir.y / sqrt(pow(bAimDir.x, 2) + pow(bAimDir.y, 2)));
//
//            if (bShootTimer >= 15)
//            {
//                b2.shape.setPosition(bossCenter);
//                b2.currVelocity = bAimDirNorm;
//                bBullets.push_back(Bullet(b2));
//
//                bShootTimer = 0; // reset timer
//                weirdFace.shape.move(bAimDirNorm * 10.f);
//            }
//
//            else
//                bShootTimer++;
//
//            for (size_t i = 0; i < bBullets.size(); i++)
//            {
//
//                bBullets[i].shape.move(bBullets[i].currVelocity);
//
//                //Out of bounds
//                if (bBullets[i].shape.getPosition().x < 0 || bBullets[i].shape.getPosition().x > window.getSize().x
//                    || bBullets[i].shape.getPosition().y < 0 || bBullets[i].shape.getPosition().y > window.getSize().y)
//                {
//                    bBullets.erase(bBullets.begin() + i);
//
//                }
//
//                else
//                {
//                    //Enemy collision
//
//                    if (bBullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//                    {
//                        player.HP -= 0.7;
//                        bBullets.erase(bBullets.begin() + i);
//
//                    }
//                }
//            }
//
//            // for enemy collision with player
//            if (weirdFace.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//            {
//                player.HP -= 1.5;
//                player.shape.move(bAimDirNorm * 150.f);
//            }
//
//
//            bHpBar.setPosition(weirdFace.shape.getPosition().x + 5.f, weirdFace.shape.getPosition().y - 25.f);
//
//
//
//            // Enemy bullets 2
//            Vector2f boss2Center = Vector2f(monster2.shape.getPosition().x + 100.f, monster2.shape.getPosition().y + 100.f);
//            bAimDir2 = playerCenter - boss2Center;
//            Vector2f bAimDirNorm2 = Vector2f(bAimDir2.x / sqrt(pow(bAimDir2.x, 2) + pow(bAimDir2.y, 2)), bAimDir2.y / sqrt(pow(bAimDir2.x, 2) + pow(bAimDir2.y, 2)));
//
//            if (bShootTimer >= 15)
//            {
//                b2.shape.setPosition(boss2Center);
//                b2.currVelocity = bAimDirNorm2;
//                bBullets.push_back(Bullet(b2));
//
//                bShootTimer = 0; // reset timer
//                monster2.shape.move(bAimDirNorm2 * 10.f);
//            }
//
//            else
//                bShootTimer++;
//
//            for (size_t i = 0; i < bBullets.size(); i++)
//            {
//
//                bBullets[i].shape.move(bBullets[i].currVelocity);
//
//                //Out of bounds
//                if (bBullets[i].shape.getPosition().x < 0 || bBullets[i].shape.getPosition().x > window.getSize().x
//                    || bBullets[i].shape.getPosition().y < 0 || bBullets[i].shape.getPosition().y > window.getSize().y)
//                {
//                    bBullets.erase(bBullets.begin() + i);
//
//                }
//
//                else
//                {
//                    //Enemy collision
//
//                    if (bBullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//                    {
//                        player.HP -= 0.7;
//                        bBullets.erase(bBullets.begin() + i);
//
//                    }
//                }
//            }
//
//            // for enemy collision with player
//            if (monster2.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
//            {
//                player.HP -= 1.5;
//                player.shape.move(bAimDirNorm2 * 150.f);
//            }
//
//
//            bHpBar.setPosition(monster2.shape.getPosition().x + 5.f, monster2.shape.getPosition().y - 25.f);
//
//
//
//
//
//
//
//            /*===========================================================//
//               ?iUpdate?j UI
//            //===========================================================*/
//            hpBar.setSize(Vector2f((float)player.HP * 0.45f, 10.f));
//            mpBar.setSize(Vector2f((float)player.MP * 0.45f, 10.f));
//
//            bHpBar.setSize(Vector2f((float)weirdFace.HP * 0.45f, 10.f));
//
//        }
//
//
//        /*===========================================================//
//            ?iDraw?j
//        //===========================================================*/
//        window.clear();
//        /*===========================================================//
//            ?iDraw?j  player
//        //===========================================================*/
//        window.draw(player.shape);
//        window.draw(hpBar);
//        window.draw(mpBar);
//
//
//        /*===========================================================//
//            ?iDraw?j bullets
//        //===========================================================*/
//        for (size_t i = 0; i < pBullets.size(); i++)
//        {
//            window.draw(pBullets[i].shape);
//        }
//
//        for (size_t i = 0; i < bBullets.size(); i++)
//        {
//            window.draw(bBullets[i].shape);
//        }
//
//
//
//        /*===========================================================//
//            ?iDraw?j Boss
//        //===========================================================*/
//        window.draw(weirdFace.shape);
//        window.draw(bHpBar);
//        window.draw(monster2.shape);
//        //window.draw(longLineEne.shape);
//
//        /*===========================================================//
//             ?iDraw?j UI
//        //===========================================================*/
//        if (player.HP <= 0)
//        {
//            window.draw(gameOverText);
//        }
//
//        if (weirdFace.HP <= 0)
//        {
//            window.draw(youWin);
//        }
//
//
//        window.draw(player.shape);
//        window.display();
//
//    }
//}
//
//
//
