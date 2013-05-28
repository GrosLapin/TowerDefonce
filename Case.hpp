#ifndef CASE_HPP
#define CASE_HPP
#include <cstddef>
#include "Enum.hpp"
#include <vector>
#include <list>
#include <set>
#include <sstream>
class Tour;
class Constructible ;
class Monstre;
class Map;
class Effet;
class Case
{
    public :
        Case(int p_i, int p_j,Map &p_carte);
         ~ Case();

        int getI () { return i;};
        int getJ () { return j;};
        std::string toString();

        // pour la navigation dans la map
        bool quelleDirection(Case* p_voisin,Direction &out_dir);
        Case* getVoisin(Direction direction);

        // pour l'editeur de map
        void addVoisin(Direction direction, Case* p_voisin);

        // les assesseurs sur les booléen
        bool getFranchissable   ()          { return franchissable;};
        void setFranchissable   (bool boule){ franchissable = boule;};
        bool getOccupe          ()          { return occupe;};
        void setOccupe          (bool boule){ occupe = boule;};
        Map& getMap             ()          { return carte;};

        // la gestion de la liste de monstre
        void monstreArrive  (Monstre* moob);
        void monstrePart    (Monstre* moob);
        std::set<Monstre* > getListMonstre() { return listeMonstre;};

        // la gestion des tours a portée
        void ajoutConstructible      (Constructible* p_tour);
        void suppressionConstructible(Constructible* p_tour);
        std::set<Constructible* >    getListConstructible()    { return listeConstructible;};


        // gestion de Effect
        void ajoutEffect    (Effet * p_Effect);
        void removeEffect   (Effet * p_Effect);
        std::list<Effet* > getListEffets() const { return listEffets;};
        template <class T> void ajoutEffect    (std::vector<T> &p_listEffect)
        {
            // ajoute de tout les effect dans la liste
            typename std::vector<T>::iterator it = p_listEffect.begin();

            for ( it ; it != p_listEffect.end() ; ++it )
            {
                ajoutEffect((*it));
            }
        };
        template <class T> void removeEffect   (std::vector<T> &p_listEffect)
        {
            // on supprime la liste des effet qu'on nous demande de supprimer

            typename std::vector<T>::iterator it = p_listEffect.begin();
            for ( it ; it != p_listEffect.end() ; ++it )
            {
                removeEffect((*it));
            }
        };

        // pour le debug
        int nbCible () { return listeMonstre.size() + listeConstructible.size(); };

    private :

        // une case sait a quelle map elle appartient
        Map &carte;

        // la definition meme d'un case
        int i,j;
        Case* voisin[6];

        // utile pour les sort de zone ( si si )
        std::set<Monstre* > listeMonstre;
        // liste de tours
         std::set<Constructible* >   listeConstructible;

         // la lsite des effect sur la case
         std::list<Effet* > listEffets;

        bool franchissable;
        bool occupe;

        void removeVoisin(Direction direction);
};

#endif

