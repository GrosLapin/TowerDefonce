#include "Case.hpp"
#include "Tour.hpp"
#include "Monstre.h"
#include "Constructible.hpp"
#include "MonTimer.hpp"
#include "Effet.hpp"
#include <iostream>

void Case::ajoutConstructible (Constructible* p_tour)
{
     listeConstructible.insert(p_tour);
}

void Case::suppressionConstructible(Constructible* p_tour)
{
     listeConstructible.erase(p_tour);
}

Case::Case(int p_i, int p_j,Map &p_carte) : voisin ({NULL,NULL,NULL,NULL,NULL,NULL}), carte(p_carte)
{
    i = p_i;
    j = p_j;
    franchissable = true;
}

void Case::ajoutEffect    (Effet * p_Effect)
{

    // 1) on ajoute cette effet a notre liste d'effet
    listEffets.push_back(p_Effect);

    // 2) on ajoute cette effet comme effect "subie" au gens sur la case
    std::set<Monstre* >::iterator itMonstre;
    std::set<Constructible* >::iterator itConstr;

    // et on demande a tout les cible d'ajouter l'effet
    for ( itMonstre = listeMonstre.begin(); itMonstre != listeMonstre.end(); ++itMonstre )
    {
        (*itMonstre)->addEffetPropre(p_Effect);
    }
    for ( itConstr = listeConstructible.begin(); itConstr != listeConstructible.end(); ++itConstr )
    {
        (*itConstr)->addEffetPropre(p_Effect);
    }

}
void  Case::removeEffect   (Effet * p_Effect)
{

    std::set<Monstre* >::iterator itMonstre;
    std::set<Constructible* >::iterator itConstr;

    // et on demande a tout les cible de supprimer l'effet
    for ( itMonstre = listeMonstre.begin(); itMonstre != listeMonstre.end(); ++itMonstre )
    {
      //   std::cout << " suppression d'un effet de la tours sur un monstre" << std::endl;
        (*itMonstre)->removeEffetPropre(p_Effect);
    }
     for ( itConstr = listeConstructible.begin(); itConstr != listeConstructible.end(); ++itConstr )
    {
      //  std::cout << " suppression d'un effet de la tours sur une tour" << std::endl;
        (*itConstr)->removeEffetPropre(p_Effect);
    }
    // et on supprime réellement l'effet
    listEffets.remove(p_Effect);

}
std::string Case::toString()
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
   return oss.str();
}
void Case::monstreArrive(Monstre* moob)
{
    listeMonstre.insert(moob);
}
void Case::monstrePart  (Monstre* moob)
{
    listeMonstre.erase(moob);
}

bool Case::quelleDirection(Case* p_voisin,Direction &out_dir)
{
    bool pasTrouve = true;
    int dir = DebutDirection;
    while (pasTrouve && dir <=FinDirection )
    {
        if ( voisin[dir] == p_voisin)
        {
            pasTrouve= false;
        }
        else
        {
            dir+=1;
        }
    }
    out_dir = (Direction)dir;
    return !pasTrouve;
}
Case::~Case()
{

    for (int k = DebutDirection ; k <= FinDirection ; k++)
    {
        if (voisin[k] != NULL)
        {

           voisin[k]->voisin[directionOppose((Direction)k)] = NULL;
        }
    }
}
Case* Case::getVoisin(Direction direction)
{

    return voisin[direction];
}

void Case::addVoisin(Direction direction, Case* p_voisin)
{
    // on ne peut ajouter un voisin que la case est "libre"
    if ( voisin[direction] == NULL)
    {
        // on ajoute le voisin
        voisin[direction] = p_voisin;
        // et on dit au voisin de nous ajouter
        p_voisin->addVoisin(directionOppose(direction),this);
        // on evite la boucle infine avec le if == NULL

        //std::cout << "(" << i << "," << j << ") a pour voisin ("<<p_voisin->i<< "," << p_voisin->j << ")" << std::endl;
    }
}

void Case::removeVoisin(Direction direction)
{
    // si on a un voisin dans cette direction
    Case *unVoisin = voisin[direction];
    if ( unVoisin != NULL)
    {
        // On supprime notre liens ave clui
        voisin[direction] = NULL;
        // et on dit au voisin de nous supprimer
        unVoisin-> voisin[directionOppose(direction)] = NULL;

    }
}
