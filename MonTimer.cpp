#include "MonTimer.hpp"

double MonTimer::vitesse = 1;

MonTimer::MonTimer () : sf::Clock()
{
}
float MonTimer::GetElapsedTime() const
{
    return sf::Clock::getElapsedTime().asMicroseconds() * MonTimer::vitesse;
}
void MonTimer::restart()
{

    sf::Clock::restart();
}

void MonTimer::setSpeed(double p_vit)
{
    if ( p_vit > 0 )
        MonTimer::vitesse = p_vit;
}
