/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include "Game.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Lander");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    Game Game;
    Game.Run(window);
    return 0;
}
