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
}

sf::RectangleShape Player::Draw()
{
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
{
    sf::Vertex line[] =
    {
        sf::Vector2f(position - velocity),
        sf::Vector2f(position)
    };
    return Line(line);
}

void Arrow::Update(Planet planets[])
{
    /*
    for(Planet planet: planets)
    {
        //TODO: Physics here
    }
    */
}
