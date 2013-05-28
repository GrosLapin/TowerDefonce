#include "DetecteurCible.hpp"
#include "Case.hpp"
#include "Cible.hpp"
#include "Monstre.h"
#include "Constructible.hpp"

// ###################################################  MERE  ###################################################################
std::vector<Cible *> DetecteurCible::operator() ()
{
    // la version de base se contente de retourne la liste des monstres sur les cases s'ils sont visible et non volant
    std::vector<Cible *> monstreAPorte;
    std::set<Case *>::iterator it = caseCible.begin();
    // pour toutes les cases a porte
    for ( it ; it != caseCible.end(); ++it )
    {
        // on recupere les monstre dans les cases
        std::set<Cible* > listCible = cibleDansCase((*it));
        // on ajoute les monstre que l'on peut cibler
        std::set<Cible* >::iterator itMoob = listCible.begin() ;
        for ( itMoob ; itMoob != listCible.end() ; ++itMoob)
        {
            if ( cibleCiblable(*itMoob) )
            {
                monstreAPorte.push_back((*itMoob));
            }
        }
    }


    return monstreAPorte;
}
bool DetecteurCible::cibleCiblable (Cible* p_cible)
{
    return p_cible->isVisible() && !p_cible->isVolant();
}
std::set<Cible *> DetecteurCible::cibleDansCase(Case* p_case)
{
    std::set<Cible *> setC;
    std::set<Monstre *> setM = p_case->getListMonstre();
    for (   std::set<Monstre *>::iterator it = setM.begin();
            it != setM.end();
            ++it)
    {

        setC.insert(*it);
    }
    return setC ;
}


// ################################################### DetecteurConstructible ###########################################################
std::set<Cible *> DetecteurConstructible::cibleDansCase(Case* p_case)
{
    std::set<Cible *> setC;
    std::set<Constructible *> setM = p_case->getListConstructible();
    for (   std::set<Constructible *>::iterator it = setM.begin();
            it != setM.end();
            ++it)
    {
        // BUG !!!
        setC.insert((*it));
    }

    return setC ;
}
