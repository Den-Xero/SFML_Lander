#include "Game.h"
#include "Physics.h"
#include "Entity.h"

void Game::Run(sf::RenderWindow& window)
{

    Physics Phy;
    //stops the game when player is dead and out of fuel.
    GameOver = false;
    
    //stops the game from reseting terrain and player pos when restarting.
    if (!NextLevel)
    {
        
        srand(time(NULL));

        //sets the players pos at start of the game.
        StartPoint = { rand() % 999 + 25.f, rand() % 10 + 5.f };
        TopPoint = { StartPoint.X, StartPoint.Y };
        BottomLeft = { TopPoint.X - 10, TopPoint.Y + 20 };
        BottomRight = { TopPoint.X + 10 , TopPoint.Y + 20 };
        BottomPoint = { StartPoint.X, StartPoint.Y + 20 };
        ThrustTopLeft = { BottomLeft.X + 5, BottomLeft.Y };
        ThrustTopRight = { BottomRight.X - 5, BottomRight.Y };
        ThrustBottom = { BottomPoint.X, BottomPoint.Y + 10 };

        //sets the terrain Y points are start of the game.
        for (size_t i = 0; i < 18; i++)
        {
            TerrainYLevel1.push_back(rand() % 300 + 780);
        }

        for (size_t i = 0; i < 18; i++)
        {
            TerrainYLevel2.push_back(rand() % 300 + 780);
        }

        for (size_t i = 0; i < 18; i++)
        {
            TerrainYLevel3.push_back(rand() % 300 + 780);
        }

        for (size_t i = 0; i < 18; i++)
        {
            TerrainYLevel4.push_back(rand() % 300 + 780);
        }
    }


    
    //init of Entities used in the game
    Entity Ship;
    Entity Thrust;
    Entity LZ1L1;
    Entity LZ2L1;
    Entity LZ3L1;
    Entity LZ1L2;
    Entity LZ2L2;
    Entity LZ3L2;
    Entity LZ1L3;
    Entity LZ2L3;
    Entity LZ3L3;
    Entity LZ1L4;
    Entity LZ2L4;
    Entity LZ3L4;
    //Attemted at partical system but couldn't get it to work in time.
    //Entity Partical1;
    //Partical1.MakePartical(BottomPoint, 20);
    //Entity Partical2;
    //Partical2.MakePartical(BottomPoint, -20);
    //Entity Partical3;
    //Partical3.MakePartical(BottomPoint, 90);
    //Entity Partical4;
    //Partical4.MakePartical(BottomPoint, -90);
    //Entity Partical5;
    //Partical5.MakePartical(BottomPoint, 0);
    //Entity Partical6;
    //Partical6.MakePartical(BottomPoint, 40);
    //Entity Partical7;
    //Partical7.MakePartical(BottomPoint, -40);

    
    for (size_t i = 0; i < 17; i++)
    {
        Entity* Line = new Entity;
        LineVec.push_back(Line);
    }

    for (size_t i = 0; i < 17; i++)
    {
        sf::FloatRect OOB;
        OutOfBoundsVec.push_back(OOB);
    }
    
    //makes the terrain for the level the player is on.
    switch (LevelCount)
    {
    case 1:
        LoadLevel1(LZ1L1, LZ2L1, LZ3L1, LineVec, OutOfBoundsVec);
        break;
    case 2:
        LoadLevel2(LZ1L2, LZ2L2, LZ3L2, LineVec, OutOfBoundsVec);
        break;
    case 3:
        LoadLevel3(LZ1L3, LZ2L3, LZ3L3, LineVec, OutOfBoundsVec);
        break;
    case 4:
        LoadLevel4(LZ1L4, LZ2L4, LZ3L4, LineVec, OutOfBoundsVec);
        break;
    default:
        LoadLevel1(LZ1L1, LZ2L1, LZ3L1, LineVec, OutOfBoundsVec);
        break;
    }
    

    //loads font from file for text.
    sf::Font Font;

    // Load from a font file on disk
    if (!Font.loadFromFile("Font/Roboto-Black.ttf"))
    {
        std::cout << "Missing font" << std::endl;
        return;
    }

    //makes the text to be display.
    sf::Text NoFuel("You are out of fuel", Font, 50);
    NoFuel.setStyle(sf::Text::Bold);
    NoFuel.setFillColor(sf::Color::Red);
    NoFuel.setPosition(750, 400);

    sf::Text LowFuel("You are low on fuel", Font, 30);
    LowFuel.setStyle(sf::Text::Bold);
    LowFuel.setFillColor(sf::Color::Yellow);
    LowFuel.setPosition(800, 150);

    // We can still output to the console window
    std::cout << "Lander Game: Starting" << std::endl;

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        //makes ship.
        Ship.MakeShip(TopPoint, BottomLeft, BottomRight);
        if (FirstTimeBorder)
        {
            //makes the first border for ship
            ShipBorder = Ship.FirstTimeGetShipBorder();
            FirstTimeBorder = false;
        }
        else
        {
            //makes all the borders after
            ShipBorder = Ship.LoopGetShipBorder(TotalXMovement, TotalYMovement, ShipBorder);
        }
        //makes the flame at bottom of ship when thrust is on.
        Thrust.MakeShip(ThrustTopLeft, ThrustBottom, ThrustTopRight);
        //makes gameplay text for player to look at stats.
        sf::Text ScoreTex("Score: " + std::to_string(Score), Font, 20);
        ScoreTex.setStyle(sf::Text::Bold);
        ScoreTex.setFillColor(sf::Color::Cyan);
        ScoreTex.setPosition(0, 0);

        sf::Text FuelTex("Fuel: " + std::to_string(Fuel), Font, 20);
        FuelTex.setStyle(sf::Text::Bold);
        FuelTex.setFillColor(sf::Color::Cyan);
        FuelTex.setPosition(0, 20);

        sf::Text XMoveTex("XMovement: " + std::to_string(TotalXMovement), Font, 20);
        XMoveTex.setStyle(sf::Text::Bold);
        XMoveTex.setFillColor(sf::Color::Cyan);
        XMoveTex.setPosition(0, 40);

        sf::Text YMoveTex("YMovement: " + std::to_string(TotalYMovement), Font, 20);
        YMoveTex.setStyle(sf::Text::Bold);
        YMoveTex.setFillColor(sf::Color::Cyan);
        YMoveTex.setPosition(0, 60);

        sf::Text EndTex("Game Over, Your Score: " + std::to_string(Score) + ". Press W to restart or F to quit", Font, 40);
        EndTex.setStyle(sf::Text::Bold);
        EndTex.setFillColor(sf::Color::Cyan);
        EndTex.setPosition(350, 400);

        //checks for collions with LZs and the speed and angle of collion if all is good points are given if not player is put back at top.
        if (ShipBorder.intersects(LZ1))
        {
            if (RotationValue < 10 && RotationValue > -10)
            {
                if (TotalYMovement < 0.3 && TotalXMovement < 0.3)
                {

                    Score += 5;
                    if (LevelCount == 4)
                    {
                        LevelCount = 0;
                    }
                    else
                    {
                        LevelCount++;
                    }
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);

                }
                else
                {
                    if (Fuel == 0)
                    {
                        GameOver = true;
                    }
                    else
                    {
                        TotalXMovement = 0;
                        TotalYMovement = 0;
                        FirstTimeBorder = true;
                        NextLevel = true;
                        Run(window);
                    }
                    
                }
            }
            else
            {
                if (Fuel == 0)
                {
                    GameOver = true;
                }
                else
                {
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);
                }
            }
        }

        if (ShipBorder.intersects(LZ2))
        {
            if (RotationValue < 10 && RotationValue > -10)
            {
                if (TotalYMovement < 0.3 && TotalXMovement < 0.3)
                {

                    Score += 1;
                    if (LevelCount == 4)
                    {
                        LevelCount = 0;
                    }
                    else
                    {
                        LevelCount++;
                    }
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);

                }
                else
                {
                    if (Fuel == 0)
                    {
                        GameOver = true;
                    }
                    else
                    {
                        TotalXMovement = 0;
                        TotalYMovement = 0;
                        FirstTimeBorder = true;
                        NextLevel = true;
                        Run(window);
                    }

                }
            }
            else
            {
                if (Fuel == 0)
                {
                    GameOver = true;
                }
                else
                {
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);
                }
            }
        }

        if (ShipBorder.intersects(LZ3))
        {
            if (RotationValue < 10 && RotationValue > -10)
            {
                if (TotalYMovement < 0.3 && TotalXMovement < 0.3)
                {

                    Score += 2;
                    if (LevelCount == 4)
                    {
                        LevelCount = 0;
                    }
                    else
                    {
                        LevelCount++;
                    }
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);

                }
                else
                {
                    if (Fuel == 0)
                    {
                        GameOver = true;
                    }
                    else
                    {
                        TotalXMovement = 0;
                        TotalYMovement = 0;
                        FirstTimeBorder = true;
                        NextLevel = true;
                        Run(window);
                    }

                }
            }
            else
            {
                if (Fuel == 0)
                {
                    GameOver = true;
                }
                else
                {
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);
                }
            }
        }

        //checks collions with terrain.
        for (sf::FloatRect P : OutOfBoundsVec)
        {
            if (ShipBorder.intersects(P))
            {
                if (Fuel == 0)
                {
                    GameOver = true;
                }
                else
                {
                    TotalXMovement = 0;
                    TotalYMovement = 0;
                    FirstTimeBorder = true;
                    NextLevel = true;
                    Run(window);
                }
            }
        }

        //if player is dead and out of fuel this does not happen.
        if (!GameOver)
        {
            //Delta time
            DT = DTClock.restart().asSeconds();

            //Gravity
            GravCheck = G * DT;
            if (GravCheck < 0 || GravCheck > 0.6)
            {
                GravCheck = 0.165;
            }

            TotalYMovement += GravCheck;



            //how the ship rotates
            Phy.CalculateAAndAddToTheta(BottomPoint.X, BottomPoint.Y, TopPoint.X, TopPoint.Y);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && RotationValue < 56)
            {
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, TopPoint.X, TopPoint.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, BottomLeft.X, BottomLeft.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, BottomRight.X, BottomRight.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, BottomPoint.X, BottomPoint.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, ThrustTopLeft.X, ThrustTopLeft.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, ThrustTopRight.X, ThrustTopRight.Y);
                Phy.RotateTopPointRight(BottomPoint.X, BottomPoint.Y, ThrustBottom.X, ThrustBottom.Y);
                RotationValue++;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && RotationValue > -56)
            {
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, TopPoint.X, TopPoint.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, BottomLeft.X, BottomLeft.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, BottomRight.X, BottomRight.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, BottomPoint.X, BottomPoint.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, ThrustTopLeft.X, ThrustTopLeft.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, ThrustTopRight.X, ThrustTopRight.Y);
                Phy.RotateTopPointLeft(BottomPoint.X, BottomPoint.Y, ThrustBottom.X, ThrustBottom.Y);
                RotationValue--;
            }

            //thrust to move player.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Fuel > 0)
            {
                Phy.Thrust(RotationValue, TotalXMovement, TotalYMovement, DT);
                size_t i = 0;
                ThrustOn = true;
                Fuel -= 0.5;
            }
            else if (Fuel <= 0)
            {
                ThrustOn = false;
            }
            else
            {
                ThrustOn = false;
            }

            //moves the ship with the values stored.
            Ship.move(TotalXMovement, TotalYMovement);
            Thrust.move(TotalXMovement, TotalYMovement);

            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                }
            }

            // We must clear the window each time around the loop
            window.clear();
            //draws all the entities in the game and terrain depending on level
            window.draw(Ship);
            if (ThrustOn)
            {
                window.draw(Thrust);
            }
            switch (LevelCount)
            {
            case 1:
                window.draw(TerrainL);
                window.draw(LZ1L1);
                window.draw(LZ2L1);
                window.draw(LZ3L1);
                break;
            case 2:
                window.draw(TerrainL);
                window.draw(LZ1L2);
                window.draw(LZ2L2);
                window.draw(LZ3L2);
                break;
            case 3:
                window.draw(TerrainL);
                window.draw(LZ1L3);
                window.draw(LZ2L3);
                window.draw(LZ3L3);
                break;
            case 4:
                window.draw(TerrainL);
                window.draw(LZ1L4);
                window.draw(LZ2L4);
                window.draw(LZ3L4);
                break;
            default:
                window.draw(TerrainL);
                window.draw(LZ1L1);
                window.draw(LZ2L1);
                window.draw(LZ3L1);
                break;
            }
            window.draw(ScoreTex);
            window.draw(FuelTex);
            window.draw(XMoveTex);
            window.draw(YMoveTex);

            //displays warrning text to player about fuel.
            if (FuelWarningCount > 5 && FuelWarningCount <= 8)
            {
                if (Fuel <= 250 && Fuel > 0)
                {
                    window.draw(LowFuel);

                    if (FuelWarningCount < 8)
                    {
                        FuelWarningCount += 5 * DT;
                    }
                }

                if (FuelWarningCount >= 8)
                {
                    FuelWarningCount = 0;
                }
            }
            else if (FuelWarningCount <= 5)
            {
                FuelWarningCount += 5 * DT;
            }

            if (Fuel <= 0)
            {
                window.draw(NoFuel);
            }
            window.display();
        }

        //what happens when player is dead and out of fuel
        if (GameOver)
        {
            TotalXMovement = 0;
            TotalYMovement = 0;
            FirstTimeBorder = true;
            NextLevel = true;
            window.clear();
            window.draw(EndTex);
            window.display();
            //ask the player if they want to play again or quit
            while (1 != 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    Run(window);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    window.close();
                }
            }
        }
        // Get the window to display its contents
        

       
            
   
    }

    std::cout << "Lander Game: Finished" << std::endl;

}

