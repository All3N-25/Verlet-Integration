#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Headers/Solver.hpp"
#include "Headers/Renderer.hpp"
#include "Headers/Particle.hpp"

int main() 
{   
    Solver solver;
    Particle particle;
    
    uint16_t WindowWidth = 1000;
    uint16_t WindowHeight = 1000;

    uint16_t windowPosX = (2560 - WindowWidth) / 2;
    uint16_t windowPosY = (1440 - WindowHeight) / 2;

    sf::RenderWindow window(sf::VideoMode({WindowWidth, WindowHeight}), "My window", sf::Style::Close);
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));
    window.setFramerateLimit(60);

    float radius = 5.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);

    Renderer render(window);
    
    // run the program as long as the window is open
    while (window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        } 
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePosInt);

            Particle newParticle;
        
            newParticle.setRadius(radius);                
            newParticle.Accelerate({0.0f, 9.8f});           
            newParticle.setStartPos(mousePosFloat);

            solver.addParticles(newParticle);
        }

        //delta time
        //float dt = 1.0f / 60.0f;
        solver.update();

        window.clear(sf::Color(80, 80, 80, 255));
        
        render.RenderConstraint();

        //Render the particles
        for(const auto& particle : solver.getParticles()){
            circle.setPosition(particle.getPosition());
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(1.0f);
            circle.setFillColor(sf::Color::Red);
            window.draw(circle);
        }

        window.display();
    }
    return 0;
}