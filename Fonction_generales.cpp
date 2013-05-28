#include "Fonction_generales.hpp"
#include <fstream>
#include <vector>
#include <map>
#include "Cible.hpp"

bool plusDeVie(Cible* p)
{
    return p->getPV() == 0;
}

std::vector<sf::Vector2<int> > casesCibles(Case* centre, unsigned int range, TypeDePorte porte)
{
    std::vector<sf::Vector2<int> > listCase;
    sf::Vector2<int> caseXY;

    // si le centre est null
    if ( centre == NULL )
    {
        return listCase;
    }
    //std::cout << "debut" << std::endl;
    switch (porte)
    {
        case Disque :
        {
            // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            // les cercles concentriques
            for (int i = 1; i <= range ; i++ )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(centre, i );
                std::vector<sf::Vector2<int> >::iterator it = cercle.begin();
                // on ajoute le cercle au disque

                int tailleCercle = cercle.size();
                for (it; it != cercle.end() ; ++it )
                {

                    caseXY.x = it->x;
                    caseXY.y = it->y;
                    listCase.push_back(caseXY);
                    //listCase.push_back(cercle[i]);
                }
            }
            break;
        }
        case Etoile :
        {
             // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            for (int i = 1; i <= range ; i++ )
            {
                // les 6 points principaux
                sf::Vector2<int> XYest ;
                XYest.x = caseXY.x + i;
                XYest.y = caseXY.y;
                sf::Vector2<int> XYouest ;
                XYouest.x = caseXY.x - i;
                XYouest.y = caseXY.y;

                sf::Vector2<int> XYsud_ouest ;
                XYsud_ouest.x = caseXY.x - i;
                XYsud_ouest.y = caseXY.y + i ;
                sf::Vector2<int> XYnord_ouest ;
                XYnord_ouest.x = caseXY.x ;
                XYnord_ouest.y = caseXY.y - i ;

                sf::Vector2<int> XYnord_est ;
                XYnord_est.x = caseXY.x + i;
                XYnord_est.y = caseXY.y - i;
                sf::Vector2<int> XYsud_est ;
                XYsud_est.x = caseXY.x;
                XYsud_est.y = caseXY.y + i;


                listCase.push_back(XYest);
                listCase.push_back(XYnord_est);
                listCase.push_back(XYnord_ouest);
                listCase.push_back(XYouest);
                listCase.push_back(XYsud_ouest);
                listCase.push_back(XYsud_est);
            }
            break;
        }
        case LigneO_E :
        {
             // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            for (int i = 1; i <= range ; i++ )
            {
                // les 6 points principaux
                sf::Vector2<int> XYest ;
                XYest.x = caseXY.x + i;
                XYest.y = caseXY.y;
                sf::Vector2<int> XYouest ;
                XYouest.x = caseXY.x - i;
                XYouest.y = caseXY.y;

                listCase.push_back(XYest);
                listCase.push_back(XYouest);

            }
            break;
        }
        case LigneSO_NE:
        {
             // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            for (int i = 1; i <= range ; i++ )
            {
                // les 6 points principaux

                sf::Vector2<int> XYsud_ouest ;
                XYsud_ouest.x = caseXY.x - i;
                XYsud_ouest.y = caseXY.y + i ;

                sf::Vector2<int> XYnord_est ;
                XYnord_est.x = caseXY.x + i;
                XYnord_est.y = caseXY.y - i;
                sf::Vector2<int> XYsud_est ;

                listCase.push_back(XYnord_est);

                listCase.push_back(XYsud_ouest);
            }
            break;
        }
        case LigneSE_NO :
        {
             // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            for (int i = 1; i <= range ; i++ )
            {

                sf::Vector2<int> XYnord_ouest ;
                XYnord_ouest.x = caseXY.x ;
                XYnord_ouest.y = caseXY.y - i ;

                sf::Vector2<int> XYsud_est ;
                XYsud_est.x = caseXY.x;
                XYsud_est.y = caseXY.y + i;



                listCase.push_back(XYnord_ouest);

                listCase.push_back(XYsud_est);
            }

            break;
        }
        case CerclePaire :
        {
            // 0 = le centre 2 / 4 ...
            // il faut le centre
            caseXY.x = centre->getI();
            caseXY.y = centre->getJ();
            listCase.push_back(caseXY);

            // les cercles concentriques
            for (int i = 2; i <= range ; i += 2 )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(centre, i );
                std::vector<sf::Vector2<int> >::iterator it = cercle.begin();
                // on ajoute le cercle au disque

                int tailleCercle = cercle.size();
                for (it; it != cercle.end() ; ++it )
                {

                    caseXY.x = it->x;
                    caseXY.y = it->y;
                    listCase.push_back(caseXY);
                    //listCase.push_back(cercle[i]);
                }
            }
            break;
        }
        case CercleImpaire :
        {
            // il y a pas le centre : 1/3/5/7
             // les cercles concentriques
            for (int i = 1; i <= range ; i += 2 )
            {
                std::vector<sf::Vector2<int> > cercle = calculCercle(centre, i );
                std::vector<sf::Vector2<int> >::iterator it = cercle.begin();
                // on ajoute le cercle au disque
               // std::cout << " rayon : "<< i <<" soit "<< cercle.size() << " cases"<<std::endl;
                int tailleCercle = cercle.size();
                for (it; it != cercle.end() ; ++it )
                {
                   // std::cout << "\t"<< caseXY.x <<"  "<< caseXY.y<<std::endl;
                    caseXY.x = it->x;
                    caseXY.y = it->y;
                    listCase.push_back(caseXY);
                    //listCase.push_back(cercle[i]);
                }
            }
            break;
        }
    }

}


