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
    clock_t start, stop;
    start = time(NULL);

    RenderWindow window(VideoMode(1680, 840), "The Final Game!");
    window.setFramerateLimit(100);

    /*===========================================================//
        Init Text
    //===========================================================*/
    Font font;
    font.loadFromFile("font/Arial.ttf");

    /*===========================================================//
        Init Textures
    //===========================================================*/
    Texture playerTex;
    playerTex.loadFromFile("textures/FinnAdventureTime.png");

    Texture humanBossTex;
    humanBossTex.loadFromFile("textures/JAKE_THE_DOG.png"); // my add

    Texture monster2Tex;
    monster2Tex.loadFromFile("textures/Original_Ice_King.png"); // my add

    Texture longLineEneTex;
    longLineEneTex.loadFromFile("textures/longLineEne.png"); // my add

    Texture bumbPrincessTex;
    bumbPrincessTex.loadFromFile("textures/bumbPrincess.png");

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
    

    // for hp ???
    RectangleShape hpBar;
    hpBar.setFillColor(Color::Red);

    // for mp ???
    RectangleShape mpBar;
    mpBar.setFillColor(Color::Blue);


    /*===========================================================//
         Boss init
    //===========================================================*/

    Boss enemy1(&monster2Tex);
    enemy1.shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    Boss enemy2(&humanBossTex);
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
  
    //--------- weapon----------//
     // player's bullet
    vector<Weapon> guns;
    vector<bool> havegun;
    vector<int> gunbulletcnt;
    bool haveGun = false;
    int weapontype = 0;
    int index = -1;
    // gun
    Texture normalgunTex;
    normalgunTex.loadFromFile("textures/gun.png");
    Weapon normalgun(normalgunTex, 200.0, 1);
    guns.push_back(normalgun);
    havegun.push_back(false);
    gunbulletcnt.push_back(100);
    // machine gun
    Texture machinegunTex;
    machinegunTex.loadFromFile("textures/machinegun.png");
    Weapon machinegun(machinegunTex, 400.0, 2);
    guns.push_back(machinegun);
    havegun.push_back(false);
    gunbulletcnt.push_back(100);
    // shotgun
    Texture shotgunTex;
    shotgunTex.loadFromFile("textures/shotgun.png");
    Weapon shotgun(shotgunTex, 800.0, 3);
    guns.push_back(shotgun);
    havegun.push_back(false);
    gunbulletcnt.push_back(100);

    int shootTimer = 0;
    
    Bullet b4(bossBulletTex);
    // enemies' bullet
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].bullets.push_back(b4);
    }
    //-------------- medicalKit----------//
    Sprite medicalKit;
    Texture medicalKitTex;
    medicalKitTex.loadFromFile("textures/medicalKit.png");
    medicalKit.setTexture(medicalKitTex);
    medicalKit.setScale(Vector2f(0.1f, 0.1f));
    vector<Sprite> medicalKits;
    int medicalKitNum = 3;
    int medicalKitRest = 0;

    //----------- youbike----------------//
    Sprite bike;
    Texture bikeTex;
    bikeTex.loadFromFile("textures/youbike.png");
    bike.setTexture(bikeTex);
    bike.setScale(Vector2f(0.2f, 0.2f));
    bike.setPosition(rolldice());


    //-------- vector-------------//
    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDir;
    Vector2f aimDirNorm;
    Vector2f aimDirNormArray[20];
    Vector2f rotateOrigin = Vector2f(1.f, 1.f);

    Vector2f bossCenter;
    Vector2f bAimDir;
    Vector2f bAimDirNorm;

    //cout << aimDirNorm.x << " " << aimDirNorm.y << endl;

    //---------- bullet texture------------------//
    Texture gunBulletTex;
    gunBulletTex.loadFromFile("textures/bullet.png");
    Bullet b1(gunBulletTex);
    Texture gunBulletTex2;
    gunBulletTex2.loadFromFile("textures/bullet2.png");
    Bullet b2(gunBulletTex2);
    Texture gunBulletTex3;
    gunBulletTex3.loadFromFile("textures/fireball.png");
    Bullet b3(gunBulletTex3);

    vector<vector<Bullet>>bullets;
    vector<Bullet> temp(20);
    bullets.resize(10, temp);

    //-------- text-----------//
    Font font2;
    font.loadFromFile("font/Arial.ttf");



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
               Update player
            //===========================================================*/
            // movement

            if (Keyboard::isKeyPressed(Keyboard::W))
                player.shape.move(0.f, -player.playerSpeed);
            if (Keyboard::isKeyPressed(Keyboard::S))
                player.shape.move(0.f, player.playerSpeed);
            if (Keyboard::isKeyPressed(Keyboard::D))
                player.shape.move(player.playerSpeed, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::A))
                player.shape.move(-player.playerSpeed, 0.f);

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
                Update controls
            //===========================================================*/

            if (shootTimer < 20)
            {
                    shootTimer++;
            }

            /*===========================================================//
                Update Bullet
            //===========================================================*/
            playerCenter = Vector2f(player.shape.getPosition().x + 100.f, player.shape.getPosition().y - 15.f);
            mousePosWindow = Vector2f(Mouse::getPosition(window));
            aimDir = mousePosWindow - playerCenter;
            aimDirNorm = Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

            // take gun
            for (int i = 0; i < guns.size(); i++)
            {
                if (player.shape.getGlobalBounds().intersects(guns[i].shape.getGlobalBounds()) && havegun[i] == false && haveGun == false)
                {
                    weapontype = guns[i].type;
                    index = i;
                    havegun[i] = true;
                    haveGun = true;
                }
                else if (havegun[i] == true && haveGun == true)
                {
                    guns[i].shape.setPosition(player.shape.getPosition().x + 85.f, player.shape.getPosition().y - 20.f);
                }
                if (gunbulletcnt[i] <= 0)
                {
                    haveGun = false;
                    guns.erase(guns.begin() + i);
                    havegun.erase(havegun.begin() + i);
                    gunbulletcnt.erase(gunbulletcnt.begin() + i);
                    index = -1;
                }
            }
            // drop gun
            if (Keyboard::isKeyPressed(Keyboard::X))
                if (index != -1)
                {
                    haveGun = false;
                    guns.erase(guns.begin() + index);
                    havegun.erase(havegun.begin() + index);
                    gunbulletcnt.erase(gunbulletcnt.begin() + index);
                    index = -1;
                }

            //if (Keyboard::isKeyPressed(Keyboard::K) && shootTimer >= 20)
            //{
            //    b1.shape.setPosition(playerCenter);
            //    b1.currVelocity = aimDirNorm;
            //    pBullets.push_back(Bullet(b1));

            //    shootTimer = 0;
            //}

            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20 && haveGun == true)
            {
                if (weapontype == 1)
                {
                    b1.shape.setPosition(player.shape.getPosition().x + 105.f, player.shape.getPosition().y - 20.f);
                    b1.currVelocity = aimDirNorm * b1.maxSpeed;
                    bullets[0].push_back(Bullet(b1));
                }
                else if (weapontype == 2)
                {
                    b2.shape.setPosition(player.shape.getPosition().x + 175.f, player.shape.getPosition().y - 20.f);
                    b2.currVelocity = aimDirNorm * b2.maxSpeed;
                    bullets[0].push_back(Bullet(b2));
                }
                else if (weapontype == 3)
                {
                    b3.shape.setPosition(player.shape.getPosition().x + 175.f, player.shape.getPosition().y + 5.f);
                    b3.currVelocity = aimDirNorm * b3.maxSpeed;
                    bullets[0].push_back(Bullet(b3));
                }
                
                if (weapontype == 2)
                {
                    // rotation martix
                   
                        aimDirNormArray[1] = rotaionMatrix(aimDirNorm, -10);
                        aimDirNormArray[2] = rotaionMatrix(aimDirNorm, -5);
                        aimDirNormArray[3] = rotaionMatrix(aimDirNorm, 5);
                        aimDirNormArray[4] = rotaionMatrix(aimDirNorm, 10);
                       
                    
                    // pushback bullet
                    for (int i = 1; i <= 4; i++)
                    {
                        b2.currVelocity = aimDirNormArray[i] * b2.maxSpeed;
                        bullets[i].push_back(Bullet(b2));
                    }
                }
                gunbulletcnt[index]--;
                shootTimer = 0;
            }

            //========== bullet movement=========//
            if (weapontype == 1 || weapontype == 2)
            {
                for (size_t i = 0; i < bullets[0].size(); i++)
                {
                    bullets[0][i].shape.move(bullets[0][i].currVelocity);
                    //Out of bounds
                    if (bullets[0][i].shape.getPosition().x < 0 || bullets[0][i].shape.getPosition().x > window.getSize().x
                        || bullets[0][i].shape.getPosition().y < 0 || bullets[0][i].shape.getPosition().y > window.getSize().y)
                    {
                        bullets[0].erase(bullets[0].begin() + i);
                    }
                    else
                    {
                        //Enemy and bullet collision
                        if (!enemies.empty() and !bullets[0].empty())
                        {
                            for (int i = 0; i < bullets[0].size(); i++)
                            {
                                for (int j = 0; j < enemies.size(); j++)
                                {
                                    if (bullets[0][i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                                    {
                                        if (enemies[j].HP < 1)
                                        {
                                            enemies[j].shape.setTexture(deadHumanBossTex);
                                            enemies.erase(enemies.begin() + j);
                                        }

                                        else
                                            enemies[j].HP -= 5.3;

                                        bullets[0].erase(bullets[0].begin() + i);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            if (weapontype == 2)
            {
                for (int k = 1; k <= 4; k++)
                    for (size_t i = 0; i < bullets[k].size(); i++)
                    {
                        bullets[k][i].shape.move(bullets[k][i].currVelocity);
                        //Out of bounds
                        if (bullets[k][i].shape.getPosition().x < 0 || bullets[k][i].shape.getPosition().x > window.getSize().x
                            || bullets[k][i].shape.getPosition().y < 0 || bullets[k][i].shape.getPosition().y > window.getSize().y)
                        {
                            bullets[k].erase(bullets[k].begin() + i);
                        }
                        else
                        {
                            //Enemy and bullet collision
                            if (!enemies.empty() and !bullets[k].empty())
                            {
                                for (int i = 0; i < bullets[k].size(); i++)
                                {
                                    for (int j = 0; j < enemies.size(); j++)
                                    {
                                        if (bullets[k][i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                                        {
                                            if (enemies[j].HP < 1)
                                            {
                                                enemies[j].shape.setTexture(deadHumanBossTex);
                                                enemies.erase(enemies.begin() + j);
                                            }

                                            else
                                                enemies[j].HP -= 5.3;

                                            bullets[k].erase(bullets[k].begin() + i);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
            }
            
            if (weapontype == 3)
            {
                for (size_t i = 0; i < bullets[0].size(); i++)
                {
                    FloatRect bounds = bullets[0][i].shape.getLocalBounds();
                    bullets[0][i].shape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                    bullets[0][i].shape.setScale(Vector2f(bullets[0][i].size, bullets[0][i].size));
                    bullets[0][i].shape.move(bullets[0][i].currVelocity);
                    bullets[0][i].size += 0.005;
                    //Out of bounds
                    if (bullets[0][i].shape.getPosition().x < 0 || bullets[0][i].shape.getPosition().x > window.getSize().x
                        || bullets[0][i].shape.getPosition().y < 0 || bullets[0][i].shape.getPosition().y > window.getSize().y)
                    {
                        bullets[0].erase(bullets[0].begin() + i);
                    }
                    else
                    {
                        //Enemy and bullet collision
                        if (!enemies.empty() and !bullets[0].empty())
                        {
                            for (int i = 0; i < bullets[0].size(); i++)
                            {
                                for (int j = 0; j < enemies.size(); j++)
                                {
                                    if (bullets[0][i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
                                    {
                                        if (enemies[j].HP < 1)
                                        {
                                            enemies[j].shape.setTexture(deadHumanBossTex);
                                            enemies.erase(enemies.begin() + j);
                                        }

                                        else
                                            enemies[j].HP -= 5.3;

                                        bullets[0].erase(bullets[0].begin() + i);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            

            // medical kit
            stop = time(NULL);
            if (medicalKitRest < medicalKitNum && (start - stop) % 20 == 0)
            {
                for (int i = medicalKitRest; i < medicalKitNum; i++)
                {
                    medicalKits.push_back(medicalKit);
                    medicalKits[i].setPosition(rolldice());
                    medicalKitRest++;
                }
            }
            for (int i = 0; i < medicalKitRest; i++)
            {
                if (player.shape.getGlobalBounds().intersects(medicalKits[i].getGlobalBounds()))
                {   
                    if(player.HPMax - player.HP < 30)
                         player.HP = player.HPMax;
                    else if (player.HP < player.HPMax)
                    {
                        player.HP += 30;
                    }
                    medicalKits.erase(medicalKits.begin() + i);
                    medicalKitRest--;
                }
            }
            // get bike
            if (player.shape.getGlobalBounds().intersects(bike.getGlobalBounds()))
            {
                bike.setPosition(player.shape.getPosition().x, player.shape.getPosition().y + 70.f);
                player.playerSpeed = 6.f;
            }



            /*===========================================================//
                 Update Enemy
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
                    b4.shape.setPosition(enemies[i].bossCenter);
                    b4.currVelocity = enemies[i].bAimDirNorm;
                    enemies[i].bullets.push_back(Bullet(b4));

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


            //

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

        // bullet count
        Text bulletCnt;
        if (haveGun == true)
        {
            bulletCnt.setString(to_string(gunbulletcnt[index]));
            bulletCnt.setFont(font);
            bulletCnt.setPosition(Vector2f(1600.f, 800.f));
            bulletCnt.setCharacterSize(30);
            bulletCnt.setStyle(Text::Bold);
            bulletCnt.setFillColor(Color::Red);
        }
        /*===========================================================//
           Update UI
        //===========================================================*/
        hpBar.setSize(Vector2f((float)player.HP * 0.45f, 10.f));
        mpBar.setSize(Vector2f((float)player.MP * 0.45f, 10.f));

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].bHpBar.setSize(Vector2f((float)enemies[i].HP * 0.45f, 10.f));
        }




        /*===========================================================//
            Draw
        //===========================================================*/
        window.clear();
        /*===========================================================//
            Draw  player
        //===========================================================*/
        window.draw(player.shape);
        window.draw(hpBar);
        window.draw(mpBar);


        /*===========================================================//
           Draw bullets
        //===========================================================*/
        for (int i = 0; i < guns.size(); i++)
        {
            window.draw(guns[i].shape);
        }

        if (haveGun == true)
           window.draw(bulletCnt);

        for (int i = 0; i < bullets[0].size(); i++)
        {
            window.draw(bullets[0][i].shape);
        }
        for (int j = 1; j <= 4; j++)
            for (int i = 0; i < bullets[j].size(); i++)
            {
                window.draw(bullets[j][i].shape);
            }
        for (int i = 0; i < medicalKitRest; i++)
        {
            window.draw(medicalKits[i]);
        }
        window.draw(bike);

        for (int i = 0; i < enemies.size(); i++)
        {
            for (int j = 0; j < enemies[i].bullets.size(); j++)
            {
                window.draw(enemies[i].bullets[j].shape);
            }
        }



        /*===========================================================//
            Draw Boss
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
           Draw UI
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