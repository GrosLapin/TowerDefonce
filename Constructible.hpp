#ifndef COMSTRUCTIBLE_H
#define COMSTRUCTIBLE_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include "Enum.hpp"
#include "Cible.hpp"

/*
                            Constructible

                        /\                    |
                        |                     |
                        |                     |
                    Tour                     "mur" et "flag"
                |           |
                |           |
                "tour"     "piege"                                  */
class Case;
class Effet;
class Constructible : public Cible
{
    public :
        Constructible();
        virtual ~Constructible();

        // geteurs
        virtual unsigned int getTempsDeConstructionDeBase() const   { return tempsDeConstructionDeBase;};

        // seteur
        virtual void setTempsDeConstructionDeBase ( const unsigned int p_temps);

        virtual void arriveEnJeu (Case *p_position);
        virtual void removeEffetPropre (Effet* p_effet);
        virtual void addEffetPropre (Effet* p_effet);

        virtual void ajoutCibleAuSelecteur  (SelecteurCible* p_selecteur);
        virtual void removeCibleAuSelecteur (SelecteurCible* p_selecteur);

         virtual void QuiEstLa () { std::cout << "Constructible" << std::endl;};

    protected :

        unsigned int tempsDeConstructionDeBase;


};

#endif COMSTRUCTIBLE_H
