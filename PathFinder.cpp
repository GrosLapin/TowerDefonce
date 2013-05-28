#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#include "PathFinder.hpp"
#include "Case.hpp"
#include <limits>

//#################################    MOMAN ######################################
// le comportement de base pour les fonctions redefinissable
double PathFinder::caseFanchissable (Case* p_case)
{
    if (! p_case->getFranchissable())
    {
        std::cout << "nest pas :" << p_case->getI() << " " << p_case->getJ()  << std::endl;
    }
    return p_case->getFranchissable();
}
double PathFinder::poidCase         (Case* p_case)
{
    return 1;
}

 std::map<Case*,double > PathFinder::getMapPoid(Case *spawn,  std::list<Case*> listNexus)
 {
      // on a besoin d'avoir le poid de chaque case
    std::map<Case*,double > mapPoid;

    // et la liste des cases qui nous ont amener a la case
    std::map<Case*, std::list<Case* > > mapPrecedent;
    // on veux la liste des case a visiter
    std::queue<Case*> caseAVisiter;

    // la premiere case qu'on visite le debut
    caseAVisiter.push(spawn);
    mapPoid[spawn] = 1;

    // tant que la queue est pas vide
    while ( !caseAVisiter.empty())
    {
        // on prend la 1er case
        Case* first = caseAVisiter.front();

        // et on le supprime de la liste
        caseAVisiter.pop();

        // on regarde tous ces voisins
        for (int k = DebutDirection ; k <= FinDirection ; k++)
        {
            // si le voisin est non null
            Case* voisin = first->getVoisin((Direction)k) ;
            // si le voisin est pas null, on regarde s'il est franchissable sauf si on est des fou !!
            if ( voisin != NULL && caseFanchissable(voisin) )
            {
                // si le voisin nous est inconue :
                if ( mapPoid[voisin] == 0 &&  voisin!=spawn)
                {
                    // on lui donne un poid
                    mapPoid[voisin] = mapPoid[first]+poidCase(voisin);
                    // et on lui donne la liste de son voisin
                    mapPrecedent[voisin] =  mapPrecedent[first];
                    // et on ajoute le voisin :)
                    mapPrecedent[voisin].push_back(first);

                     // et on ajoute cette case a visiter, afin de mettre a jours ces voisins s'il le faut
                    caseAVisiter.push(voisin);
                }
                // Ne sert pas pour des distances fixes
                else // si on le connais deja
                {
                    // et que le score qu'on avait etait pas bon
                    if ( mapPoid[voisin] > mapPoid[first]+1 )
                    {
                        std::cout<< "WOOOOOOOOOOOOOOT pathfinder operator()" << std::endl;

                        // on lui donne un poid
                        mapPoid[voisin] = mapPoid[first]+1;
                        // et on lui donne la liste de son voisin
                        mapPrecedent[voisin] =  mapPrecedent[first];
                        // et on ajoute le voisin :)
                        mapPrecedent[voisin].push_back(first);
                        // et on ajoute cette case a visiter, afin de mettre a jours ces voisins s'il le faut
                        caseAVisiter.push(voisin);
                    }

                }
            }
        }
    }
//    std::cout << mapPoid.size() << std::endl;
    return mapPoid;
 }
