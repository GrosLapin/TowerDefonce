#include "Fonction_graphique.hpp"
#include "MonTimer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "Tour.hpp"

/**
Affiche le monstre la ou il doit etre sur la case, avec le bon angle et la bonne position
affiche également les points de vie du moob
*/
void afficheMonstre        (sf::RenderWindow &App, sf::Sprite  &SpriteMoob ,Monstre* monMoob,int cote, int offSetX, int offSetY ,  std::list<Tour*> &listTour)
{
   using namespace std;

    Case* caseMoob = monMoob->CaseCourante();

    drawHexagoneIJ ( caseMoob->getI() , caseMoob->getJ(), SpriteMoob, cote, offSetX,  offSetY);
    //sf::Shape pv   = sf::RectangleShape (0,0, 0+monMoob->getPV()/2 ,0,5,sf::Color::Black);

    sf::RectangleShape pv (sf::Vector2f(5,monMoob->getPV()/2));
    pv.setFillColor(sf::Color::Black);
    /// Moche

    drawHexagoneIJ ( caseMoob->getI() , caseMoob->getJ(), pv, cote, offSetX,  offSetY);
    // on centre le moob

    int etape;
    Direction dtion = monMoob->quelleDirection(etape);
    // on bouge en fonction de la direction
    double moobOffSetX=0,moobOffSetY=0,moobAvancement;
    if ( etape == 0)
    {
        moobAvancement = ((1000-monMoob->getAvancement())/1000)*cote*(sqrt(3));
    }
    else
    {
        moobAvancement = ((500-monMoob->getAvancement())/1000)*cote*(sqrt(3));
    }

    double angle = 0;
    switch (dtion)
    {
        case Est  : {
            moobOffSetX = moobAvancement;
            moobOffSetY =0;
            angle = -90;
            if ( etape == 0)
            {
                moobOffSetX -= (sqrt(3)/2) *cote;

            }

            break;}
        case NordEst : {
            moobOffSetX = moobAvancement / 2 ;
            moobOffSetY = -moobAvancement * (sqrt(3)/2) ;

            if ( etape == 0)
            {
                moobOffSetX -= (sqrt(3)/2) *cote /2;
                moobOffSetY += (sqrt(3)/2) *cote *(sqrt(3)/2);

            }
            angle = -30;
            break;}
        case NordOuest : {
            moobOffSetX = -moobAvancement / 2 ;
            moobOffSetY = -moobAvancement * (sqrt(3)/2) ;
            if ( etape == 0)
            {
                moobOffSetX += (sqrt(3)/2) *cote /2;
                moobOffSetY += (sqrt(3)/2) *cote *(sqrt(3)/2);

            }
            angle = 30;
            break;}
        case Ouest : {
            moobOffSetX = - moobAvancement;
            moobOffSetY = 0;
            if ( etape == 0)
            {
                moobOffSetX += (sqrt(3)/2) *cote;


            }
            angle = 90;
            break;}
        case SudOuest : {
             angle = 160;
            moobOffSetX = -moobAvancement / 2 ;
            moobOffSetY = moobAvancement * (sqrt(3)/2) ;
             if ( etape == 0)
            {
                moobOffSetX += (sqrt(3)/2) *cote /2;
                moobOffSetY -= (sqrt(3)/2) *cote *(sqrt(3)/2);

            }

            break;}
        case SudEst: {
             angle = -160;
             moobOffSetX = moobAvancement / 2 ;
            moobOffSetY = moobAvancement * (sqrt(3)/2) ;
              if ( etape == 0)
            {
                moobOffSetX -= (sqrt(3)/2) *cote /2;
                moobOffSetY -= (sqrt(3)/2) *cote *(sqrt(3)/2);

            }

            break;}
    }

    SpriteMoob.move(moobOffSetX,moobOffSetY);
   //double centreX = SpriteMoob.getSize().x/2;

   // double centreY = SpriteMoob.getSize().y/2 ;


    double centreX = SpriteMoob.getTextureRect().width /2  ;//  SpriteTower.getTexture().getSize().x/2;
    double centreY = SpriteMoob.getTextureRect().height/2 ;
    SpriteMoob.setPosition(centreX,centreY);
    SpriteMoob.rotate(angle);

    pv.  move(moobOffSetX-centreX,moobOffSetY-centreY);
    App.draw(pv);
    App.draw(SpriteMoob);

    //la gestion de l'attaque n'est pas encore definie
    if ( monMoob != NULL )
    {

        using namespace std;

        Case* laCase = monMoob->CaseCourante();

        if (laCase != NULL )
        {


            std::list<Tour*>::iterator itt = listTour.begin();

            for ( itt; itt != listTour.end() ; ++itt)
            {
                if ( (*itt)->getCible() == monMoob)
                {

                    sf::Vector2<int> ij;
                    sf::Vector2<double>xy;
                    ij.x = (*itt)->getPosition()->getI();
                    ij.y = (*itt)->getPosition()->getJ();
                    xy = IJtoXY (ij, cote, offSetX,  offSetY);
                   // sf::Shape Line   = sf::Shape::Line(SpriteMoob.GetPosition().x,SpriteMoob.GetPosition().y,xy.x,xy.y, 2, sf::Color::Red);
                   // App.Draw(Line);

                }
            }
        }
    }

}

