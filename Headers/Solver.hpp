#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>

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
            updatePositions(dt);

        }

        void updatePositions(float dt){
            for(auto& obj : particles){
                obj.updatePosition(dt);
            }
        }

        void applyGravity(){
            for (auto& obj : particles) {
                obj.Accelerate(gravity);
            }
        }

    private:
        
        std::vector<Particle> particles;

    };