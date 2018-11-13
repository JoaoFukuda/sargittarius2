/*
    Sargittarius 2 - Game about arrows and weird laws of gravity
    Copyright (C) 2018 - João Francisco Cocca Fukuda

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    If in any doubts, contact me at <joao.fukuda@usp.br>
 */

//        |
// Needed V (I already forgot it's purpose, but keep it)
#define SFML_STATIC

// Include on sub-files later on (this is just a placeholder for now... or not)
#include <SFML/Window.hpp>
#include "object.hpp"

#ifndef IOSTREAM
#include <iostream>
#endif

enum Part
{
    Walking,
    Aiming,
    Shooting
};

int main()
{
    // Game main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Sargittarius 2.X", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    Part part = Walking;

    PlanetList planets;
    PlayerList players;
    ArrowList arrows;
    
    // CHANGE TO BE AN AUTOMATIC PLANET/PLAYER CREATOR
    //-------------------------------------------------
    Planet planet = Planet(75, sf::Vector2f(200, 100));
    planets.Push(planet);
    planet = Planet(40, sf::Vector2f(450, 300));
    planets.Push(planet);
    planet = Planet(52, sf::Vector2f(150, 350));
    planets.Push(planet);

    Player player = Player(planets.head->planet);
    players.Push(player);
    //-------------------------------------------------

    PlayerLink *currentPlayer = players.head;
    sf::Vertex mouseAim[2];
    // Game main loop
    while(window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Input handling at it's best
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        if(part != Shooting && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(part != Aiming)
            {
                mouseAim[0] = sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window)));
                Arrow arrow = Arrow(currentPlayer->player);
                arrows.Push(arrow);
                part = Aiming;
            }
            mouseAim[1] = sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window)));
            float tempDist = sqrt((mouseAim[0].position.x - mouseAim[1].position.x)*(mouseAim[0].position.x - mouseAim[1].position.x) + (mouseAim[0].position.y - mouseAim[1].position.y)*(mouseAim[0].position.y - mouseAim[1].position.y));
            arrows.head->arrow.position = currentPlayer->player.planet.position + sf::Vector2f(cos(currentPlayer->player.position*PI*2/360), sin(currentPlayer->player.position*PI*2/360)) * (planet.radius + 10) + 35.f*sf::Vector2f((mouseAim[0].position.x - mouseAim[1].position.x)/tempDist, (mouseAim[0].position.y - mouseAim[1].position.y)/tempDist);
            arrows.head->arrow.velocity = sf::Vector2f((mouseAim[0].position.x - mouseAim[1].position.x)/1000, (mouseAim[0].position.y - mouseAim[1].position.y)/1000);
        }
        if(part == Aiming && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if((arrows.head->arrow.velocity.x*1000)*(arrows.head->arrow.velocity.x*1000) < 25 && (arrows.head->arrow.velocity.y*1000)*(arrows.head->arrow.velocity.y*1000) < 25)
            {
                ArrowLink *aux = arrows.head;
                arrows.head = arrows.head->next;
                free(aux);
                part = Walking;
            }
            else
            {
                currentPlayer = currentPlayer->next;
                if(!currentPlayer) currentPlayer = players.head;
                part = Shooting;
            }
        }
        if(part == Walking)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                currentPlayer->player.position += 16 / currentPlayer->player.planet.radius;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                currentPlayer->player.position -= 16 / currentPlayer->player.planet.radius;
            }
        }

        // Clear and display window (very self-explanatory)
        // Anything that needs to be drawn needs to be drawn in between those two commands
        window.clear(sf::Color::Black);
        
        PlanetLink *currPlanet = planets.head;
        while(currPlanet)
        {
            window.draw(currPlanet->planet.Draw());
            currPlanet = currPlanet->next;
        }

        PlayerLink *currPlayer = players.head;
        while(currPlayer)
        {
            window.draw(currPlayer->player.Draw());
            currPlayer = currPlayer->next;
        }

        ArrowLink *currArrow = arrows.head;
        if(part == Shooting && currArrow->arrow.Update(planets)) part = Walking;
        while(currArrow)
        {
            window.draw(currArrow->arrow.Draw().vertex, 2, sf::Lines);
            currArrow = currArrow->next;
        }
        if(part == Aiming) window.draw(mouseAim, 2, sf::Lines);

        window.display();
    }

    system("pause");

    return 0;
}
