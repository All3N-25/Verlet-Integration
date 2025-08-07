#pragma once
#include <SFML/Graphics.hpp>


class Particle{

    private:
    sf::Vector2f position_current;
    sf::Vector2f position_previous;
    sf::Vector2f Accelation;
    float Radius;

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

        void setStartPos(sf::Vector2f pos){
            position_current = pos;
            position_previous = pos;
        }

        void setPosition(sf::Vector2f Position){
            position_current = Position;
        }

        sf::Vector2f getPosition() const {
            return position_current;
        }


        void setRadius(float Rad){
            Radius = Rad;
        }

        float getRadius() const{
            return Radius;
        }
        
};