// les fonctions qui ne sont pas "virtuel"
 std::list<Case *> PathFinder::operator() (Case *spawn,  std::list<Case*> listNexus)
 {
    // pas d'appriorie, ca va marcher
    berserk = false;

    // on a besoin d'avoir le poid de chaque case
    std::map<Case*,double > mapPoid;

    // et la liste des cases qui nous ont amener a la case
    std::map<Case*, std::list<Case* > > mapPrecedent;
    // on veux la liste des case a visiter
    std::queue<Case*> caseAVisiter;

    // la premiere case qu'on visite le debut ( si on peut >< )
    if ( caseFanchissable (spawn) )
    caseAVisiter.push(spawn);
    mapPoid[spawn] = 1;

    // tant que la queue est pas vide
    while ( !caseAVisiter.empty())
    {
        // on prend la 1er case
        Case* first = caseAVisiter.front();

        // et on le supprime de la liste
        caseAVisiter.pop();

        // on regarde tous ces voisins
        for (int k = DebutDirection ; k <= FinDirection ; k++)
        {
            // si le voisin est non null
            Case* voisin = first->getVoisin((Direction)k) ;
            // si le voisin est pas null, on regarde s'il est franchissable sauf si on est des fou !!
            if ( voisin != NULL && caseFanchissable(voisin) )
            {
                // si le voisin nous est inconue :
                if ( mapPoid[voisin] == 0)
                {
                    // on lui donne un poid
                    mapPoid[voisin] = mapPoid[first]+poidCase(voisin);
                    // et on lui donne la liste de son voisin
//                    std::cout << first->getI() << "," << first->getJ() << std::endl;
                    mapPrecedent[voisin] =  mapPrecedent[first];
                    // et on ajoute le voisin :)
                    mapPrecedent[voisin].push_back(first);

                     // et on ajoute cette case a visiter, afin de mettre a jours ces voisins s'il le faut
                    caseAVisiter.push(voisin);
                }
                // Ne sert pas pour des distances fixes
                else // si on le connais deja
                {
                    // et que le score qu'on avait etait pas bon
                    if ( mapPoid[voisin] > mapPoid[first]+1 )
                    {
                        std::cout<< "WOOOOOOOOOOOOOOT pathfinder operator()" << std::endl;

                        // on lui donne un poid
                        mapPoid[voisin] = mapPoid[first]+1;
                        // et on lui donne la liste de son voisin
                        mapPrecedent[voisin] =  mapPrecedent[first];
                        // et on ajoute le voisin :)
                        mapPrecedent[voisin].push_back(first);
                        // et on ajoute cette case a visiter, afin de mettre a jours ces voisins s'il le faut
                        caseAVisiter.push(voisin);
                    }

                }
            }
        }
    }



    // on cherche le nexus le plus proche
    Case* CaseMin = NULL;

    std::list<Case*>::iterator it = listNexus.begin();
    /*bool nexusEqSpawn = listNexus.end() != std::find(listNexus.begin(),listNexus.end(),spawn );
    if ( mapPoid[(*it)]  == 0 )
    {
        if ( !( nexusEqSpawn && caseFanchissable(spawn)) )
            mapPoid[(*it)] = std::numeric_limits<double>::max();
    }*/
    for ( it; it != listNexus.end() ; ++it)
    {
        // si l'un des nexus n'est pas accessible on berserkise
        if ( mapPoid[(*it)] == 0 )
        {
            berserk = true;
        }
        else
        {
            if ( CaseMin == NULL )
            {
                CaseMin= *it;
            }
            // on recherche le nexus ayant le plus petit coup

            if ( mapPoid[(*it)] < mapPoid[CaseMin])
            {
                CaseMin = (*it);
            }
        }

    }

    // si tout est null on a juste besoin de retourné qqch
    if (  CaseMin == NULL)
        CaseMin =listNexus.front();

    // juste une petite verification ^^'
    if( CaseMin == spawn && !caseFanchissable(CaseMin))
    {
        berserk = true;
    }
    // si y a un chemin, on ajoute la dernier case
    if ( mapPoid[CaseMin]  != 0 )
         mapPrecedent[CaseMin].push_back(CaseMin);

    std::cout << "taille " << mapPrecedent[CaseMin].size() << std::endl;
    return mapPrecedent[CaseMin];
 }

//################################## BERSERK   #####################################

std::list<Case *> PathBerserk::operator() (Case *spawn,  std::list<Case*> listNexus)
{

    std::list<Case *> list = PathFinder::operator()(spawn,listNexus);
    std::list<Case *>::iterator it = std::find_if(list.begin(),list.end(),notFranchissable );

//     std::cout << "it " << *it << "   it end " << *(list.end()) << "   it debut " << *(list.begin())<< std::endl;
    std::list<Case *>::iterator it2 = list.begin();
    int i = 1;
    std::cout << std::endl ;
 //   std::cout << "avant " << std::endl ;
  /*  for ( it2 ; it2 != list.end() ; ++it2 )
    {
        std::cout << i << ":" << (*it2)->toString() << "  (" << (*it2)->getFranchissable() << std::endl ;
    }*/
    if ( it != list.end())
        ++it;
    list.erase(it,list.end());
//    std::cout << " apres "<< std::endl ;
    i = 1;
    it2 = list.begin();
    for ( it2 ; it2 != list.end() ; ++it2 )
    {
//         std::cout << i << ":" << (*it2)->toString() << "  (" << (*it2)->getFranchissable() << std::endl ;
    }
    return list;
}

bool notFranchissable(Case * p_case)
{
    return !p_case->getFranchissable();
}
