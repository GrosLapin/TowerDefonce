#ifndef timer_hpp
#define timer_hpp
#include <SFML/Graphics.hpp>

class MonTimer : public sf::Clock
{
    public :
        float GetElapsedTime() const;
        void restart();
        MonTimer ();
        static void setSpeed(double p_vit);
        static double getSpeed () { return vitesse;};
    private :
        static double vitesse;


};

#endif
