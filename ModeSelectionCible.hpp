#ifndef MODE_SELECTION_CIBLE_HPP
#define MODE_SELECTION_CIBLE_HPP
#include <vector>
#include <set>
#include <iostream>
class Case;
class Cible;
class ModeSelectionCible
{
    public :
        ModeSelectionCible(){};
        virtual ~ ModeSelectionCible(){};

        // je suis pas sur qu'il y a ai un sens a l'operateur ()
        // mais bon ça m'entraine ^^'
        virtual std::vector<Cible *> operator() (std::vector<Cible *> vectCible);
        virtual std::vector<Cible *> operator() (std::vector<Cible *> vectCible,ModeSelectionCible &p_modeSelCible);
        virtual double valeurCible (Cible* p_cible);

    protected :

};

#endif


