#ifndef GAME_H
#define GAME_H
#include <iostream>
#include<time.h>
#include <stdlib.h>
#include "PivotPoint.h"
#include <vector>
//#include <windows.h>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

class Entity;

class Game
{
private:
	float G{ 0.165 };
	float GravCheck{ 0 };
	float TotalYMovement{ 0 };
	float TotalXMovement{ 0 };
	float LanderThrust{ 0 };
	float Fuel{ 2000 };
	float FuelWarningCount{ 0 };
	int Score{ 0 };
	int RotationValue{ 0 };
	int LevelCount{ 1 };
	std::vector<float> TerrainYLevel1;
	std::vector<float> TerrainYLevel2;
	std::vector<float> TerrainYLevel3;
	std::vector<float> TerrainYLevel4;
	bool ThrustOn{ false };
	bool FirstTimeBorder{ true };
	float DT{ 0 };
	sf::Clock DTClock;
	sf::FloatRect ShipBorder;
	sf::FloatRect LZ1;
	sf::FloatRect LZ2;
	sf::FloatRect LZ3;
	sf::VertexArray TerrainL;
	sf::VertexArray TerrainOutOfBounds1;
	bool NextLevel{ false };
	bool GameOver{ false };
	PivotPoint StartPoint{ 0.f, 0.f};
	PivotPoint TopPoint{ 0.f, 0.f };
	PivotPoint BottomLeft{ 0.f, 0.f };
	PivotPoint BottomRight{ 0.f , 0.f };
	PivotPoint BottomPoint{ 0.f, 0.f };
	PivotPoint ThrustTopLeft{ 0.f, 0.f };
	PivotPoint ThrustTopRight{ 0.f, 0.f };
	PivotPoint ThrustBottom{ 0.f, 0.f };
	std::vector<Entity*> LineVec;
	std::vector<sf::FloatRect> OutOfBoundsVec;
public:
	~Game()
	{
		for (Entity* P : LineVec)
			delete P;
	}
	void Run(sf::RenderWindow& window);

	void LoadLevel1(Entity& LZ1L1, Entity& LZ2L1, Entity& LZ3L1, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec);
	void LoadLevel2(Entity& LZ1L2, Entity& LZ2L2, Entity& LZ3L2, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec);
	void LoadLevel3(Entity& LZ1L3, Entity& LZ2L3, Entity& LZ3L3, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec);
	void LoadLevel4(Entity& LZ1L4, Entity& LZ2L4, Entity& LZ3L4, std::vector<Entity*> LineVec, std::vector<sf::FloatRect>& OutOfBoundsVec);
};
#endif
