#include "AttaqueZone.hpp"
#include "Case.hpp"
#include "Cible.hpp"

// fonction qui sert prendre DES cibles dans le range autour de la cible
std::vector<Cible *> AttaqueZone::operator() (Cible* cible)
{
    // par defaut ça prend la cible x)
    std::vector<Cible *> retour;
    if ( cible != NULL )
    {
        retour.push_back(cible);
    }

    return retour;
}
