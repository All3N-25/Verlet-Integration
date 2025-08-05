#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Solver.hpp"
#include "Headers/Renderer.hpp"
#include "Headers/Particle.hpp"

int main() 
{
    float radius = 50.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);

    uint16_t WindowWidth = 800;
    uint16_t WindowHeight = 600;

    uint16_t windowPosX = (2560 - 800) / 2;
    uint16_t windowPosY = (1440 - 600) / 2;

    sf::RenderWindow window(sf::VideoMode({WindowWidth, WindowHeight}), "My window", sf::Style::Close);
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));

    window.setFramerateLimit(60);

    Solver solver;
    Particle particle;

    particle.Accelerate({0.0f, 9.8f});

    solver.addParticles(particle);

    
    // run the program as long as the window is open
    while (window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }

        float dt = 1.0f / 60.0f;

        solver.update(dt);

        window.clear(sf::Color(0, 0, 0, 255));

        for(const auto& particle : solver.getParticles()){
            circle.setPosition(particle.getPosition());
            circle.setFillColor(sf::Color::Red);
            window.draw(circle);
        }

        window.display();
    }
    return 0;
}