#include "Constructible.hpp"
#include "Map.hpp"
#include "SelecteurCible.hpp"
#include "Effet.hpp"
#include "Case.hpp"
#include "Cible.hpp"
 Constructible::Constructible() :Cible()
 {
      prixDeBase = 10;              // en po
      tempsDeConstructionDeBase = 1 ; // en seconde
      pv  = 100;
      armure = 10;
 }

 Constructible::~Constructible()
 {
    // on indique a la case ou on etait, qu'on y est plus
    position->setFranchissable(true);
    position->suppressionConstructible(this);

    // quitte le jeu supprime est effet des aura
    Cible::quitteLeJeu();
    // le destructeur de la mere detruite les aura

 }




 void Constructible::ajoutCibleAuSelecteur  (SelecteurCible* p_selecteur)
{
    p_selecteur->ajoutCible(this);
}
void Constructible::removeCibleAuSelecteur (SelecteurCible* p_selecteur)
{
    p_selecteur->removeCible(this);
}



void  Constructible::arriveEnJeu (Case *p_position)
{
    // on appelle la moman
    Cible::arriveEnJeu(p_position);

    // et on dit qu'on sur un case
    p_position->ajoutConstructible(this);

    // et c'est bloquant
    p_position->setFranchissable(false);


}

void  Constructible::removeEffetPropre (Effet* p_effet)
{
    // on demande a l'effet de se retirer
    p_effet->actionAuRetrait(this);
}
void  Constructible::addEffetPropre (Effet* p_effet)
{
    // on demande a l'effet de se metre dns la bonen ligne
    p_effet->ajouteEffet(this);

}

void Constructible::setTempsDeConstructionDeBase ( const unsigned int p_temps)
{
    tempsDeConstructionDeBase = p_temps;
}
