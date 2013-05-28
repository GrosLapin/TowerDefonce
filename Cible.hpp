#ifndef CIBLE
#define CIBLE
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>  // un peu domage d'inclure tout ça pour un vecteur2
#include <map>
#include <list>
#include <queue>
#include <set>
#include "Enum.hpp"
class Case;
class Effet;
class EffetOverTime;
class EffetUnique;
class SelecteurCible;
class Cible
{
    public :
        Cible();
        virtual ~Cible();

        // geteurs
        virtual Case* getPosition() const            { return position;  };
        virtual double getPV() const                 { return pv;        };
        virtual double getArmure() const             { return armure;    };
        virtual std::set<Case *> getCaseAPorteDEffet () const { return caseAPorteDEffet ;};

        // seteur
        virtual void setPV(const double p_pv);
        virtual bool subirDommage(double dommage);
        virtual void setArmure (const double p_armure );
        virtual void setPrixDeBase ( const unsigned int p_gold);
        virtual bool isVisible () const { return visible ;};
        virtual bool isVolant () const { return volante ;};

        //// fonction
        virtual void addPorteEffet(TypeDePorte tdp, unsigned int porte);
        virtual void arriveEnJeu (Case *p_position);
        virtual void quitteLeJeu ();
        friend void changeCase (Cible* cible,Case* nouvelleCase);

        // la fonction generique que l'on appel de l'exterieur
        virtual void addEffetPropre     (Effet* p_effet) = 0 ;
        virtual void removeEffetPropre  (Effet* p_effet) = 0 ;
        // la meme chose pour le "selecteurCible"
        // TODO : QU'est ce que ça fout la ?
        virtual void ajoutCibleAuSelecteur  (SelecteurCible* p_selecteur) = 0;
        virtual void removeCibleAuSelecteur (SelecteurCible* p_selecteur) = 0;

        // les fonction qui sont appelle par le "visiteur d'effet
        virtual void ajoutEffetOverTimePropre      (EffetOverTime * p_effet );
        virtual void ajoutEffetUniquePropre        (EffetUnique * p_effet );
        virtual void removeEffetOverTimePropre     (EffetOverTime * p_effet );
        virtual void removeEffetUniquePropre       (EffetUnique * p_effet );

        // ajoute des effet a difuser
        virtual void addEffetAura       (Effet* p_effet) ;
        virtual void removeEffetAura    (Effet* p_effet) ;

        // debug
        virtual void QuiEstLa () { std::cout << "cible" << std::endl;};

    protected :

        // je suis pas sur que ça soit utile dans "cible" mais apres tout pourquoi pas
        bool volante;
        bool visible;

        // localisation
        Case* position;

        // gestion de la porté
        std::set<Case *> caseAPorteDEffet;

        // pour l'affichage ET la construction de la porté
        std::vector<TypeDePorte> listTypeDePorte;               // ne sert que si on doit pouvoir "deconstruire"
        std::vector<unsigned int> listPorte;                    // ne sert que si on doit pouvoir "deconstruire"
        std::vector<sf::Vector2<int> > listCaseCandidates;

        // prix
        unsigned int prixDeBase;

        // defence
        double pv;
        double pvAlaCreation;
        double armure;

        // liste d'effect sur la cible
        std::list<EffetOverTime*> listEffetOverTime;
        std::list<EffetUnique*>   listEffetUnique;

        // liste des effet que la cible difuse
        std::vector<Effet*> listEffetAura;

        // fonction privé
        void MAJcaseAPorte();




};
#endif
