#include "Map.hpp"
#include <iostream>
#include <sstream>
#include "Fonction_generales.hpp"
#include "Case.hpp"
Map::Map()
{
}



bool Map::removeCase (int i, int j)
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    std::string ij = oss.str();

    // si la case n'esite pas deja
    Case* maCase = mapCase[ij];
    if (maCase != NULL )
    {
        // recherhce de l'id de la case
        int i=0;
        while ( listCase[i] != maCase)
            i +=1;


        listCase.erase(listCase.begin()+i);

        deleteElement(listCase,maCase);
        delete maCase;

        mapCase[ij] = NULL;

        return true;
    }

    // rien a a supprimer si ça existe pas
    return false;

}
Case* Map::getCase(int i, int j)
{
    std::ostringstream oss;
    oss << i <<  "_"  << j;
    std::string ij = oss.str();

    // si la case n'esite pas deja
    Case* maCase = mapCase[ij];
    if (maCase != NULL )
    {

        return maCase;
    }

    // rien a a supprimer si ça existe pas
    return NULL;

}
bool Map::addCase(Case* p_case)
{
    std::cout << p_case->getFranchissable() << std::endl;

    // la fleme de l'ecrir deux fois
    std::ostringstream oss;
    oss <<  p_case->getI() <<  "_"  << p_case->getJ();
    std::string ij = oss.str();
    oss.str("");

    // si la case n'esite pas deja
    if (mapCase[ij] == NULL )
    {
        //std::cout << ij  << std::endl;
        // ajout de la case dans la liste
        listCase.push_back(p_case);

        // ajoute de la case dans la map
        mapCase[ij] = p_case;

        // on fait le liens avec les cases existantes
        for (int k = DebutDirection ; k <= FinDirection ; k++)
        {
            // les IJ de la case a ajouter
            int i = p_case->getI();
            int j = p_case->getJ();

            // now IJ sont ceux du voisin dans la direction "k"
            IJvoisin((Direction)k,i,j);

            // si cette case existe
            oss << i <<  "_"  << j;
            std::string ij_voisin = oss.str();
            oss.str("");

            Case * voisin = mapCase[ij_voisin];
            if ( voisin!= NULL)
            {
                // On ajoute cette case comme voisin ( et vis versa )
                p_case->addVoisin((Direction)k,voisin);
            }


        }

        return true;
    }

    // existe deja
    return false;
}
