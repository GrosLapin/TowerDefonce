#include "Cible.hpp"
#include "Effet.hpp"
#include "Case.hpp"
#include "Map.hpp"
#include "Fonction_generales.hpp"

Cible::Cible ()
{
    position = NULL;
    volante = false;
    visible = true;
    // les pv sont definie dans l'arrivé en jeu
    pv = 0;
    pvAlaCreation = 100;
}

/// Je suis une putin de fonction friend, pour ça que je passe Cible*
void changeCase(Cible* cible,Case* nouvelleCase)
{

    // te paye pas ma tete merci
    if ( nouvelleCase != NULL && cible->position != NULL)
    {

        ///###########################################################
        ///                   1) les effest propre
        ///###########################################################
        // on regarde les auras qui se finissent et ceux qui commence
        std::list<Effet* > copyEffetCaseAvant = cible->position->getListEffets();
        std::list<Effet* > copyEffetCaseApres = nouvelleCase->getListEffets();
        std::list<Effet* > copyEffetASupprimer;

        // on supprimes les ellement qui sont dans les deux liste
        std::list<Effet* >::iterator it= copyEffetCaseAvant.begin();
        for ( it ; it != copyEffetCaseAvant.end() ; ++it )
        {
            // on cherche l'ellement avec find
            // si il le trouve pas il retourne copyEffetCaseApres.back()
            // donc on rentre dans le if si on le trouve
            if ( copyEffetCaseApres.end() != std::find( copyEffetCaseApres.begin(),  copyEffetCaseApres.end(), (*it) ) )
            {
                // on supprime dans les deux cases
                copyEffetASupprimer.push_back((*it));
            }
        }
        // on supprime concretement
        it= copyEffetASupprimer.begin();
        for ( it ; it != copyEffetASupprimer.end() ; ++it )
        {
            copyEffetCaseApres.remove((*it));
            copyEffetCaseAvant.remove((*it));
        }

        // on supprime les effets qui sont encors dans la liste avant
        it= copyEffetCaseAvant.begin();

        for ( it ; it != copyEffetCaseAvant.end() ; ++it )
        {
            // il ne faut pas retirer un effet que l'on difuse, il y sera forcement a la case suivante
            if ( cible->listEffetAura.end() == std::find(cible->listEffetAura.begin(),cible->listEffetAura.end(),(*it)) )
            cible->removeEffetPropre((*it));
        }

        // et on ajoute les effet qui n'etait pas la avant
        it= copyEffetCaseApres.begin();

        for ( it ; it != copyEffetCaseApres.end() ; ++it )
        {
            cible->addEffetPropre((*it));
        }


        ///###########################################################
        ///                   2) les aura de la cible
        ///###########################################################
        // 1) on crée liste de case a porté de la prochaine case
        std::set<Case *> caseAPorteApres;
        std::set<Case *> nouvellePorte;
        std::set<Case *> caseAPorteAvant = cible->caseAPorteDEffet;
        std::vector<sf::Vector2<int> >::iterator it2 = cible->listCaseCandidates.begin();
        for ( it2 ; it2!=cible->listCaseCandidates.end() ; ++it2 )
        {
            // les case candidates sont centrée en (0,0) il faut ajoute la possision du centre pour avoir les cases a porté
            Case* caseAAjouter = cible->position->getMap().getCase(it2->x+nouvelleCase->getI(), it2->y+nouvelleCase->getJ() );
            if ( caseAAjouter != NULL)
            {
                // la case existe on l'ajoute a la liste des case a porté
                caseAPorteApres.insert(caseAAjouter);
                nouvellePorte.insert(caseAAjouter);
            }
        }

        // 2) supression des doublon
        std::set<Case *> caseASupprimer;
         std::set<Case *>::iterator itCase= caseAPorteAvant.begin();
        for (itCase ; itCase != caseAPorteAvant.end() ; ++itCase )
        {
            // on cherche l'ellement avec find
            // si il le trouve pas il retourne caseASupprimer.back()
            // donc on rentre dans le if si on le trouve
            if ( caseAPorteApres.end() != std::find( caseAPorteApres.begin(),  caseAPorteApres.end(), (*itCase) ) )
            {
                // on supprime dans les deux cases
                caseASupprimer.insert((*itCase));
            }
        }
         // on supprime concretement
        itCase= caseASupprimer.begin();
        for ( itCase ;itCase != caseASupprimer.end() ; ++itCase )
        {
            caseAPorteApres.erase(caseAPorteApres.find(*itCase));
            caseAPorteAvant.erase(caseAPorteAvant.find(*itCase));
        }

        // on supprime les case hors porté
        itCase= caseAPorteAvant.begin();
        for ( itCase ;itCase != caseAPorteAvant.end() ; ++itCase )
        {

            (*itCase)->removeEffect(cible->listEffetAura);
        }


        // et on ajoute les a porté
        itCase= caseAPorteApres.begin();
        for ( itCase; itCase != caseAPorteApres.end() ; ++itCase )
        {

            (*itCase)->ajoutEffect(cible->listEffetAura);
        }
        ///###########################################################
        /// 3) on change de position ( c'est le but quand meme hein ;)
        ///###########################################################

        cible->position = nouvelleCase;
        cible->caseAPorteDEffet = nouvellePorte;
    }
}

