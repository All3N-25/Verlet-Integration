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
            Collisions();
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

                const sf::Vector2 to_obj = obj.getPosition() - position;
                const float dist = std::sqrt(to_obj.x * to_obj.x + to_obj.y * to_obj.y);

                if (dist > (radius - obj.getRadius())){
                    const sf::Vector2f normal = to_obj / dist;
                    sf::Vector2f currentPos = position + normal * (dist - obj.getRadius());
                    obj.setPosition(currentPos);
                }
            }
            
        }

        void Collisions(){
            const float    response_coef = 0.75f;
            const uint32_t particle_count = particles.size();

            for(uint64_t i{0}; i < particle_count; i++){
                Particle& object_1 = particles[i];

                // Iterate on object involved in new collision pairs
                for(uint64_t k{i + 1}; k < particle_count; k++){
                    Particle& object_2 = particles[k];
                    const sf::Vector2f v = object_1.getPosition() - object_2.getPosition(); 
                    const float dist2 = v.x * v.x + v.y * v.y;
                    const float min_dist = object_1.getRadius() + object_2.getRadius();

                    //Check Overlapping
                    if(dist2 < (min_dist * min_dist)){
                        const float dist = sqrt(dist2);
                        const sf::Vector2f n = v / dist;
                        const float mass_ratio_1 = object_1.getRadius() / (object_1.getRadius() + object_2.getRadius());
                        const float mass_ratio_2 = object_2.getRadius() / (object_1.getRadius() + object_2.getRadius());
                        const float delta =  0.5f * response_coef * (dist - min_dist);

                        //Update Positions
                        sf::Vector2f pos1 = (object_1.getPosition() - n * mass_ratio_2 * delta);
                        sf::Vector2f pos2 = (object_2.getPosition() + n * mass_ratio_2 * delta);
                        object_1.setPosition(pos1);
                        object_2.setPosition(pos2);
                    }
                }
             }
        }

    private:
        
        std::vector<Particle> particles;

    };