void afficheConstructible  (sf::RenderWindow &App, sf::Sprite &SpriteTower ,sf::Shape &PolygonPorte,Constructible* maCons,int cote, int offSetX, int offSetY )
{
    // affichage du sprite de la construction
    int i = maCons->getPosition()->getI();
    int j = maCons->getPosition()->getJ();


    drawHexagoneIJ ( i,j, SpriteTower, cote, offSetX,  offSetY);
    //SpriteTower.SetCenter(SpriteTower.GetSize().x/2,SpriteTower.GetSize().y/2);

    sf::Vector2f positionAvant = SpriteTower.getPosition();
    SpriteTower.setPosition(positionAvant.x-SpriteTower.getTextureRect().height,positionAvant.y-SpriteTower.getTextureRect().width);
    App.draw(SpriteTower);


    // affichage de la porté
    std::set<Case *> cibles = maCons->getCaseAPorteDEffet();
    std::set<Case *>::iterator its;
    for ( its= cibles.begin() ; its != cibles.end() ; ++its )
    {
        drawHexagoneIJ ( (*its)->getI() , (*its)->getJ(), PolygonPorte, cote, offSetX,  offSetY);
         App.draw(PolygonPorte);
    }
    // les point de vue ( mon dieu c'est moche le code graphique )
    double centreX = SpriteTower.getTextureRect().width /2  ;//  SpriteTower.getTexture().getSize().x/2;
    double centreY = SpriteTower.getTextureRect().height/2 ;
    /*sf::Shape pv   = sf::Shape::Line (0,0, 0+maCons->getPV()/2 ,0,5,sf::Color::Black);
    drawHexagoneIJ (  i,j, pv, cote, offSetX,  offSetY);
    pv.Move(0-centreX,0-centreY);
    App.draw(pv);*/

}

void gestionTouches (sf::View &View, sf::Clock &timer)
{
    float Offset =  timer.getElapsedTime().asMilliseconds();

    // le deplacement de la map
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )      View.move( 0,      -Offset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )    View.move( 0,       Offset);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )    View.move(-Offset,  0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )   View.move(Offset,   0);

    // le zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) )         View.zoom(1.005f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) )    View.zoom(0.995f);

    // la gestion du "temps"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )    MonTimer::getSpeed() * 1.07;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )    MonTimer::getSpeed() / 1.07;

    // clean
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) )     std::cout <<std::endl <<std::endl<<std::endl<<std::endl;

}

sf::ConvexShape* createHexagone (int cote, sf::Color couleur)
{
        sf::ConvexShape* hexagone = new sf::ConvexShape(6);
        double sqrt3 = sqrt(3.0);
    	sf::Color point =  sf::Color::White;
		sf::Color bordure = sf::Color::Black;


        hexagone->setPoint(0,sf::Vector2f (0             , cote));
        hexagone->setPoint(1,sf::Vector2f (cote*sqrt3/2  , cote/2));
        hexagone->setPoint(2,sf::Vector2f (cote*sqrt3/2  , -cote/2));
        hexagone->setPoint(3,sf::Vector2f (0             , -cote));
        hexagone->setPoint(4,sf::Vector2f (-cote*sqrt3/2 , -cote/2));
        hexagone->setPoint(5,sf::Vector2f (-cote*sqrt3/2 , cote/2));

        hexagone->setOutlineThickness(3);
        hexagone->setFillColor(couleur);
        hexagone->setOutlineColor(sf::Color::Black);

        return hexagone;
}

