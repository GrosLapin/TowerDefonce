#ifndef EFFET_H
#define EFFET_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include <set>
#include "MonTimer.hpp"
class Cible;
class Monstre;
class Case;
class Tour;
class Constructible;

// class "interface"
class Effet
{
    public :
        virtual ~Effet() {};
        // doit FORCEMENT finir par cible->removeEffet(this);
        virtual void actionAuRetrait (Constructible* con)=0;
        virtual void actionAuRetrait (Monstre* moob)=0;
        // une sorte de visiteur
        virtual void ajouteEffet (Constructible* con) =0;
        virtual void ajouteEffet (Monstre* moob) =0;

        virtual bool isMalus () const { return malus;};
    protected :
        bool malus;

};

// les effets faisant un + X sur une stat
class EffetUnique : public Effet
{
    public :
        // afin que le bonus soit mis dans la bonne liste dans le constructible
        // cette fonction sert aussi a appliquer les effet d'arrivé doit forcement
        // etre redefini dans un effet unique, et on doit appelet EffetUnique::ajouteEffet
        virtual void ajouteEffet (Constructible* con);
        virtual void ajouteEffet (Monstre* moob);
        virtual void actionAuRetrait (Constructible* con);
        virtual void actionAuRetrait (Monstre* moob);
        virtual ~EffetUnique() {};

};

// les effets ayant une composante de temps, que ça soit du heal over time ou du slow
class EffetOverTime : public Effet
{
    public :
        // permet de metre un bonus en fonction du temps
        virtual bool appliqueEffet (Constructible * con, double temps) const =0;
        virtual bool appliqueEffet (Monstre * moob, double temps) const = 0;
        // la meme chose que pour effetunique, a part qu'on en a moins besoin
        virtual void ajouteEffet (Constructible*  con);
        virtual void ajouteEffet (Monstre* moob);

        virtual void actionAuRetrait (Constructible* con);
        virtual void actionAuRetrait (Monstre* moob);
        virtual ~EffetOverTime() {};
};

// les classe filles : les object concret
class PerteDePv : public EffetOverTime
{
    public :
        PerteDePv(double p_dmgPerSec);
       virtual bool appliqueEffet (Constructible * con, double temps) const ;
        virtual bool appliqueEffet (Monstre * moob, double temps) const ;
        virtual void actionAuDepart (Cible* cible) const {};
        virtual void actionALArrive (Cible* cible) const {};

    private :
         double dmgPerSec;

};
class ModificateurVitesse : public EffetUnique
{
    public :
        ModificateurVitesse(double p_pourCent);
        // permet de metre un bonus
        virtual void ajouteEffet (Constructible* con){};
        virtual void ajouteEffet (Monstre* moob) ;
        virtual void actionAuRetrait (Constructible* con){};
        virtual void actionAuRetrait (Monstre* moob);
    private :
        double pourCent;

};
class ModificateurVitesseFlat : public EffetUnique
{
    public :
        ModificateurVitesseFlat(double pbonus);
        // permet de metre un bonus
        virtual void ajouteEffet (Constructible* con){};
        virtual void ajouteEffet (Monstre* moob) ;
        virtual void actionAuRetrait (Constructible* con){};
        virtual void actionAuRetrait (Monstre* moob);
    private :
        double bonus;

};

#endif EFFET_H
