#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include<time.h>
#include "PivotPoint.h"
#include <stdlib.h>
#include <vector>
//#include <windows.h>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>


class Entity : public sf::Drawable, public sf::Transformable
{
protected:

    //used to draw the entity
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // draw the vertex array
        target.draw(Lander, states);
        target.draw(LandingZone, states);
    }

    sf::ConvexShape Lander;
    sf::ConvexShape LandingZone;
    sf::ConvexShape Partical;
    bool Alive{ false };
    float StartSpeed{ 100 };
    float EndSpeed{ 50 };
    float SpeedT{ 0 };
    float Speed{ 0 };
    float StartSize{ 5 };
    float EndSize{ 1 };
    float SizeT{ 0 };
    float Size{ 0 };
    int Angle{ 0 };
    int LifeTime{ 20 };
    int TimeAlive{ 0 };
    float XPos{ 0 }, YPos{ 0 };
    float XVelocity{ 0 }, YVelocity{ 0 };

public:

    Entity() {};

    //function to make ship
    void MakeShip(PivotPoint TopPoint, PivotPoint BottomLeft, PivotPoint BottomRight)
    {
        Lander.setPointCount(3);
        Lander.setPoint(0, sf::Vector2f(TopPoint.X, TopPoint.Y));
        Lander.setPoint(1, sf::Vector2f(BottomLeft.X, BottomLeft.Y));
        Lander.setPoint(2, sf::Vector2f(BottomRight.X, BottomRight.Y));

        Lander.setFillColor(sf::Color::Black);
        Lander.setOutlineThickness(1.f);
        Lander.setOutlineColor(sf::Color::White);
    }

    //function to make LZs
    void MakeLandingZones(sf::Vertex TerrainP1, sf::Vertex TerrainP2)
    {
        sf::Vector2f T1 = TerrainP1.position;
        sf::Vector2f T2 = TerrainP2.position;
        sf::Vector2f T3 = T2;
        T3.y++;
        sf::Vector2f T4 = T1;
        T4.y++;
        LandingZone.setPointCount(4);
        LandingZone.setPoint(0, T1);
        LandingZone.setPoint(1, T2);
        LandingZone.setPoint(2, T3);
        LandingZone.setPoint(3, T4);


        LandingZone.setFillColor(sf::Color::Yellow);
    }

    //function to make out of bounds
    void MakeOutOfBounds(sf::Vertex TerrainP1, sf::Vertex TerrainP2)
    {
        sf::Vector2f T1 = TerrainP1.position;
        sf::Vector2f T2 = TerrainP2.position;
        sf::Vector2f T3 = T2;
        T3.y++;
        sf::Vector2f T4 = T1;
        T4.y++;
        LandingZone.setPointCount(4);
        LandingZone.setPoint(0, T1);
        LandingZone.setPoint(1, T2);
        LandingZone.setPoint(2, T3);
        LandingZone.setPoint(3, T4);


        LandingZone.setFillColor(sf::Color::White);
    }

    //Atemted at partical
    /*void MakePartical(PivotPoint Point, float Theta)
    {
        Angle = Theta;
        Alive = true;
        sf::Vector2f T1(0, 0);
        sf::Vector2f T2(0, 0);
        sf::Vector2f T3 = T2;
        T3.y += Size;
        sf::Vector2f T4 = T1;
        T4.y += Size;
        Partical.setPointCount(4);
        Partical.setPoint(0, T1);
        Partical.setPoint(1, T2);
        Partical.setPoint(2, T3);
        Partical.setPoint(3, T4);

        sf::FloatRect Bounds = Partical.getLocalBounds();
        Partical.setOrigin(Bounds.width/2, Bounds.top);

        XPos = Point.X;
        YPos = Point.Y;

        Partical.setPosition(XPos, YPos);

        Partical.setFillColor(sf::Color::White);
    }*/

    /*bool IsAlive()
    {
        return Alive;
    }*/

    /*void UpdatePartical(float DT)
    {
        if (Alive && TimeAlive <= LifeTime)
        {
            SpeedT = TimeAlive / LifeTime;
            Speed = StartSpeed + SpeedT * (EndSpeed - StartSpeed);
            XVelocity = Speed * cos(Angle);
            YVelocity = Speed * sin(Angle);

            XPos += XVelocity * DT;
            YPos += YVelocity * DT;

            Size = StartSize + SizeT * (EndSize - StartSize);

            Partical.setPosition(XPos, YPos);


            TimeAlive++;
        }
        else
        {
            Alive = false;
        }
    }*/
   
    //gets borders for terrain and ship.
    sf::FloatRect GetLZBorder() const
    {
        return LandingZone.getGlobalBounds();
    }

    sf::FloatRect FirstTimeGetShipBorder() const
    {
        return Lander.getGlobalBounds();
    }

    sf::FloatRect LoopGetShipBorder(float X, float Y, sf::FloatRect OldBorder)
    {
        sf::FloatRect NewBorder = OldBorder;
        NewBorder.left += X;
        NewBorder.top += Y;
        return NewBorder;
    }

};
#endif

