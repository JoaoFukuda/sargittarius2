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

#ifndef IOSTREAM
#include <iostream>
#endif

#include "object.hpp"

Planet::Planet(float radius, sf::Vector2f position)
{
    this->radius = radius;
    this->position = position;
}

sf::CircleShape Planet::Draw()
{
    sf::CircleShape shape = sf::CircleShape(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    return shape;
}

Player::Player(Planet planet)
{
    this->planet = planet;
    isAlive = true;
}

sf::RectangleShape Player::Draw()
{
    sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(24, 12));
    shape.setOrigin(12, 6);
    shape.setRotation(position);
    sf::Vector2f posOffset = sf::Vector2f(cos(position*PI*2/360), sin(position*PI*2/360)) * (planet.radius + 10);
    shape.setPosition(planet.position + posOffset);
    return shape;
}

Arrow::Arrow(Player player)
{
    this->player = player;
}

Line Arrow::Draw()
{
    float distance = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    sf::Vector2f tail = sf::Vector2f(
        velocity.x * 23 / distance,
        velocity.y * 23 / distance
    );
    sf::Vertex line[] =
    {
        position - tail,
        sf::Vector2f(position)
    };
    return Line(line);
}

bool Arrow::Update(PlanetList planets)
{
    PlanetLink *curr = planets.head;
    bool collision = false;
    while(curr)
    {
        sf::Vector2f relPos = (curr->planet.position - position);
        float distance = sqrtf(relPos.x*relPos.x + relPos.y*relPos.y);
        float force =
            PI*(curr->planet.radius + 350)*(curr->planet.radius + 350)
            /
            ((distance - curr->planet.radius*7/8)*15000000);

        velocity = velocity + sf::Vector2f(force * (relPos.x / distance), force * (relPos.y / distance));

        if(distance <= curr->planet.radius) collision = true;
        
        curr = curr->next;
    }
    position += velocity;
    return collision;
}
