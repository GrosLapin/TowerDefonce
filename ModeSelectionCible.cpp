#include "ModeSelectionCible.hpp"
#include "Case.hpp"
#include "Cible.hpp"

std::vector<Cible *> ModeSelectionCible::operator() (std::vector<Cible *> vectCible)
{
    return this->operator()(vectCible,*this);
}
std::vector<Cible *> ModeSelectionCible::operator()(std::vector<Cible *> vectCible,ModeSelectionCible &p_modeSelCible)
{
    // le multyset est une solution sous optimal de feignant :)
    double max = 0; // on dit que valeur cible c'est positif
    std::vector<Cible *> listFinale;

    // on parcourt la liste
    std::vector<Cible *>::iterator it = vectCible.begin();
    for ( it ; it != vectCible.end() ; ++it )
    {
        // 3 cas
        double temps = p_modeSelCible.valeurCible(*it);
        if ( temps > max )
        {
            // bingo, on vire ce qu'on avait avant et on recommence x)
            listFinale.clear();
            max = temps;
            listFinale.push_back(*it);
        }
        else if ( temps == max )
        {
            listFinale.push_back(*it);
        }
        // else on fait rien x)
    }
    return listFinale;
}
double ModeSelectionCible::valeurCible (Cible* p_cible)
{
    return 1.0;
}