void Game::LoadLevel1(Entity& LZ1L1, Entity& LZ2L1, Entity& LZ3L1, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec)
{
    TerrainOutOfBounds1.clear();
    TerrainOutOfBounds1.setPrimitiveType(sf::LinesStrip);
    TerrainOutOfBounds1.resize(18);
    TerrainOutOfBounds1[0] = sf::Vector2f(0, TerrainYLevel1[0]);
    TerrainOutOfBounds1[1] = sf::Vector2f(300, TerrainYLevel1[1]);
    TerrainOutOfBounds1[2] = sf::Vector2f(350, TerrainYLevel1[2]);
    TerrainOutOfBounds1[3] = sf::Vector2f(500, TerrainYLevel1[3]);
    TerrainOutOfBounds1[4] = sf::Vector2f(620, TerrainYLevel1[4]);
    TerrainOutOfBounds1[5] = sf::Vector2f(800, TerrainYLevel1[5]);
    TerrainOutOfBounds1[6] = sf::Vector2f(850, TerrainYLevel1[6]);
    TerrainOutOfBounds1[7] = sf::Vector2f(900, TerrainYLevel1[7]);
    TerrainOutOfBounds1[8] = sf::Vector2f(1050, TerrainYLevel1[8]);
    TerrainOutOfBounds1[9] = sf::Vector2f(1080, TerrainYLevel1[9]);
    TerrainOutOfBounds1[10] = sf::Vector2f(1250, TerrainYLevel1[10]);
    TerrainOutOfBounds1[11] = sf::Vector2f(1350, TerrainYLevel1[11]);
    TerrainOutOfBounds1[12] = sf::Vector2f(1475, TerrainYLevel1[12]);
    TerrainOutOfBounds1[13] = sf::Vector2f(1635, TerrainYLevel1[13]);
    TerrainOutOfBounds1[14] = sf::Vector2f(1755, TerrainYLevel1[14]);
    TerrainOutOfBounds1[15] = sf::Vector2f(1840, TerrainYLevel1[15]);
    TerrainOutOfBounds1[16] = sf::Vector2f(1875, TerrainYLevel1[16]);
    TerrainOutOfBounds1[17] = sf::Vector2f(1920, TerrainYLevel1[17]);

    for (size_t i = 0; i < 9; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }  
    
    for (size_t i = 10; i < 17; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }

    TerrainL.clear();
    TerrainL.setPrimitiveType(sf::LinesStrip);
    TerrainL.resize(24);
    TerrainL[0] = sf::Vector2f(0, TerrainYLevel1[0]);
    TerrainL[1] = sf::Vector2f(300, TerrainYLevel1[1]);
    TerrainL[2] = sf::Vector2f(350, TerrainYLevel1[2]);
    TerrainL[3] = sf::Vector2f(500, TerrainYLevel1[3]);
    TerrainL[4] = sf::Vector2f(620, TerrainYLevel1[4]);
    TerrainL[5] = sf::Vector2f(670, 1008);
    TerrainL[6] = sf::Vector2f(700, 1008);
    TerrainL[7] = sf::Vector2f(800, TerrainYLevel1[5]);
    TerrainL[8] = sf::Vector2f(850, TerrainYLevel1[6]);
    TerrainL[9] = sf::Vector2f(900, TerrainYLevel1[7]);
    TerrainL[10] = sf::Vector2f(1050, TerrainYLevel1[8]);
    TerrainL[11] = sf::Vector2f(1080, TerrainYLevel1[9]);
    TerrainL[12] = sf::Vector2f(1100, 900);
    TerrainL[13] = sf::Vector2f(1200, 900);
    TerrainL[14] = sf::Vector2f(1250, TerrainYLevel1[10]);
    TerrainL[15] = sf::Vector2f(1350, TerrainYLevel1[11]);
    TerrainL[16] = sf::Vector2f(1475, TerrainYLevel1[12]);
    TerrainL[17] = sf::Vector2f(1500, 450);
    TerrainL[18] = sf::Vector2f(1550, 450);
    TerrainL[19] = sf::Vector2f(1635, TerrainYLevel1[13]);
    TerrainL[20] = sf::Vector2f(1755, TerrainYLevel1[14]);
    TerrainL[21] = sf::Vector2f(1840, TerrainYLevel1[15]);
    TerrainL[22] = sf::Vector2f(1875, TerrainYLevel1[16]);
    TerrainL[23] = sf::Vector2f(1920, TerrainYLevel1[17]);


    LZ1L1.MakeLandingZones(TerrainL[5], TerrainL[6]);
    LZ1 = LZ1L1.GetLZBorder();

    LZ2L1.MakeLandingZones(TerrainL[12], TerrainL[13]);
    LZ2 = LZ2L1.GetLZBorder();

    LZ3L1.MakeLandingZones(TerrainL[17], TerrainL[18]);
    LZ3 = LZ3L1.GetLZBorder();
 }

