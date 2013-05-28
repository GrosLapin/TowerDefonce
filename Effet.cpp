#include "Effet.hpp"
#include "Monstre.h"
#include "Constructible.hpp"
#include "Tour.hpp"
#include "Cible.hpp"
// UNIQUE
void EffetUnique::ajouteEffet (Constructible* con)
{ con->ajoutEffetUniquePropre(this);  }
void EffetUnique::ajouteEffet (Monstre* moob)
{ moob->ajoutEffetUniquePropre(this);  }
void EffetUnique::actionAuRetrait (Constructible* con)
{ con->removeEffetUniquePropre(this);  }
void EffetUnique::actionAuRetrait (Monstre* moob)
{ moob->removeEffetUniquePropre(this);  }


// OVER TIME
void EffetOverTime::ajouteEffet (Constructible*  con)
{  con->ajoutEffetOverTimePropre(this);  }
void EffetOverTime::ajouteEffet (Monstre* moob)
{ moob->ajoutEffetOverTimePropre(this);  }
void EffetOverTime::actionAuRetrait (Constructible* con)
{

    con->removeEffetOverTimePropre(this);
}
void EffetOverTime::actionAuRetrait (Monstre* moob)
{  moob->removeEffetOverTimePropre(this);  }











 PerteDePv::PerteDePv(double p_dmgPerSec)
 {
     dmgPerSec = p_dmgPerSec;
 }
bool PerteDePv::appliqueEffet (Constructible * con, double temps) const
{
    con->subirDommage(dmgPerSec*temps);
    return true;
}
bool PerteDePv::appliqueEffet(Monstre * moob, double temps) const
{
    moob->subirDommage(dmgPerSec*temps);
    return true;
}
 ModificateurVitesse::ModificateurVitesse(double p_pourCent)
 {
     if ( p_pourCent < -99 )
     {
         p_pourCent = -99;
     }
     else
         pourCent = p_pourCent;
 }

void ModificateurVitesse::ajouteEffet (Monstre* moob)
{
    EffetUnique::ajouteEffet(moob);
        std::cout << moob->getVitesse()*( 1+pourCent/100) << " = " << moob->getVitesse() << "*" << " ( 1+ "<< pourCent << "/100)" << std::endl;
    moob->setVitesse(moob->getVitesse()*( 1+pourCent/100));
}

void ModificateurVitesse::actionAuRetrait (Monstre* moob)
{
    EffetUnique::actionAuRetrait(moob);
    std::cout << moob->getVitesse()/( 1+pourCent/100) << " = " << moob->getVitesse() << "/" << " ( 1+ "<< pourCent << "/100)" << std::endl;
    moob->setVitesse(moob->getVitesse()/( 1+pourCent/100));
}


 ModificateurVitesseFlat::ModificateurVitesseFlat(double pbonus)
 {
         bonus = pbonus;
 }

void ModificateurVitesseFlat::ajouteEffet (Monstre* moob)
{
    EffetUnique::ajouteEffet(moob);
    if ( moob->getVitesse()+bonus < 0)
    {
         moob->setVitesse(0);
    }
    else
        moob->setVitesse(moob->getVitesse()+bonus);

}

void ModificateurVitesseFlat::actionAuRetrait (Monstre* moob)
{
    EffetUnique::actionAuRetrait(moob);
    moob->setVitesse(moob->getVitesse()-bonus);


}
