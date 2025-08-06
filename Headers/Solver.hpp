#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>
#include <cmath>

class Solver{
    
    sf::Vector2f gravity = {0.0f, 1000.0f};

    public:


        void addParticles(const Particle& p){
            particles.push_back(p);
        }
        
        const std::vector<Particle>& getParticles() const {
            return particles;
        }
        
        void update(float dt){
            applyGravity();
            applyConstraint();
            updatePositions(dt);

        }

        void updatePositions(float dt){
            for(auto& obj : particles){
                obj.updatePosition(dt);
            }
        }

        void applyGravity(){
            for(auto& obj : particles) {
                obj.Accelerate(gravity);
            }
        }

        //Container
        void applyConstraint(){
            
            const sf::Vector2 position{500.0f, 500.0f};                 //Position of the Circle Constraint
            const float radius = 400.0f;                                //Radius of the Circle Constraint
            
            for(auto& obj : particles){

                const sf::Vector2 to_obj = obj.position_current - position;
                const float dist = std::sqrt(to_obj.x * to_obj.x + to_obj.y * to_obj.y);

                if (dist > (radius - 10.0f)){
                    const sf::Vector2f normal = to_obj / dist;
                    obj.position_current = position + normal * (dist - 10.0f);
                }
            }
            
        }

    private:
        
        std::vector<Particle> particles;

    };