void Game::LoadLevel2(Entity& LZ1L2, Entity& LZ2L2, Entity& LZ3L2, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec)
{
    TerrainOutOfBounds1.clear();
    TerrainOutOfBounds1.setPrimitiveType(sf::LinesStrip);
    TerrainOutOfBounds1.resize(18);
    TerrainOutOfBounds1[0] = sf::Vector2f(0, TerrainYLevel2[0]);
    TerrainOutOfBounds1[1] = sf::Vector2f(150, TerrainYLevel2[1]);
    TerrainOutOfBounds1[2] = sf::Vector2f(300, TerrainYLevel2[2]);
    TerrainOutOfBounds1[3] = sf::Vector2f(420, TerrainYLevel2[3]);
    TerrainOutOfBounds1[4] = sf::Vector2f(520, TerrainYLevel2[4]);
    TerrainOutOfBounds1[5] = sf::Vector2f(650, TerrainYLevel2[5]);
    TerrainOutOfBounds1[6] = sf::Vector2f(750, TerrainYLevel2[6]);
    TerrainOutOfBounds1[7] = sf::Vector2f(800, TerrainYLevel2[7]);
    TerrainOutOfBounds1[8] = sf::Vector2f(950, TerrainYLevel2[8]);
    TerrainOutOfBounds1[9] = sf::Vector2f(1050, TerrainYLevel2[9]);
    TerrainOutOfBounds1[10] = sf::Vector2f(1250, TerrainYLevel2[10]);
    TerrainOutOfBounds1[11] = sf::Vector2f(1300, TerrainYLevel2[11]);
    TerrainOutOfBounds1[12] = sf::Vector2f(1400, TerrainYLevel2[12]);
    TerrainOutOfBounds1[13] = sf::Vector2f(1635, TerrainYLevel2[13]);
    TerrainOutOfBounds1[14] = sf::Vector2f(1705, TerrainYLevel2[14]);
    TerrainOutOfBounds1[15] = sf::Vector2f(1740, TerrainYLevel2[15]);
    TerrainOutOfBounds1[16] = sf::Vector2f(1875, TerrainYLevel2[16]);
    TerrainOutOfBounds1[17] = sf::Vector2f(1920, TerrainYLevel2[17]);


    for (size_t i = 0; i < 9; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }

    for (size_t i = 10; i < 17; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }


    TerrainL.clear();
    TerrainL.setPrimitiveType(sf::LinesStrip);
    TerrainL.resize(24);
    TerrainL[0] = sf::Vector2f(0, TerrainYLevel2[0]);
    TerrainL[1] = sf::Vector2f(150, TerrainYLevel2[1]);
    TerrainL[2] = sf::Vector2f(200, 450);
    TerrainL[3] = sf::Vector2f(235, 450);
    TerrainL[4] = sf::Vector2f(300, TerrainYLevel2[2]);
    TerrainL[5] = sf::Vector2f(420, TerrainYLevel2[3]);
    TerrainL[6] = sf::Vector2f(520, TerrainYLevel2[4]);
    TerrainL[7] = sf::Vector2f(650, TerrainYLevel2[5]);
    TerrainL[8] = sf::Vector2f(750, TerrainYLevel2[6]);
    TerrainL[9] = sf::Vector2f(800, TerrainYLevel2[7]);
    TerrainL[10] = sf::Vector2f(950, TerrainYLevel2[8]);
    TerrainL[11] = sf::Vector2f(1050, TerrainYLevel2[9]);
    TerrainL[12] = sf::Vector2f(1100, 1010);
    TerrainL[13] = sf::Vector2f(1200, 1010);
    TerrainL[14] = sf::Vector2f(1250, TerrainYLevel2[10]);
    TerrainL[15] = sf::Vector2f(1300, TerrainYLevel2[11]);
    TerrainL[16] = sf::Vector2f(1400, TerrainYLevel2[12]);
    TerrainL[17] = sf::Vector2f(1450, 800);
    TerrainL[18] = sf::Vector2f(1500, 800);
    TerrainL[19] = sf::Vector2f(1635, TerrainYLevel2[13]);
    TerrainL[20] = sf::Vector2f(1705, TerrainYLevel2[14]);
    TerrainL[21] = sf::Vector2f(1740, TerrainYLevel2[15]);
    TerrainL[22] = sf::Vector2f(1875, TerrainYLevel2[16]);
    TerrainL[23] = sf::Vector2f(1920, TerrainYLevel2[17]);

    LZ1L2.MakeLandingZones(TerrainL[2], TerrainL[3]);
    LZ1 = LZ1L2.GetLZBorder();

    LZ2L2.MakeLandingZones(TerrainL[12], TerrainL[13]);
    LZ2 = LZ2L2.GetLZBorder();

    LZ3L2.MakeLandingZones(TerrainL[17], TerrainL[18]);
    LZ3 = LZ3L2.GetLZBorder();
}

