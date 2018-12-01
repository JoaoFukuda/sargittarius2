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

Planet::Planet(int width, int height)
{
    radius = (height/10) + (rand()%(height/8));
    position = sf::Vector2f(
        (width/4)+rand()%(width/2),
        (height/4)+rand()%(height/2)
    );
}

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

bool Arrow::Update(PlanetList planets, PlayerList players)
{
    PlanetLink *currn = planets.head;
    while(currn)
    {
        sf::Vector2f relPos = (currn->planet.position - position);
        float distance = sqrtf(relPos.x*relPos.x + relPos.y*relPos.y);
        float force =
            PI*(currn->planet.radius + 350)*(currn->planet.radius + 350)
            /
            ((distance - currn->planet.radius*7/8)*10000000);

        velocity = velocity + sf::Vector2f(force * (relPos.x / distance), force * (relPos.y / distance));

        if(distance <= currn->planet.radius) return true;
        
        currn = currn->next;
    }

    PlayerLink *curry = players.head;
    while(curry)
    {
        if(curry->player.isAlive)
        {
            float rotation = -curry->player.position*PI*2/360;
            float sine = sin(rotation);
            float coss = cos(rotation);
            sf::Vector2f relPos = position - curry->player.planet.position;
            sf::Vector2f pointTransPos = sf::Vector2f(
                relPos.x*coss - relPos.y*sine,
                relPos.x*sine + relPos.y*coss
            );

            if( pointTransPos.y >= -6 && pointTransPos.y <= 6 &&
                pointTransPos.x <= curry->player.planet.radius + 24 && pointTransPos.x > 0)
            {
                curry->player.isAlive = false;
            }
        }
        curry = curry->next;
    }

    position += velocity;
    return false;
}
