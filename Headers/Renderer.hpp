#pragma once

class Renderer{
    private:
    sf::RenderTarget& m_target;
    
    public:

        explicit
        Renderer(sf::RenderTarget& target)
            : m_target{target}
        {

        }

        void RenderConstraint(){
            float constraintRadius = 400.0f;
            sf::CircleShape ConstraintCircle(constraintRadius);
            ConstraintCircle.setPosition(sf::Vector2f(1000/2.0f, 1000/2.0f));

            ConstraintCircle.setPointCount(100); 
            ConstraintCircle.setOutlineThickness(2.0f);
            ConstraintCircle.setOrigin(constraintRadius, constraintRadius);
            ConstraintCircle.setFillColor(sf::Color::Transparent);
            ConstraintCircle.setOutlineColor(sf::Color::White);
            
            m_target.draw(ConstraintCircle);
        }

};