void Game::LoadLevel3(Entity& LZ1L3, Entity& LZ2L3, Entity& LZ3L3, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec)
{
    TerrainOutOfBounds1.clear();
    TerrainOutOfBounds1.setPrimitiveType(sf::LinesStrip);
    TerrainOutOfBounds1.resize(18);
    TerrainOutOfBounds1[0] = sf::Vector2f(0, TerrainYLevel3[0]);
    TerrainOutOfBounds1[1] = sf::Vector2f(300, TerrainYLevel3[1]);
    TerrainOutOfBounds1[2] = sf::Vector2f(350, TerrainYLevel3[2]);
    TerrainOutOfBounds1[3] = sf::Vector2f(500, TerrainYLevel3[3]);
    TerrainOutOfBounds1[4] = sf::Vector2f(620, TerrainYLevel3[4]);
    TerrainOutOfBounds1[5] = sf::Vector2f(800, TerrainYLevel3[5]);
    TerrainOutOfBounds1[6] = sf::Vector2f(850, TerrainYLevel3[6]);
    TerrainOutOfBounds1[7] = sf::Vector2f(900, TerrainYLevel3[7]);
    TerrainOutOfBounds1[8] = sf::Vector2f(1050, TerrainYLevel3[8]);
    TerrainOutOfBounds1[9] = sf::Vector2f(1080, TerrainYLevel3[9]);
    TerrainOutOfBounds1[10] = sf::Vector2f(1250, TerrainYLevel3[10]);
    TerrainOutOfBounds1[11] = sf::Vector2f(1350, TerrainYLevel3[11]);
    TerrainOutOfBounds1[12] = sf::Vector2f(1475, TerrainYLevel3[12]);
    TerrainOutOfBounds1[13] = sf::Vector2f(1635, TerrainYLevel3[13]);
    TerrainOutOfBounds1[14] = sf::Vector2f(1755, TerrainYLevel3[14]);
    TerrainOutOfBounds1[15] = sf::Vector2f(1840, TerrainYLevel3[15]);
    TerrainOutOfBounds1[16] = sf::Vector2f(1875, TerrainYLevel3[16]);
    TerrainOutOfBounds1[17] = sf::Vector2f(1920, TerrainYLevel3[17]);

    for (size_t i = 0; i < 9; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }

    for (size_t i = 10; i < 17; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }


    TerrainL.clear();
    TerrainL.setPrimitiveType(sf::LinesStrip);
    TerrainL.resize(24);
    TerrainL[0] = sf::Vector2f(0, TerrainYLevel1[0]);
    TerrainL[1] = sf::Vector2f(300, TerrainYLevel1[1]);
    TerrainL[2] = sf::Vector2f(350, TerrainYLevel1[2]);
    TerrainL[3] = sf::Vector2f(500, TerrainYLevel1[3]);
    TerrainL[4] = sf::Vector2f(620, TerrainYLevel1[4]);
    TerrainL[5] = sf::Vector2f(630, 750);
    TerrainL[6] = sf::Vector2f(670, 750);
    TerrainL[7] = sf::Vector2f(800, TerrainYLevel1[5]);
    TerrainL[8] = sf::Vector2f(850, TerrainYLevel1[6]);
    TerrainL[9] = sf::Vector2f(900, TerrainYLevel1[7]);
    TerrainL[10] = sf::Vector2f(1050, TerrainYLevel1[8]);
    TerrainL[11] = sf::Vector2f(1080, TerrainYLevel1[9]);
    TerrainL[12] = sf::Vector2f(1100, 800);
    TerrainL[13] = sf::Vector2f(1200, 800);
    TerrainL[14] = sf::Vector2f(1250, TerrainYLevel1[10]);
    TerrainL[15] = sf::Vector2f(1350, TerrainYLevel1[11]);
    TerrainL[16] = sf::Vector2f(1475, TerrainYLevel1[12]);
    TerrainL[17] = sf::Vector2f(1500, 954);
    TerrainL[18] = sf::Vector2f(1550, 954);
    TerrainL[19] = sf::Vector2f(1635, TerrainYLevel1[13]);
    TerrainL[20] = sf::Vector2f(1755, TerrainYLevel1[14]);
    TerrainL[21] = sf::Vector2f(1840, TerrainYLevel1[15]);
    TerrainL[22] = sf::Vector2f(1875, TerrainYLevel1[16]);
    TerrainL[23] = sf::Vector2f(1920, TerrainYLevel1[17]);


    LZ1L3.MakeLandingZones(TerrainL[5], TerrainL[6]);
    LZ1 = LZ1L3.GetLZBorder();

    LZ2L3.MakeLandingZones(TerrainL[12], TerrainL[13]);
    LZ2 = LZ2L3.GetLZBorder();

    LZ3L3.MakeLandingZones(TerrainL[17], TerrainL[18]);
    LZ3 = LZ3L3.GetLZBorder();
}

