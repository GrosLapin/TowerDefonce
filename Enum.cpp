#include "Enum.hpp"

Direction directionOppose (const Direction &p_dir)
{
    switch (p_dir)
    {
        case Est         : return Ouest;
        case SudEst      : return NordOuest;
        case NordEst     : return SudOuest;
        case Ouest       : return Est;
        case NordOuest   : return SudEst;
        case SudOuest    : return NordEst;
        default : return p_dir;
    }
}

// donne les coordonée de la case a coté de ij dans la direction p_dir
// i j en entré sortie
void IJvoisin (const Direction &p_dir, int& i, int& j)
{
  switch (p_dir)
    {
        case Est         :
        {
            i+=1;
            break;
        }
        case SudEst      :
        {
            j+=1;
            break;
        }
        case NordEst     :
        {
            i+=1;
            j -=1;
            break;
        }
        case Ouest       :
        {
            i -=1 ;
            break;
        }
        case NordOuest   :
        {
            j -=1;
            break;
        }
        case SudOuest    :
        {

            i -=1;
            j +=1;
            break;
        }
    }

}
