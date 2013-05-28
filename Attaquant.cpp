#include "Attaquant.hpp"
#include "DetecteurCible.hpp"
#include "Cible.hpp"
#include "Case.hpp"
#include "ModeSelectionCible.hpp"
#include "SelecteurCible.hpp"
#include "Map.hpp"
#include "Fonction_generales.hpp"
#include "AttaqueZone.hpp"

Attaquant::Attaquant()
{
    // les classes mere implémente le comportement par defaut ( normalement )
    detecteur = new DetecteurCible(caseAPorteDAttaque);
    modeSelection = new ModeSelectionCible();
    selecteurCible = new SelecteurCible();
    attaqueZone = new AttaqueZone();

    // les choses qui doivent etre a null...
    position=NULL;
    cible = NULL;

    // avoir des valeurs par defaut
    AS = 1;
    dmg =100;
}

Attaquant::~Attaquant()
{
    delete modeSelection;
    delete selecteurCible;
    delete detecteur;
    delete attaqueZone;
}

void Attaquant::addPorteAttaque(TypeDePorte tdp, unsigned int porte)
{
    // on garde en memoir
    listPorte.push_back(porte);
    listTypeDePorte.push_back(tdp);
    std::vector<sf::Vector2<int> > newCandidats =  casesCibles( porte, tdp);
    std::vector<sf::Vector2<int> >::iterator it = newCandidats.begin();
    // on ajotue les cases a porté a la lsite des cases cibles
    for ( it ; it != newCandidats.end() ; ++it )
    {
        listCaseCandidates.push_back((*it));
    }

    // si il est deja en jeu, il est de bon gout de le mettre a jorus
    if ( position != NULL )
    {
        resolutionCase(position);
    }
}

void Attaquant::resolutionCase(Case* p_position)
{
    if ( p_position != NULL )
    {
        position = p_position;
        resolutionCase();
    }
}

void Attaquant::resolutionCase()
{
    if ( position != NULL )
    {
        // on vide les case a porté d'attaque
        caseAPorteDAttaque.clear();
        // on parcout les cases candidate
        std::vector<sf::Vector2<int> >::iterator it = listCaseCandidates.begin();
        for ( it ; it!=listCaseCandidates.end() ; ++it )
        {
            // les case candidates sont centrée en (0,0) il faut ajoute la possision du centre pour avoir les cases a porté
            Case* caseAAjouter = position->getMap().getCase(it->x+position->getI(), it->y+position->getJ() );
            if ( caseAAjouter != NULL)
            {
                // la case existe on l'ajoute a la liste des case a porté
                caseAPorteDAttaque.insert(caseAAjouter);

            }
        }
    }
    // pas besoin de metre a jours le detecteur, car c'est de la réferance ( il est inteligent ce martin ... il s'épate lui meme, p-e parce qu'il est 2h du mat...Hug..)
}

Cible* Attaquant::attaque()
{
    // on attaque que si le timer est up
    double temps = timer.GetElapsedTime();
    //Cible* focus = NULL;

    if ( temps > 1/AS )
    {
        cible = NULL;
        // on choisi la cible ^^' (foncteur time)
        cible = (*selecteurCible)((*modeSelection)((*detecteur)()));
        std::vector<Cible *> listCible =  (*attaqueZone)(cible);
        if ( listCible.size() > 0 )
        {
                std::vector<Cible *>::iterator it = listCible.begin();
                // on reload
                timer.restart();
                for ( it ; it != listCible.end() ; ++it )
                {
                    (*it)->subirDommage(dmg);
                    std::cout << " tape pour du " << dmg << std::endl;
                }
        }

    }
    return cible;
}
// ###########################################################################################################
//                                                  Selecteurs
void  Attaquant::setAs  ( double p_as)
{
    if ( p_as > 0)
    {
        AS = p_as;
    }
}
void  Attaquant::setDmg ( double p_dmg)
{
    if ( p_dmg >= 0 )
    {
        dmg = p_dmg;
    }
}

void  Attaquant::setModeSelectionCible  ( ModeSelectionCible * p_modeSelection)
{
     if  ( p_modeSelection != NULL)
    {
        modeSelection = p_modeSelection;
    }
}
void  Attaquant::setSelecteurCible      ( SelecteurCible *p_selecteurCible)
{
     if  ( p_selecteurCible != NULL)
    {
        selecteurCible = p_selecteurCible;
    }
}
void  Attaquant::setAttaqueZone         (AttaqueZone *p_attaqueZone)
{
    if  ( p_attaqueZone != NULL)
    {
        attaqueZone = p_attaqueZone;
    }
}
