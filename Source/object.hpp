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

#include <math.h>
#define PI 3.14

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
    float maxRadius;
    Planet(){};
    Planet(int width, int height);
    Planet(float radius, sf::Vector2f position);

    void setRadius(int n);
    
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
    Planet *planet;
    float position;
    bool isAlive;
    int hp = 4;
    
    Player(){};
    Player(Planet *planet);

    sf::RectangleShape Draw();
};

//PLAYER COULD USE A CONSTANT LIST (ARRAY)
struct PlayerLink
{
    Player player;
    PlayerLink *next;
};

struct PlayerList
{
    PlayerLink *head = NULL;

    void Push(Player player)
    {
        PlayerLink *pl = (PlayerLink*)malloc(sizeof(PlayerLink));
        pl->player = player;
        pl->next = head;
        head = pl;
    };
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
    bool Update(PlanetList planets, PlayerList players);
};

//TODO: Lista estática 
struct ArrowLink
{
    Arrow arrow;
    ArrowLink *next;
};

struct ArrowList
{
    ArrowLink *head = NULL;

    void Push(Arrow arrow)
    {
        ArrowLink *pl = (ArrowLink*)malloc(sizeof(ArrowLink));
        pl->arrow = arrow;
        pl->next = head;
        head = pl;
    };
};
