#ifndef ENUM_HPP
#define ENUM_HPP

enum Direction
{
    Est  =0 ,
    NordEst = 1,
    NordOuest =2,
    Ouest = 3,
    SudOuest =4,
    SudEst = 5,
    DebutDirection = Est,
    FinDirection = SudEst
};

enum TypeDePorte
{
    Disque = 0,
    Etoile =1,
    LigneO_E =2,
    LigneSO_NE =3,
    LigneSE_NO =4,
    CerclePaire =5,
    CercleImpaire =6,
    DebutPorte = Disque,
    FinPorte = CercleImpaire
};

Direction directionOppose (const Direction &p_dir);
void IJvoisin (const Direction&  p_dir, int& i, int& j);

#endif
