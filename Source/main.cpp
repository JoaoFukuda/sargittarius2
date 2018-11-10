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

int main()
{
    // Game main window
    sf::Window window(sf::VideoMode(640, 480), "Sargittarius 2.X");
    
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

        // Key handling
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
    }

    return 0;
}
