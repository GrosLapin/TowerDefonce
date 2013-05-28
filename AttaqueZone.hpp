#ifndef AttaqueZone_HPP
#define AttaqueZone_HPP
#include <vector>
#include <set>
#include <iostream>
class Case;
class Cible;
class AttaqueZone
{
    public :
        AttaqueZone(int p_range = -1): range(p_range){}
        virtual ~ AttaqueZone(){};
        virtual std::vector<Cible *> operator() (Cible* cible);


    protected :
       int range;
};

#endif


