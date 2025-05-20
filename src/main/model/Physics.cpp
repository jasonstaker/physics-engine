// Physics.cpp
#include "Physics.hpp"
#include <iostream>

void Physics::update(const vector<shared_ptr<Entity>>& entities, float dt) {
    for (const auto& entity : entities) {
        updateEntity(entity, dt);
    }
}

void Physics::updateEntity(const shared_ptr<Entity>& entity, float dt) {
    Vec& acc = entity->getAcceleration();
    Vec& vel = entity->getVelocity();
    Vec& pos = entity->getPosition();

    pos = pos + (vel * dt * Config::timeScale);
    vel = vel + (acc * dt * Config::timeScale);
    acc = (Config::gravity + getLinearDragVec(entity));
    
}

Vec Physics::getLinearDragVec(const shared_ptr<Entity>& entity) {
    return entity->getVelocity() * Config::dragCoefficient * -1;
}