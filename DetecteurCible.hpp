#ifndef DETETEUR_CIBLE_HPP
#define DETETEUR_CIBLE_HPP
#include <vector>
#include <set>
#include <iostream>
class Case;
class Cible;
class DetecteurCible
{
    public :
        /// c'est bien un passage par réferance !!
        DetecteurCible(std::set<Case *> &p_CaseCible):  caseCible (p_CaseCible){}
        virtual ~ DetecteurCible(){};

        // je suis pas sur qu'il y a ai un sens a l'operateur ()
        // mais bon ça m'entraine ^^'
        virtual std::vector<Cible *> operator() ();
        virtual std::set<Cible *> cibleDansCase(Case* p_case);
        virtual bool cibleCiblable (Cible* p_cible);

    protected :
       std::set<Case *> &caseCible;
};


class DetecteurConstructible : public DetecteurCible
{
    public :
        DetecteurConstructible(std::set<Case *> &p_CaseCible):  DetecteurCible (p_CaseCible){}
        virtual std::set<Cible *> cibleDansCase(Case* p_case);
};
#endif

