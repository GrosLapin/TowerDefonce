#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <map>
#include <string>
#include <queue>
class Case;
class Map
{
    public :
        Map ();
        bool addCase(Case* p_case);
        std::vector<Case* >& getListCase () { return listCase ;};
        bool removeCase (int i, int j);
        Case* getCase(int i, int j) ;

    private :
        std::vector<Case* > listCase;
        std::map< std::string , Case* > mapCase;


};
#endif