std::vector<sf::Vector2<int> > casesCibles( unsigned int range, TypeDePorte porte)
{
    Map carte;

    Case c(0,0,carte);
    return  casesCibles(&c,  range,  porte);

}

std::vector<sf::Vector2<int> > calculCercle(Case* centre, unsigned int range)
{
    // initilisation
     std::vector<sf::Vector2<int> > caseCote;
    sf::Vector2<int> XYcentre;
    if ( centre == NULL || range < 1)
        return caseCote;
    XYcentre.x = centre->getI();
    XYcentre.y = centre->getJ();

    // les 6 points principaux
    sf::Vector2<int> XYest ;
    XYest.x = XYcentre.x + range;
    XYest.y = XYcentre.y;
    sf::Vector2<int> XYouest ;
    XYouest.x = XYcentre.x - range;
    XYouest.y = XYcentre.y;

    sf::Vector2<int> XYsud_ouest ;
    XYsud_ouest.x = XYcentre.x - range;
    XYsud_ouest.y = XYcentre.y + range ;
    sf::Vector2<int> XYnord_ouest ;
    XYnord_ouest.x = XYcentre.x ;
    XYnord_ouest.y = XYcentre.y - range ;

    sf::Vector2<int> XYnord_est ;
    XYnord_est.x = XYcentre.x + range;
    XYnord_est.y = XYcentre.y - range;
    sf::Vector2<int> XYsud_est ;
    XYsud_est.x = XYcentre.x;
    XYsud_est.y = XYcentre.y + range;


    // avec un range de 1 il y pas de "cote" avec un range de 2 le coté vaut 1.. avec 3 _> 2 ext
    for ( int i = 1 ; i <= range-1 ; i++)
    {
        sf::Vector2<int> cote;

        // est vers NE
        cote.x = XYest.x;
        cote.y = XYest.y - i;
        caseCote.push_back(cote);
        // NE vers NO
        cote.x = XYnord_est.x - i;
        cote.y = XYnord_est.y ;
        caseCote.push_back(cote);

        //  NO vers O
        cote.x = XYnord_ouest.x - i;
        cote.y = XYnord_ouest.y + i;
        caseCote.push_back(cote);
        //  O vers SO
        cote.x = XYouest.x;
        cote.y = XYouest.y + i;
        caseCote.push_back(cote);
        //  sO vers SE
        cote.x = XYsud_ouest.x+i;
        cote.y = XYsud_ouest.y;
        caseCote.push_back(cote);

         //  sE vers E
        cote.x = XYsud_est.x+i;
        cote.y = XYsud_est.y -i;
        caseCote.push_back(cote);
    }

    // on ajoute les coins
     caseCote.push_back(XYest);
     caseCote.push_back(XYnord_est);
     caseCote.push_back(XYnord_ouest);
     caseCote.push_back(XYouest);
     caseCote.push_back(XYsud_ouest);
     caseCote.push_back(XYsud_est);

     return caseCote;

/*
     std::vector<std::string> stringCase;
     std::vector<sf::Vector2<int> >::iterator it;
     std::ostringstream oss;
     for ( it = caseCote.begin(); it != caseCote.end() ; ++it)
     {
        oss << it->x <<  "_"  << it->y;
        stringCase.push_back(oss.str());
        oss.str("");
     }*/
}

std::vector<Case *> caseInRange (Case* start, int range)
{
     // calcul des case a porté ( sans doute optimisable
    std::map<int, std::vector<Case *> > caseParDistance;
    caseParDistance[0].push_back(start);

    for ( int i =0 ; i < range ; ++i )
    {
        std::vector<Case *>::iterator it = caseParDistance[i].begin();

        for ( it ; it!=caseParDistance[i].end() ; ++it )
        {
            // pour chaque voisin
            for (int k = DebutDirection ; k <= FinDirection ; k++)
            {
                Case* voisin = (*it)->getVoisin((Direction)k) ;
                if ( voisin != NULL)
                {
                    caseParDistance[i+1].push_back(voisin);
                }
            }
        }
    }

    return caseParDistance[range];

}




std::string getDossier(std::string cheminExe)
{
    int possition = cheminExe.find_last_of("/\\");
    return  cheminExe.substr(0,possition) +"/";
}

bool loadMap(Map &terrain, std::string p_fichier)
{

    std::ifstream fichier(p_fichier.c_str(), std::ios::in);  // on ouvre en lecture
    if(fichier)  // si l'ouverture a fonctionné
    {
        std::string line;  // déclaration d'une chaîne qui contiendra la ligne lue
        while(getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            std::istringstream iss;
            iss.str(line);
            std::string i, j;
            iss >> i >> j ;

            terrain.addCase(new Case(std::atoi(i.c_str()),
                                     std::atoi(j.c_str()),
                                     terrain));

        }
        fichier.close();
    }

    return false;

}

bool saveMap(Map &terrain, std::string p_fichier)
{

    std::ofstream fichier(p_fichier.c_str(),  std::ios::out |  std::ios::trunc );  //déclaration du flux et ouverture du fichier
    if(fichier)  // si l'ouverture a réussi
    {
        std::vector<Case*> list = terrain.getListCase();
        std::vector<Case*>::iterator it;
        for ( it= list.begin() ; it != list.end() ; ++it )
        {
            fichier << (*it)->getI() << " " << (*it)->getJ() <<std::endl;

        }
        fichier.close();  // on referme le fichier
        return true;
    }

    return false;

}