// ajoute des effet a difuser
void Cible::addEffetAura       (Effet* p_effet)
{
    // on ajoute a la liste des effets
    listEffetAura.push_back(p_effet);
    // et on difuse
    std::set<Case *>::iterator it = caseAPorteDEffet.begin();
    //std::cout<<"liste a porte d'effet : "<< caseAPorteDEffet.size() << std::endl;
    for ( it ; it != caseAPorteDEffet.end() ; ++it)
    {
        (*it)->ajoutEffect(p_effet);
    }

}
void Cible::removeEffetAura    (Effet* p_effet)
{
    int i=0;
    while ( listEffetAura[i] != p_effet && i < listEffetAura.size() )
        i +=1;
    if ( i < listEffetAura.size() )
    {
        // y a surment plus simple

        std::set<Case *>::iterator it = caseAPorteDEffet.begin();
        for ( it ; it != caseAPorteDEffet.end() ; ++it)
        {
            (*it)->removeEffect(p_effet);
        }

        listEffetAura.erase(listEffetAura.begin() + i);
    }

}



// les effets sur la cible
void Cible::ajoutEffetOverTimePropre      (EffetOverTime *p_effet )
{
    // on ajoute a la liste

    listEffetOverTime.push_back(p_effet);

}
void Cible::ajoutEffetUniquePropre        (EffetUnique *p_effet )
{
    listEffetUnique.push_back(p_effet);
}
void Cible::removeEffetOverTimePropre     (EffetOverTime *p_effet )
{
     listEffetOverTime.remove(p_effet);
}
void Cible::removeEffetUniquePropre       (EffetUnique *p_effet )
{
     listEffetUnique.remove(p_effet);
}

bool Cible::subirDommage(double dommage)
{
    pv -=dommage;
    // std::cout<<vie<<std::endl;
    if (pv <= 0)
    {

        pv= 0;

        quitteLeJeu();
        return true;
    }
    return false;
}
Cible::~Cible()
 {

     // il serait de bon gout de supprimer les effects des cases a porté
     /// !!! DANGER !!!
     /// si on fait qui le jeu ici, c'est appellé apres le destructeur de la classe fille
     /// et on va perdre "l'identité" de la fille et faire des appel a des fonction de la mere
     /// qui pas de chance sont en virtuel pure ....
     //this->quitteLeJeu();
     /// donc ne pas faire ça x)

     // et on supprime que les effet d'aura
      std::vector<Effet*>::iterator itEA = listEffetAura.begin();
      for ( itEA ; itEA != listEffetAura.end() ; ++ itEA)
      {
          delete (*itEA);
      }
 }
void Cible::quitteLeJeu ()
{
    // on annulle l'effet de nos aura
    std::set<Case *>::iterator it =  caseAPorteDEffet.begin();
   // std::cout << "suppression de : " <<caseAPorteDEffet.size() << " effet " << std::endl;
    for ( it ; it != caseAPorteDEffet.end() ; ++it )
    {
        // voila voila ...
        (*it)->removeEffect(listEffetAura);

    }
    // ça evitera les problemes ^^
    listEffetAura.clear();
    // je sais pas si c'est utile de la mettre mais la logique veux qu'il y soit
    // position = NULL; // si on fait ca le destructeur ne peux plus supprimer dans la liste de tour
    pv = 0;

}


void Cible::MAJcaseAPorte()
{
    std::vector<sf::Vector2<int> >::iterator it = listCaseCandidates.begin();
    std::pair<std::set<Case *>::iterator,bool> ret;
    for ( it ; it!=listCaseCandidates.end() ; ++it )
    {
        // les case candidates sont centrée en (0,0) il faut ajoute la possision du centre pour avoir les cases a porté
        Case* caseAAjouter = position->getMap().getCase(it->x+position->getI(), it->y+position->getJ() );
        if ( caseAAjouter != NULL)
        {
            // la case existe on l'ajoute a la liste des case a porté
            ret = caseAPorteDEffet.insert(caseAAjouter);
            // et on a ajoute cette effet dans la liste de la case
            // la case va egalement repercuté l'ajoute de ces aura sur les cibles dans la case
            if (ret.second==true)
            {
                 caseAAjouter->ajoutEffect(listEffetAura);
            }

        }

    }
}

// la case n'est pas en const car on lui appliquera les effect de la tour
void Cible::arriveEnJeu (Case *p_position)
{
    // 1) on fixe la position
    position = p_position;

    // 2) on ajoute a notre liste de case et on transmet nos aura
    //on parcourt les case candidates et on les ajoute a la liste des cases a po si la case existe dans la carte
    MAJcaseAPorte();

    // 3) on recupere les aura sur la case
    std::list<Effet* > effetSurLaCase = position->getListEffets();
    std::list<Effet* >::iterator itlistEffet = effetSurLaCase.begin();
    for ( itlistEffet ; itlistEffet != effetSurLaCase.end() ; ++ itlistEffet)
    {
        addEffetPropre ((*itlistEffet));
    }
    // 4) on donne vie a cette petit cible
    pv = pvAlaCreation;

}


void Cible::addPorteEffet(TypeDePorte tdp, unsigned int porte)
{
    // on garde en memoir
    listPorte.push_back(porte);
    listTypeDePorte.push_back(tdp);
    std::vector<sf::Vector2<int> > newCandidats =  casesCibles(  porte, tdp);
    std::vector<sf::Vector2<int> >::iterator it = newCandidats.begin();
    // on ajotue les cases a porté a la lsite des cases cibles
    for ( it ; it != newCandidats.end() ; ++it )
    {
        listCaseCandidates.push_back((*it));
    }

    // si la tours est deja en jeu
    if ( position != NULL)
    {
        std::cout<<"cible non null!!"<< position->toString() << "  " << NULL << std::endl;
        MAJcaseAPorte();
    }
}


// setteur
void Cible::setPV(const double p_pv)
{
    if ( p_pv > 0 )
    {
        pv = p_pv;
    }
}

void Cible::setArmure (const double p_armure )
{
    if ( p_armure > 0)
    {
        armure = p_armure;
    }
}

void Cible::setPrixDeBase ( const unsigned int p_gold)
{
    if ( p_gold > 0 )
    {
        prixDeBase = p_gold;
    }
}


