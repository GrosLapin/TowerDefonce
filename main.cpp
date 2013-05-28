////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////*
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "MonTimer.hpp"
#include "Constructible.hpp"
#include "Monstre.h"
#include "Tour.hpp"
#include "Fonction_generales.hpp"
#include "Fonction_graphique.hpp"
#include "Effet.hpp"
#include <algorithm>




////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////



int main( int argc, char *argv[])
{
    // parametre de la grille
    int cote = 60;
    int Zoom = 30;
    int offSetX =200,offSetY = 200;

    // on récupere le dossier
    std::string dossier =  getDossier(argv[0]);
    std::ostringstream oss;

    // le timer perso qui supporte l'acceleration
    MonTimer timerVariable;
    sf::Clock timerFix;
    /// est ce du a un probleme de conception ou est ce indispensable ?
    bool modificationTardive = false;

    // creation de la map
    Map carte;
    // spwan
    Case* debut = new Case(0,0,carte);
    // les nexus
    std::list<Case*> listNexus;
    listNexus.push_back(new Case(-5,7,carte));
    listNexus.push_back(new Case(2,3,carte));
    listNexus.push_back(new Case(3,3,carte));

    // si on ne charge pas ces cases avant, elle ne serons pas prioritaire sur les case
    // que loadMap va charger
    carte.addCase(debut);
    std::list<Case *>::iterator itCase = listNexus.begin();
    for ( itCase ; itCase != listNexus.end() ; ++itCase )
    {
        carte.addCase(*itCase);
    }

    // chargement
    loadMap(carte , dossier+"map.map");

     // Create main window
    sf::RenderWindow App(sf::VideoMode(offSetX*2, offSetY*2), "Tower Defonce");

    // creation de la vue
    sf::Vector2f Center(offSetX, offSetY);
    sf::Vector2f HalfSize((offSetX*cote/Zoom)/2,(offSetY*cote/Zoom)/2);
    sf::View View(Center, HalfSize);

    // chargement de la police d'ecriture
    sf::Font MyFont;
    if (!MyFont.loadFromFile(dossier+"arial.ttf"))  std::cerr << "arial not found" << std::endl;
    sf::Text *Text = new sf::Text();
    Text->setFont(MyFont);
    Text->setCharacterSize(20);
    Text->setColor(sf::Color::Red);

    // les indications visuelle : case et porté
    sf::Shape *Polygon          = createHexagone (cote, sf::Color(255, 255, 255,245));
    sf::Shape *PolygonBleu      = createHexagone (cote, sf::Color(0, 0, 255,80));
    sf::Shape *PolygonGris      = createHexagone (cote, sf::Color(0, 0, 0,80));
    sf::Shape *PolygonRose      = createHexagone (cote, sf::Color(150, 0, 0,150));
    sf::Shape *PolyPorteMonstre = createHexagone (cote, sf::Color(0,150, 0,100));

    // chargement de l'image du montre
    sf::Image ImageMoob;
    sf::Texture textureMoob;
    if (!ImageMoob.loadFromFile(dossier+"moob.png"))    std::cerr<< dossier << "moob.tga non trouvé" << std::endl;
    textureMoob.loadFromImage(ImageMoob);
    sf::Sprite spriteMoob(textureMoob);

    // Chargement de l'image de la tour
    sf::Image ImageTower;
    sf::Texture textureTower;
    if (!ImageTower.loadFromFile(dossier+"tower.png"))  std::cerr<< dossier << "moob.tga non trouvé" << std::endl;
    textureTower.loadFromImage(ImageTower);
    textureTower.setSmooth(true);
    sf::Sprite SpriteTower(textureTower);
    SpriteTower.scale(2,2);



    // creation da liste de monstre
    std::vector<Monstre *> mesMoob;

    // creation des tour;
    std::map<Case *,Constructible* > mesConstructions ;
    std::list<Tour*> listTour;

    // on met en gros la map dans l'ecrant ( a la louche )
    View.zoom(5);

    //debug
    std::list<Case *> cheminASuivre;
   int debugSFML = 0;

   std::cout << debut->getFranchissable() <<"debut " << debut->getI() << " " << debut->getJ() << std::endl;

    while (App.isOpen())
    {
        // pour savoir combien de temps c'est écoulé
        timerVariable.restart();
        // gestion de la vue
        gestionTouches (View,timerFix);
        /// DANGER !! Il faudrait reflechier ou restart le timer et ce que ça implique
        timerFix.restart();
        // Clear screen
        App.clear(sf::Color::Black);

        // on met un vue
        App.setView(View);

        // récupération de la position de la souris dans la fenêtre
        sf::Vector2i pixelPos = sf::Mouse::getPosition(App);
        // conversion en coordonnées "monde"


        sf::Vector2f CursorPos = App.mapPixelToCoords(pixelPos);
        //sf::Vector2f CursorPos = App.convertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());


        sf::Vector2<int> caseSelection = mouseToXY(CursorPos.x, CursorPos.y,  cote,  offSetX, offSetX);
        sf::Vector2<int> ijSelection = XYtoIJ( caseSelection,cote,offSetX,offSetY );

        // boucle event
        sf::Event Event;
        bool modification = false;
        while (App.pollEvent(Event))
        {

            // Close window : exit
            if (Event.type == sf::Event::Closed)
            {
                App.close();
               /* std::string fichierMap = dossier+"map.map";
                if ( !saveMap(carte,fichierMap) )
                    std::cerr << fichierMap << " introuvable";*/
            }

             // gestion Click
            if( Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left )
            {

                Case* laCase = carte.getCase(ijSelection.x,ijSelection.y);
                if ( laCase != NULL)
                {
                    Constructible* laConst = mesConstructions[laCase];
                    // on la supprime de la map <case,const>
                    mesConstructions.erase(mesConstructions.find(laCase));

                    // supression de la tour si c'est une tour
                    std::list<Tour*>::iterator itDelTour = std::find(listTour.begin(),listTour.end(),laConst);
                    if ( itDelTour != listTour.end() )
                    {
                        listTour.erase(itDelTour);
                    }
                    delete  laConst;

                    // on demande une mise a jours des chemins des monstre
                    modification =true;
                }
            }
            else if ( Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Right )
            {

                Case* laCase = carte.getCase(ijSelection.x,ijSelection.y);
                if ( laCase != NULL && laCase->getListConstructible().size() == 0 )
                {
//                      std::cout << ijSelection.x << "  "<< ijSelection.y <<std::endl;
                    // creation d'un constructible avec des effets
                    Constructible* constTemps = new Constructible ();
                    constTemps->addEffetAura(new ModificateurVitesse(-1));
                    //constTemps->addEffetAura(new PerteDePv(10));

                    //constTemps->addPorteEffet(CercleImpaire,3);
                    constTemps->addPorteEffet(Etoile,3);
                    constTemps->arriveEnJeu(laCase);
                    // ajoute a la map<>
                    mesConstructions[laCase] = constTemps;
                    modification =true;
                }


            }
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
            {

                // creation d'unmonstre avec un monstre avec une attaque
//                std::cout << debut->getI() << " " << debut->getJ() << "  " << listNexus.size() << std::endl;
                Monstre * MonstreTemps = new Monstre(debut,listNexus);
                //MonstreTemps->addPorteAttaque(Disque,3);
                MonstreTemps->arriveEnJeu(debut);
                // liste monstre
                mesMoob.push_back(MonstreTemps);
            }
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Numpad0))
            {
                // monstre avec un bonus de vitesse en zone
                Monstre * MonstreTemps = new Monstre(debut,listNexus);
                MonstreTemps->addPorteEffet(Disque,1);
                MonstreTemps->addEffetAura(new ModificateurVitesseFlat(1));
                // si on veux jsute sur lui, il faut addEffetPropre
                MonstreTemps->arriveEnJeu(debut);
                mesMoob.push_back(MonstreTemps);
            }
            if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
            {
                Case* laCase = carte.getCase(ijSelection.x,ijSelection.y);
                if ( laCase != NULL && laCase->getListConstructible().size() == 0)
                {
                    Tour* constTemps = new Tour ();
                    // ma tour a aussi des effet
                    constTemps->addPorteEffet(Etoile,2);
                    constTemps->arriveEnJeu(laCase);
                    // mais c'est aussi un tour
                    constTemps->addPorteAttaque(Disque,2);
                    // ajout ou liste
                    mesConstructions[laCase] = constTemps;
                    listTour.push_back(constTemps);
                    modification =true;
                }
            }
        }


        // affichage de la map
        std::vector<Case*> liste = carte.getListCase();
        std::vector<Case*>::iterator it;
        std::map<Case*,double > debug;

        #define DEBUG
        #ifdef DEBUG
        if ( mesMoob.size() > 0 )
        {
            debug = mesMoob[0]->getMapPoid(mesMoob[0]->getPosition(),listNexus);
        }
        #endif
        for ( it= liste.begin() ; it != liste.end() ; ++it )
        {

            // affichage des case
            drawHexagoneIJ ( (*it)->getI() , (*it)->getJ(), *Polygon, cote, offSetX,  offSetY);
            App.draw(*Polygon);

            #ifdef DEBUG
             oss << debug[(*it)];
            Text->setString(oss.str());
            oss.str("");
            drawHexagoneIJ ( (*it)->getI() , (*it)->getJ(), *Text, cote, offSetX,  offSetY);
            App.draw(*Text);
            #endif // DEBUG
        }

        // affichage des points finaux
        itCase = listNexus.begin();
        for ( itCase ; itCase != listNexus.end() ; ++itCase )
        {
             drawHexagoneIJ ( (*itCase)->getI() , (*itCase)->getJ(), *PolygonBleu, cote, offSetX,  offSetY);
             App.draw(*PolygonBleu);
        }

        // on affiche le chemin du 1er moob et sa porté
        std::set<Case *> poMoob ;
        if ( mesMoob.size() > 0 )
        {
            poMoob = mesMoob[0]->getCaseAPorteDAttaque ();
            cheminASuivre = mesMoob[0]->getCheminASuivre();
        }

        for ( itCase= cheminASuivre.begin() ; itCase != cheminASuivre.end() ; ++itCase)
        {
             drawHexagoneIJ ( (*itCase)->getI() , (*itCase)->getJ(), *PolygonBleu, cote, offSetX,  offSetY);
             App.draw(*PolygonBleu);
        }
        for (   std::set<Case *>::iterator itsC = poMoob.begin();
                itsC != poMoob.end();
                ++itsC )
        {
             drawHexagoneIJ ( (*itsC)->getI() , (*itsC)->getJ(), *PolygonRose, cote, offSetX,  offSetY);
             App.draw(*PolygonRose);
        }

        // on affiche les constructible
        std::map<Case *,Constructible* >::iterator itm = mesConstructions.begin();
        //std::cout << "construcitlbe " << mesConstructions.size() << std::endl;
        for ( itm; itm != mesConstructions.end() ; itm++)
        {
            afficheConstructible  (App, SpriteTower,*PolygonRose ,(*itm).second, cote,  offSetX, offSetY );
        }


        for ( int i=0; i<mesMoob.size(); i++ )
        {
            // affichage
            afficheMonstre  (App,spriteMoob,mesMoob[i],cote,  offSetX, offSetY , listTour);
            std::set<Case *> listCasePorte = mesMoob[i]->getCaseAPorteDEffet();
            std::set<Case *>::iterator itSetCase = listCasePorte.begin();
            for ( itSetCase ; itSetCase != listCasePorte.end(); ++itSetCase)
            {
                 drawHexagoneIJ ( (*itSetCase)->getI() , (*itSetCase)->getJ(), *PolyPorteMonstre, cote, offSetX,  offSetY);
                 App.draw(*PolyPorteMonstre);
            }
        }

        // affichage de polygone "souris"
        PolygonRose->setPosition(sf::Vector2f(caseSelection.x,caseSelection.y));
        App.draw(*PolygonRose);


        /// #####################################  Important ##################################
        /// les monstres se servant pour l'instant du timer de l'app si c'est pas a la fin, il se traine ^^'

        // la gestion des tours
        std::list<Tour*>::iterator ittour = listTour.begin();
        Cible *cible = NULL;
        for ( ittour; ittour != listTour.end() ; ittour++)
        {
              cible =(*ittour)->attaque();
        }

        App.display();

        std::vector<int> asupprimer;
        for ( int i=0; i<mesMoob.size(); i++ )
        {
            // calcul du chemin du monstre s'il y a des modif
            if ( modification || modificationTardive)
            {
                mesMoob[i]->calculChemin(mesMoob[i]->getPosition(),listNexus);
            }

            // il bouge
            mesMoob[i]->attaque();

            // on marque ce qu'il faut a supprimer
            if (   mesMoob[i]->getPV() <= 0 )
            {
                asupprimer.push_back (i);
            }
        }
        // on delete
        for ( int j = asupprimer.size()-1 ; j >= 0; j-- )
        {
            delete (mesMoob[asupprimer[j]]);
            mesMoob.erase(mesMoob.begin() + asupprimer[j] );
        }

        modificationTardive = false;
        std::vector<Constructible*> constASuppr;
        std::map<Case*,Constructible*>::iterator itCons;
        for (  itCons = mesConstructions.begin(); itCons != mesConstructions.end()  ; itCons++)
        {
              if ( (*itCons).second->getPV() <= 0 )
              {
                    constASuppr.push_back((*itCons).second);
              }
        }
        // on delete
        for ( int j = constASuppr.size()-1 ; j >= 0; j-- )
        {

            Constructible* tourTemp = constASuppr[j];
                    mesConstructions.erase(mesConstructions.find(tourTemp->getPosition()));
                    std::list<Tour*>::iterator itDelTour = std::find(listTour.begin(),listTour.end(),tourTemp);
                    if ( itDelTour != listTour.end() )
                    {
                        listTour.erase(itDelTour);
                    }
                    delete tourTemp;
                    modificationTardive = true;
        }


    }

    return EXIT_SUCCESS;
}

