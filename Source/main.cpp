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
#include <time.h>

#ifndef IOSTREAM
#include <iostream>
#endif

enum Part
{
    Walking,
    Aiming,
    Shooting
};

bool Collide(PlanetList planets, Planet tempPlanet)
{
    PlanetLink *curr = planets.head;
    while(curr)
    {
        if(
            (curr->planet.radius + tempPlanet.radius + 24)*(curr->planet.radius + tempPlanet.radius + 24) >
            ((curr->planet.position.x - tempPlanet.position.x)*(curr->planet.position.x - tempPlanet.position.x))+((curr->planet.position.y - tempPlanet.position.y)*(curr->planet.position.y - tempPlanet.position.y))
        ) return true;
        curr = curr->next;
    }
    return false;
}

int NumOfPlayersAlive(PlayerList list)
{
    PlayerLink *current = list.head;
    int num = 0;
    while(current)
    {
        if(current->player.isAlive)
        {
            num++;
        }
        current = current->next;
    }
    return num;
}

int main()
{
    srand(time(NULL));
    // Game main window
    sf::VideoMode desktopWindowMode = sf::VideoMode::getDesktopMode();
    unsigned int WINDOW_WIDTH, WINDOW_HEIGHT;
    WINDOW_WIDTH = 640;//desktopWindowMode.width;
    WINDOW_HEIGHT = 480;//desktopWindowMode.height;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sargittarius 2.X", sf::Style::Default);
    window.setPosition(sf::Vector2i(0, 0));

    Part part = Walking;
    int numOfPlayers = 2;
    int numOfPlanets = 3;

    PlanetList planets;
    PlayerList players;
    ArrowList arrows;
    
    for(; numOfPlanets > 0; numOfPlanets--)
    {
        Planet tempPlanet;
        do
        {
            tempPlanet = Planet(WINDOW_WIDTH, WINDOW_HEIGHT);

            window.clear();
            PlanetLink *currPlanet = planets.head;
            while(currPlanet)
            {
                window.draw(currPlanet->planet.Draw());
                currPlanet = currPlanet->next;
            }window.draw(tempPlanet.Draw());
            window.display();

        }while(Collide(planets, tempPlanet));
        planets.Push(tempPlanet);
    }

    PlanetLink *plan = planets.head;
    for(int nop = numOfPlayers; nop > 0 && plan; nop--)
    {
        players.Push(Player(plan->planet));
        plan = plan->next;
    }

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
            arrows.head->arrow.position = currentPlayer->player.planet.position + sf::Vector2f(cos(currentPlayer->player.position*PI*2/360), sin(currentPlayer->player.position*PI*2/360)) * (currentPlayer->player.planet.radius + 10) + 35.f*sf::Vector2f((mouseAim[0].position.x - mouseAim[1].position.x)/tempDist, (mouseAim[0].position.y - mouseAim[1].position.y)/tempDist);
            arrows.head->arrow.velocity = sf::Vector2f((mouseAim[0].position.x - mouseAim[1].position.x)/500, (mouseAim[0].position.y - mouseAim[1].position.y)/500);
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
            else part = Shooting;
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
            if(currPlayer->player.isAlive) window.draw(currPlayer->player.Draw());
            currPlayer = currPlayer->next;
        }

        ArrowLink *currArrow = arrows.head;
        if(part == Shooting && currArrow->arrow.Update(planets, players))
        {
            if(NumOfPlayersAlive(players) > 0)
                do
                {
                    currentPlayer = currentPlayer->next;
                    if(!currentPlayer) currentPlayer = players.head;
                } while(!currentPlayer->player.isAlive);
            else
            {
                //TODO: What to do when there are no players left?
                window.close();
            }

            part = Walking;
        }
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
