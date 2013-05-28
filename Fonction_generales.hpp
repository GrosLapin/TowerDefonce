#ifndef FONCTION_GENERAL_HPP
#define FONCTION_GENERAL_HPP
#include "Enum.hpp"
#include <string>
#include <vector>
#include <map>
#include "Case.hpp"
#include "Monstre.h"
#include "Map.hpp"
#include "Tour.hpp"
class Tour;
class Map;
class Case;
class Monstre;
bool saveMap(Map &terrain, std::string p_fichier);
bool loadMap(Map &terrain, std::string p_fichier);
std::string getDossier(std::string cheminExe);
void MortMonstre (Monstre* moob, std::map<Case *,Tour* > &p_pointeurListMonstre);
std::vector<Case *> caseInRange (Case* start, int range);
std::vector<sf::Vector2<int> > calculCercle(Case* centre,unsigned int range);
std::vector<sf::Vector2<int> > casesCibles(Case* centre, unsigned int range, TypeDePorte porte);
std::vector<sf::Vector2<int> > casesCibles( unsigned int range, TypeDePorte porte);
// ne sert a rien x)
template <typename T> void deleteElement(std::vector<T > &list, const T &element)
{
     int i=0;
     while ( list[i] != element)
            i +=1;
    list.erase(list.begin() + i);
}







#endif
