#ifndef FONCTION_HPP
#define FONCTION_HPP
#include <SFML/Graphics.hpp>
#include "Enum.hpp"
#include "Map.hpp"
#include "Fonction_generales.hpp"
#include <list>
#include <cmath>
class Tour;
class Cible;

//void drawHexagone (sf::Shape &Polygon ,int cote,sf::Color couleur);
sf::ConvexShape* createHexagone (int cote, sf::Color couleur);

template <class T>
void drawHexagoneIJ (const int j,const int i, T &Polygon,int cote,int offSetX, int offSetY)
{
    double sqrt3 = sqrt(3.0);
    double x = offSetX;
    double y = offSetY;
    cote++;

    x += cote*sqrt3*i + j*(sqrt3/2)*cote;
    y += (double)j*1.5*(double)cote;


    Polygon.setPosition(sf::Vector2f(x,y));
}




sf::Vector2<int> mouseToXY(int mouseX, int mouseY, int cote, int offSetX, int offSetY);
sf::Vector2<int> XYtoIJ (sf::Vector2<int> XY ,int cote, int offSetX, int offSetY);
sf::Vector2<double> IJtoXY (sf::Vector2<int> IJ ,int cote, int offSetX, int offSetY);
void cadrillage (sf::RenderWindow &App,int cote, int offSetX, int offSetY );
void afficheMonstre   (sf::RenderWindow &App, sf::Sprite  &SpriteMoob ,Monstre* monMoob,int cote, int offSetX, int offSetY ,  std::list<Tour*> &listTour);
void gestionTouches (sf::View &View,sf::Clock &timer);
bool plusDeVie(Cible*);

void afficheConstructible  (sf::RenderWindow &App, sf::Sprite &SpriteTower ,sf::Shape &PolygonPorte,Constructible* maCons,int cote, int offSetX, int offSetY );


#endif
