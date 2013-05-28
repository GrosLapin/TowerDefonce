#ifndef ATTAQUANT_H
#define ATTAQUANT_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include <set>
#include "MonTimer.hpp"
#include "Enum.hpp"
class DetecteurCible;
class ModeSelectionCible;
class SelecteurCible;
class Cible;
class Case;
class AttaqueZone;
class Attaquant
{
    public :
        // le minimume vital
        virtual ~Attaquant();
        Attaquant();
        virtual Cible* attaque();

        // la liste des case a porté dans un terrain "plein"
        virtual void addPorteAttaque(TypeDePorte tdp, unsigned int porte);
        // pour que ça soit des case réels et pas jsute de ij
        virtual void resolutionCase(Case* p_position);  // parce qu'on garde la carte en mémoir
        virtual void resolutionCase();                  // ça sert uniquement quand on change la Po ( je crois )

        // les assesseurs
        virtual double getAS () const {return AS;};
        virtual double getDmg () const {return dmg;};

        // les seteurs
        virtual void setAs  ( double p_as);
        virtual void setDmg ( double p_dmg);
        template <class T>
        // TODO : Pourquoic'est pas en normal et la création de l'obet n'est pas a l'exterieur de la classe ?
        void setDetecteurCible ()
        {
            detecteur = new T (caseAPorteDAttaque);
        };
        virtual void setModeSelectionCible  ( ModeSelectionCible * p_modeSelection);
        virtual void setSelecteurCible      ( SelecteurCible *p_selecteurCible);
        virtual void setAttaqueZone         (AttaqueZone *p_attaqueZone);

        /// a mediter aussi
        virtual Cible* getCible() {return cible;};

        // debug ( ou du moins affichage )
        virtual  std::set<Case *> getCaseAPorteDAttaque () { return caseAPorteDAttaque;};
    protected :
        /// a reflechir
        Cible* cible;


        // les classiques
        double AS;
        double dmg;

        // qui dit AS qui timer
         MonTimer timer;

        // la "vision" de l'attaquant
        DetecteurCible *detecteur;
        // la gestion des priorité ( taper sur la cible qui a le moins de point de vie par exemple )
        ModeSelectionCible * modeSelection;
        // en cas d'absence de "mode de selection de cible" ou simplement en cas d'egalité
        // il est bon de pouvoir choisir la cible de manier unique.
        // par exemple, 1er arrivé 1er focus, ou le plus avancer,
        SelecteurCible *selecteurCible;
        // si on tape en zone, savoir comment on le fait
        AttaqueZone *attaqueZone;

        // gestion de la porté
        std::set<Case *> caseAPorteDAttaque;

        // pour l'affichage ET la construction de la porté
        std::vector<TypeDePorte> listTypeDePorte;               // ne sert que si on doit pouvoir "deconstruire"
        std::vector<unsigned int> listPorte;                    // ne sert que si on doit pouvoir "deconstruire"
        std::vector<sf::Vector2<int> > listCaseCandidates;

        // on garde la cate en mémoir
        Case* position;


};


#endif
