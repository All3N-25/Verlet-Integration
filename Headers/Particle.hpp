#pragma once
#include <SFML/Graphics.hpp>


class Particle{
    sf::Vector2f position_current = {400, 300};
    sf::Vector2f position_previous = {400, 300};
    sf::Vector2f Accelation;

    public:
        void updatePosition(float dt){
            const sf::Vector2f velocity = position_current - position_previous;

            //Save current position
            position_previous = position_current;
        
            //Verlet Integration
            position_current = position_current + velocity + Accelation * dt * dt;
            //Reset accel
            Accelation = {};
        }

        void Accelerate(sf::Vector2f acc){
            Accelation += acc;
        }

        sf::Vector2f getPosition() const {
            return position_current;
        }
        
};