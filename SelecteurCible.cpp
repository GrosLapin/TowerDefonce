#include "Case.hpp"
#include "SelecteurCible.hpp"
#include "Monstre.h"
#include "Constructible.hpp"
#include "Cible.hpp"

// les fonctions generiques
void SelecteurCible::ajoutCible(Cible* p_cible)
{
    p_cible->ajoutCibleAuSelecteur(this);
}
void SelecteurCible::removeCible(Cible* p_cible)
{
    p_cible->removeCibleAuSelecteur(this);
}

// les appel une fois la résolution de type faite
void SelecteurCible::ajoutCible(Monstre* p_monstre)
{
    listMonstre.push_back(p_monstre);
}
void SelecteurCible::removeCible(Monstre* p_monstre)
{
    listMonstre.remove(p_monstre);
}
void SelecteurCible::ajoutCible(Constructible* p_const)
{
    listConstructible.push_back(p_const);
}
void SelecteurCible::removeCible(Constructible* p_const)
{
    listConstructible.remove(p_const);
}

// c'est moche hien... si tu veux mieu... faut payer x)
Cible* SelecteurCible::operator() (std::vector<Cible *> listCible)
{
    if ( listCible.size() > 0 )
    {
        return listCible[0];
    }
    else
        return NULL;
}