sf::Vector2<int> mouseToXY(int mouseX, int mouseY, int cote, int offSetX, int offSetY)
{
    sf::Vector2<int> vect2;
    cote++;
    double sqrt3 = sqrt(3);

    // le coté en haut a gauche : f(x) = -x/sqrt(3)  - 1
    double penteDroite =  -1/sqrt3;
    // le coté en haut a droite : g(x) =  x/sqrt(3)  - 1
    double penteGauche = -penteDroite;

    double i,j;
    j = ceil((mouseY - penteDroite*(mouseX-offSetX) -offSetY)/cote);
    i = ceil((mouseY - penteGauche*(mouseX-offSetX) -offSetY )/cote);
    double mouseOnJBas = j*cote ;
    double mouseOnJHaut= i*cote ;



    double hauteur = (mouseOnJHaut - mouseOnJBas);


    double X1 , Y1, X2,Y2;
    X1  =(double)offSetX;
    Y1 =       (double)mouseOnJBas+(double)offSetY;
    X2 =   X1 - hauteur*sqrt3/2.0;
    Y2 =   Y1 + hauteur/2.0;

    // ajustement en fonction du cas dans lequel on est
    // f%3 ==0 on est deja bien placé
    if ( ((int)i+(int)j) % 3 == 2 || ((int)i+(int)j) % 3 == -1)
    {
        Y2 += -cote;
    }
    else if ( ((int)i+(int)j) % 3 == 1 || ((int)i+(int)j) % 3 == -2 )
    {

        double iBis = ceil((mouseX-offSetX) /(cote*sqrt3/2.0));
        int iBisMod3 = (int)iBis%3;
        int iMod3 = (int)i%3;
        // gestion des cas negatifs
        if ( iMod3%3 < 0 )   iMod3 += 3;
        if ( iBisMod3%3 < 0) iBisMod3+= 3;
        int mod3plus1 = (iBisMod3+1)%3;
        int mod3plus2 = (iBisMod3+2)%3;

        if ( iMod3 ==  mod3plus1)
        {
            // on est sur le "triangle" a droite
            X2 += (cote*sqrt3/2.0);
            Y2 -= cote/2.0;
        }
        else if ( iMod3 == mod3plus2 )
        {
            X2 -= (cote*sqrt3/2.0);
            Y2 -= cote/2.0;
        }
    }



    vect2.x = X2;
    vect2.y = Y2;
    return vect2;
}


sf::Vector2<double> IJtoXY (sf::Vector2<int> IJ ,int cote, int offSetX, int offSetY)
{
    double sqrt3 = sqrt(3.0);
    double x = offSetX;
    double y = offSetY;
    cote++;

    x += cote*sqrt3*IJ.x + IJ.y*(sqrt3/2)*cote;
    y += (double)IJ.y*1.5*(double)cote;


    sf::Vector2<double> vec;
    vec.x =x;
    vec.y =y;
    return vec;
}


sf::Vector2<int> XYtoIJ (sf::Vector2<int> XY ,int cote, int offSetX, int offSetY)
{
    double sqrt3 = sqrt(3);
    cote++;
    double x = XY.x;
    double y = XY.y;
    x -= offSetX;
    y -= offSetY;

    double j =  round (y/(cote*1.5));
    // le coté en haut a droite : g(x) =  x/sqrt(3)  - 1


    double i = round (x / (cote*sqrt3/2));

        i-= j;
        i/=2;

    sf::Vector2<int> vec;

    /// DANGER : depuis SFML 2 j'ai du changer X et Y est ce juste un bug mineur ou est ce que ça cache autre chose
    vec.y =(int) round(i);
    vec.x =(int) round(j);
    return vec;

}


