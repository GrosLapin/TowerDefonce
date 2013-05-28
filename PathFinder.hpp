#ifndef PATHFINDER
#define PATHFINDER
#include <list>

class Case;
class PathFinder
{
    public :
        PathFinder () {};
        virtual ~PathFinder() {};

        virtual std::list<Case *> operator() (Case *spawn,  std::list<Case*> listNexus);

        virtual double caseFanchissable (Case* p_case);
        virtual double poidCase         (Case* p_case);

        virtual bool isBerserk () { return berserk ;};

        //debug
         std::map<Case*,double > getMapPoid(Case *spawn,  std::list<Case*> listNexus);
    protected :
        bool berserk;

};

// on ne s'arrete pas sur une tour
class PathFinderVol : public PathFinder
{
    public :
    virtual double caseFanchissable (Case* p_case) { return true;};
};

class PathBerserk : public PathFinder
{
    public :
    virtual std::list<Case *> operator() (Case *spawn,  std::list<Case*> listNexus);
    virtual double caseFanchissable (Case* p_case) { return true;};



};

 bool notFranchissable(Case* p_case);
#endif
