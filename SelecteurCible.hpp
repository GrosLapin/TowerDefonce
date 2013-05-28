#ifndef SELECTION_CIBLE_HPP
#define SELECTION_CIBLE_HPP
#include <vector>
#include <list>
class Case;
class Monstre;
class Cible;
class Constructible;

class SelecteurCible
{
    public :
        SelecteurCible(){};
        virtual ~ SelecteurCible(){};

        // la fonction principal
        virtual Cible* operator() (std::vector<Cible *> listCible);

        // la fonction pour la résolution de type
        virtual void ajoutCible(Cible* p_cible);
        virtual void removeCible(Cible* p_cible);
        // les fonctions appeller par la cible une fois la résolution faites
        virtual void ajoutCible(Monstre* p_monstre);
        virtual void removeCible(Monstre* p_monstre);
        virtual void ajoutCible(Constructible* p_const);
        virtual void removeCible(Constructible* p_const);
    protected :

        // ces deux liste ne servent uniquement si on a besoin de garder un ordre
        // d'arriver. un selecteurCible peut tres bien ne pas s'en servir.
        std::list<Constructible *> listConstructible;
        std::list<Monstre *> listMonstre;

};

#endif
