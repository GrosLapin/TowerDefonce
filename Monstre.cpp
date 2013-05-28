#include "Monstre.h"
#include "Case.hpp"
#include "Effet.hpp"
#include "SelecteurCible.hpp"
#include "DetecteurCible.hpp"
#include "MonTimer.hpp"
#include <assert.h>
#include "PathFinder.hpp"
#include <algorithm>
Monstre:: Monstre(Case *spawn, std::list<Case*> listNexus) : Cible () , Attaquant()
{

    vitesse =0.2 ;
    avancementCase = 499;
    pv = 100;
    casePrecedante = NULL;

    // on met les comportement de base pour les chemins
    pathBerserk = new PathBerserk();
    stackPathFinder.push(new PathFinder());
    berserk = false;
     std::cout <<"0______o";
 calculChemin(spawn,listNexus);
    std::cout <<"0_";
    Attaquant::setDetecteurCible<DetecteurConstructible>();

}
Monstre::~Monstre()
{
    delete timerMove;
}
 std::map<Case*,double >  Monstre::getMapPoid(Case *spawn,  std::list<Case*> listNexus)
 {
     if ( berserk)
        return pathBerserk->getMapPoid(spawn,  listNexus);
    return (stackPathFinder.top())->getMapPoid(spawn,  listNexus);
 }
void Monstre::quitteLeJeu()
{
    // si je meurs je suis plus sur aucune case
    Cible::position->monstrePart(this);
    Cible::quitteLeJeu();

}

void Monstre::calculChemin (Case *spawn,  std::list<Case*> listNexus)
{
    // spwan non null, nexus non vide, et spawn!C nexus
    if ( spawn != NULL && listNexus.size() != 0 )// && listNexus.end() == std::find(listNexus.begin(),listNexus.end(),spawn ))
    {
        cheminASuivre = (* (stackPathFinder.top() ) ) (spawn,listNexus);

        berserk =false;
        if ( (*(stackPathFinder.top()) ).isBerserk() )
        {

            berserk =true;
            // nous sommes pas contant : BERSERK !
            cheminASuivre = (*pathBerserk)(spawn,listNexus);


        }
    }
}



void Monstre::ajoutCibleAuSelecteur  (SelecteurCible* p_selecteur)
{
    p_selecteur->ajoutCible(this);
}
void Monstre::removeCibleAuSelecteur (SelecteurCible* p_selecteur)
{
    p_selecteur->removeCible(this);
}



// la partie entiere donne le nombre de case restante, les decimales l'avancement sur la case.
double Monstre::distanceAParcourir()
{
    // p-e verfier que ça marche bien si y pas de chemin ou pas de case ^^
    return cheminASuivre.size()-1 + avancementCase/1000;
}

void  Monstre::arriveEnJeu (Case *p_position)
{
    // on appelle la moman
    Cible::arriveEnJeu(p_position);
    // on se place
    Attaquant::resolutionCase(p_position);
    // et on dit qu'on sur un case
    p_position->monstreArrive(this);

    timerMove = new MonTimer();
}



void  Monstre::removeEffetPropre (Effet* p_effet)
{
    // on demande a l'effet de se retirer
    p_effet->actionAuRetrait(this);
}

void  Monstre::addEffetPropre (Effet* p_effet)
{
    // on demande a l'effet de se metre dns la bonen ligne
    p_effet->ajouteEffet(this);

}

/*void Monstre::setCheminASuivre (std::list<Case *> &new_chemin)
{
    if ( new_chemin.size() > 0 )
        cheminASuivre = new_chemin;
}*/

Direction Monstre::quelleDirection(int& etape)
{
    Direction dir = Est;
    // si l'avancement est < 500 on va vers le centre
    if ( avancementCase > 500 )
    {
        etape = 0;
        // casePrecedante NE DOIT PAS pouvoir etre null puisqu'on commence sur une case avec un avancement de 500
        assert(casePrecedante!=NULL);
       Cible::position->quelleDirection(casePrecedante,dir);
        dir = directionOppose(dir);
    }
    else // si non on va vers la bordure du voisin
    {
        etape = 1;
        // si c'est la derniere case
        if (cheminASuivre.size() <= 1)
        {
           //  on continue sur 1 ou deux px la ou un va ^^
            Cible::position->quelleDirection(casePrecedante,dir);
            dir = directionOppose(dir);
        }
        else
        {
            Cible::position->quelleDirection( *(++cheminASuivre.begin()),dir);

        }

    }
    return dir;
}



void Monstre::setVitesse (double p_vit)
{
    if ( p_vit >= 0 )
    {
        vitesse = p_vit;
    }
}

double Monstre::getAvancement()
{
    return avancementCase;
}

void Monstre::changementDeCase()
{
    // le fait d'etre appeller par monstre::avance nous assure que nous ne somme pas sur la dernier
    // case du chemein

    // on supprime la distance parcourue en trop
    avancementCase += 1000;

    // On change concrettement de case
    Cible::position->monstrePart(this);
    // on garde en mémoire
    casePrecedante = Cible::position;
    // et on suprime du chemin
    cheminASuivre.erase(cheminASuivre.begin());


    // on change de case au niveau de la cible et on met a jours les effets
    changeCase(this,cheminASuivre.front());

    // et il arrive dans la suivante
    Cible::position->monstreArrive(this);

    // et on decale la partie attaque
    Attaquant::resolutionCase(Cible::position);

}


Cible* Monstre::attaque()
{
    Attaquant::attaque();
// sans doute une erreur de conception
/// TO DO : un monstre attaque, ou bouge mais ne bouge pas en attaquant
    Monstre::avance(timerMove->GetElapsedTime());
    timerMove->restart();
}
double Monstre::avance(double temps)
{
    using namespace std;

    //cout << "j' ai " << listEffetAura.size() << " aura et je subis " << listEffetOverTime.size()<< "EOT et " << listEffetUnique.size() << " EU "<<endl;
     // on applique les effets over time du monstre ( donc de la cible )
    std::list<EffetOverTime*>::iterator it = listEffetOverTime.begin();
    //if ( listEffetOverTime  == NULL )
    //std::cout << listEffetOverTime.size() << std::endl;
    for ( it; it != listEffetOverTime.end() ; ++it )
    {
        (*it)->appliqueEffet(this,temps);
    }


    double distance = (temps * vitesse)*500;


    // on fini quand on est a la moitier
    if (  (avancementCase-distance) < 500 && cheminASuivre.size() <= 1 )
    {
        //avancementCase = 0;
        // si on est pas un berserk... on repose en paix ( pas de repos pour les bourin )
        if ( !berserk)
        {

            quitteLeJeu();
        }
    }
    else
    {
        if ( avancementCase > 0 )
        {
              avancementCase -= distance;
        }
        else
        {
            avancementCase -= distance;
            changementDeCase();
        }
    }

   return distance;
}
