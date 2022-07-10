#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <math.h>       
#define PI 3.14159265


////////////////////////////////////////////////////////////

sf::ContextSettings options;
int width = 1700;
int height = 1050;
int fps = 30;

int taille = 20;
int nb_step = 0;
int degre;
float cote = taille*3 / (2*sqrt(3));
int amplitude = 12;
float vitesse = 0.4;
bool mur;
int row;
int col;
const int zone_prox = 10*taille;
const int zone_align = 5*taille;
const int zone_collision = taille*3;
const int marge = 50;

const int config[2] = {8,8}; //row , col
const int nb_serf = config[0]*config[1];
sf::VertexArray list_serf[nb_serf];
std::vector<float> long_pas;
std::vector<float> pas;
std::vector<float> centre;

sf::RenderWindow window;
sf::RectangleShape carre;

////////////////////////////////////////////////////////////

sf::Text text;
sf::Text t_autre;
sf::Text console;
sf::Font font;
void LoadFont();
void SetText(sf::Text& txt, sf::String str);



// class Serf {
//     public:

// };

