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

#include <SFML/Graphics.hpp>

struct Line
{
    sf::Vertex vertex[2];

    Line(sf::Vertex line[])
    {
        vertex[0] = line[0];
        vertex[1] = line[1];
    };
};

class Planet
{
public:
    sf::Vector2f position;
    float radius;
    Planet(){};
    Planet(float radius, sf::Vector2f position);
    
    sf::CircleShape Draw();
};

struct PlanetLink
{
    Planet planet;
    PlanetLink *next;
};

struct PlanetList
{
    PlanetLink *head = NULL;

    void Push(Planet planet)
    {
        PlanetLink *pl = (PlanetLink*)malloc(sizeof(PlanetLink));
        pl->planet = planet;
        pl->next = head;
        head = pl;
    };
};

class Player
{
public:
    Planet planet;
    float position;
    bool isAlive;
    
    Player(){};
    Player(Planet planet);

    sf::RectangleShape Draw();
};

class Arrow
{
private:
    Player player;
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    
    Arrow(Player player);

    Line Draw();
    void Update(PlanetList planets);
};