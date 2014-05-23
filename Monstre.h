#ifndef MONSTRE_H
#define MONSTRE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <stack>
#include "Cible.hpp"
#include "Attaquant.hpp"
class Constructible;
class PathFinder;
class Tour;
class Case ;

// test modif
class Monstre : public Cible, public Attaquant
{
    public:
        Monstre(Case *spawn,  std::list<Case*> listNexus);
        virtual ~Monstre();

        virtual double distanceAParcourir();
        // la partie entiere donne le nombre de case restante, les decimales l'avancement sur la case.
        virtual Direction quelleDirection(int& etape);
        virtual void calculChemin (Case *spawn,  std::list<Case*> listNexus);
        //getteur
        virtual double getAvancement();
        virtual Case* CaseCourante() { return Cible::getPosition();};
        virtual double getVitesse () const { return vitesse;};
        // setteur
        //virtual void setCheminASuivre (std::list<Case *> &new_chemin);
        virtual void setVitesse (double p_vit);

        // les visiteur de la cible
        virtual void removeEffetPropre (Effet* p_effet);
        virtual void addEffetPropre (Effet* p_effet);

        // les visiteurs des attaquants
        virtual void ajoutCibleAuSelecteur  (SelecteurCible* p_selecteur);
        virtual void removeCibleAuSelecteur (SelecteurCible* p_selecteur);

        // surcharge de l'arrivé en jeu pour le monstre. Servira egalement pour la
        // fonction de résolution de case des attaquants
        virtual void arriveEnJeu (Case *p_position);
        virtual void quitteLeJeu ();

        // le monstre quand il attaque, ba il avance aussi :o c'est fou ca
        virtual Cible* attaque();

        //debug
        virtual std::list<Case *> getCheminASuivre() { return cheminASuivre;};
        std::map<Case*,double > getMapPoid(Case *spawn,  std::list<Case*> listNexus);

         virtual void QuiEstLa () { std::cout << "Monstre" << std::endl;};
    protected:
        // pour l'instant un seul appel...
        void changementDeCase();
        double avance(double temps);

        // tout ce dont il a besoin pour se déplacer
        double vitesse;
        double avancementCase;
        Case* casePrecedante;

        // pour savoir s'il est en train d'attaque ou s'il a fini son chemin
        bool berserk;

        // le chemin qu'il suit
        std::list<Case *> cheminASuivre;
        // et ce qu'il faut pour le calculer
        PathFinder *pathBerserk;
        std::stack<PathFinder*> stackPathFinder;

        // j'ai besoin de savoir quand j'ai avancer pour la dernier fois
        MonTimer* timerMove;




};

#endif // MONSTRE_H