void Game::LoadLevel4(Entity& LZ1L4, Entity& LZ2L4, Entity& LZ3L4, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec)
{
    TerrainOutOfBounds1.clear();
    TerrainOutOfBounds1.setPrimitiveType(sf::LinesStrip);
    TerrainOutOfBounds1.resize(18);
    TerrainOutOfBounds1[0] = sf::Vector2f(0, TerrainYLevel2[0]);
    TerrainOutOfBounds1[1] = sf::Vector2f(150, TerrainYLevel2[1]);
    TerrainOutOfBounds1[2] = sf::Vector2f(300, TerrainYLevel2[2]);
    TerrainOutOfBounds1[3] = sf::Vector2f(420, TerrainYLevel2[3]);
    TerrainOutOfBounds1[4] = sf::Vector2f(520, TerrainYLevel2[4]);
    TerrainOutOfBounds1[5] = sf::Vector2f(650, TerrainYLevel2[5]);
    TerrainOutOfBounds1[6] = sf::Vector2f(750, TerrainYLevel2[6]);
    TerrainOutOfBounds1[7] = sf::Vector2f(800, TerrainYLevel2[7]);
    TerrainOutOfBounds1[8] = sf::Vector2f(950, TerrainYLevel2[8]);
    TerrainOutOfBounds1[9] = sf::Vector2f(1050, TerrainYLevel2[9]);
    TerrainOutOfBounds1[10] = sf::Vector2f(1250, TerrainYLevel2[10]);
    TerrainOutOfBounds1[11] = sf::Vector2f(1300, TerrainYLevel2[11]);
    TerrainOutOfBounds1[12] = sf::Vector2f(1400, TerrainYLevel2[12]);
    TerrainOutOfBounds1[13] = sf::Vector2f(1635, TerrainYLevel2[13]);
    TerrainOutOfBounds1[14] = sf::Vector2f(1705, TerrainYLevel2[14]);
    TerrainOutOfBounds1[15] = sf::Vector2f(1740, TerrainYLevel2[15]);
    TerrainOutOfBounds1[16] = sf::Vector2f(1875, TerrainYLevel2[16]);
    TerrainOutOfBounds1[17] = sf::Vector2f(1920, TerrainYLevel2[17]);


    for (size_t i = 0; i < 9; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }

    for (size_t i = 10; i < 17; i++)
    {
        LineVec[i]->MakeOutOfBounds(TerrainOutOfBounds1[i], TerrainOutOfBounds1[i + 1]);
        OutOfBoundsVec[i] = LineVec[i]->GetLZBorder();
    }


    TerrainL.clear();
    TerrainL.setPrimitiveType(sf::LinesStrip);
    TerrainL.resize(24);
    TerrainL[0] = sf::Vector2f(0, TerrainYLevel2[0]);
    TerrainL[1] = sf::Vector2f(150, TerrainYLevel2[1]);
    TerrainL[2] = sf::Vector2f(180, 675);
    TerrainL[3] = sf::Vector2f(220, 675);
    TerrainL[4] = sf::Vector2f(300, TerrainYLevel2[2]);
    TerrainL[5] = sf::Vector2f(420, TerrainYLevel2[3]);
    TerrainL[6] = sf::Vector2f(520, TerrainYLevel2[4]);
    TerrainL[7] = sf::Vector2f(650, TerrainYLevel2[5]);
    TerrainL[8] = sf::Vector2f(750, TerrainYLevel2[6]);
    TerrainL[9] = sf::Vector2f(800, TerrainYLevel2[7]);
    TerrainL[10] = sf::Vector2f(950, TerrainYLevel2[8]);
    TerrainL[11] = sf::Vector2f(1050, TerrainYLevel2[9]);
    TerrainL[12] = sf::Vector2f(1100, 350);
    TerrainL[13] = sf::Vector2f(1200, 350);
    TerrainL[14] = sf::Vector2f(1250, TerrainYLevel2[10]);
    TerrainL[15] = sf::Vector2f(1300, TerrainYLevel2[11]);
    TerrainL[16] = sf::Vector2f(1400, TerrainYLevel2[12]);
    TerrainL[17] = sf::Vector2f(1450, 847);
    TerrainL[18] = sf::Vector2f(1500, 847);
    TerrainL[19] = sf::Vector2f(1635, TerrainYLevel2[13]);
    TerrainL[20] = sf::Vector2f(1705, TerrainYLevel2[14]);
    TerrainL[21] = sf::Vector2f(1740, TerrainYLevel2[15]);
    TerrainL[22] = sf::Vector2f(1875, TerrainYLevel2[16]);
    TerrainL[23] = sf::Vector2f(1920, TerrainYLevel2[17]);

    LZ1L4.MakeLandingZones(TerrainL[2], TerrainL[3]);
    LZ1 = LZ1L4.GetLZBorder();

    LZ2L4.MakeLandingZones(TerrainL[12], TerrainL[13]);
    LZ2 = LZ2L4.GetLZBorder();

    LZ3L4.MakeLandingZones(TerrainL[17], TerrainL[18]);
    LZ3 = LZ3L4.GetLZBorder();
}
