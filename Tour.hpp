#ifndef TOUR_H
#define TOUR_H
#include "Constructible.hpp"
#include "Attaquant.hpp"
class Case;
class Tour : public Constructible, public Attaquant
{
    public :
        Tour();
        virtual ~Tour();
        virtual void arriveEnJeu (Case *p_position);

    protected :


};

#endif TOUR_H
