// Renderer.cpp
#include "Renderer.hpp"
#include "Entity.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

Renderer::Renderer() {}

Renderer::Renderer(unsigned int width, unsigned int height) : width(width), height(height) {
    window = new sf::RenderWindow(sf::VideoMode({width, height}), "Physics Engine");
    window->setVerticalSyncEnabled(true);
}

void Renderer::render(const vector<shared_ptr<Entity>>& entities) {
    
    if (window->isOpen()) {
        if (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window->close();
                }
            }
        }

        window->clear();
        for (shared_ptr<Entity> entity : entities) {
            renderEntity(entity);
        }
        window->display();
    }
}

void Renderer::renderEntity(const shared_ptr<Entity>& entity) {
    auto drawnEntity = shapeFactory.createShape(entity);
    window->draw(*drawnEntity);
}