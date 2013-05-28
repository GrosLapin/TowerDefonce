#include "Tour.hpp"
#include "Case.hpp"
Tour::Tour() : Constructible(), Attaquant()
{
}

Tour::~Tour()
{
    //ici aussi on fait confiance au parent
}

void Tour::arriveEnJeu (Case *p_position)
{
    Constructible::arriveEnJeu(p_position);
    Attaquant::resolutionCase(p_position);

}

