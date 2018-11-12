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

int main()
{
    // Game main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Sargittarius 2.X");

    Planet planet = Planet(75, sf::Vector2f(100, 100));
    PlanetList pl;
    pl.Push(planet);
    Player player = Player(planet);
    Arrow arrow = Arrow(player);
    arrow.position = sf::Vector2f(0, 0);
    arrow.velocity = sf::Vector2f(0.25, 0.25);
    
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.position += 16 / player.planet.radius;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.position -= 16 / player.planet.radius;
        }
        // Clear and display window (very self-explanatory)
        // Anything that needs to be drawn needs to be drawn in between those two commands
        window.clear(sf::Color::Black);
        
        window.draw(pl.head->planet.Draw());

        window.draw(player.Draw());

        arrow.Update(pl);
        window.draw(arrow.Draw().vertex, 2, sf::Lines);

        window.display();
    }

    return 0;
}
