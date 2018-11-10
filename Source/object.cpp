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

#include "object.hpp"

Planet::Planet(float radius, sf::Vector2f position)
{
    this->radius = radius;
    this->position = position;
}

sf::CircleShape Planet::Draw()
{
    sf::CircleShape shape = sf::CircleShape(radius);
    shape.setOrigin(radius/2, radius/2);
    shape.setPosition(position);
    return shape;
}

Player::Player(Planet planet)
{
    this->planet = planet;
    isAlive = true;
}

sf::RectangleShape Player::Draw()
{//FIXME: Set the position relative to the planet, not (0,0)
    sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(80, 40));
    shape.setOrigin(40, 20);
    shape.setRotation(position);
    return shape;
}

Arrow::Arrow(Player player)
{
    this->player = player;
}

Line Arrow::Draw()
{//FIXME: Get the clamped position 1, not the dinamic
    sf::Vertex line[] =
    {
        sf::Vector2f(position - velocity),
        sf::Vector2f(position)
    };
    return Line(line);
}

void Arrow::Update(PlanetList planets)
{//FIXME: Do physics things
//TODO: Get the hitscan here?
    PlanetLink *curr = planets.head;
    while(curr)
    {
        //Do physics here and add to the valocity
    }
    //Clamp velocity?
    position += velocity;
}
