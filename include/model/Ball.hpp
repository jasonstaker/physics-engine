#pragma once

#include "Entity.hpp"

class Ball : public Entity {
public:

    // constructors
    Ball(Vec position = Vec(), Vec velocity = Vec(), Vec acceleration = Vec(), float mass = 1.0f, float radius = 10.0f);

    // destructor
    ~Ball() override {}

    // functions
    int getRadius();

private:

    // fields
    float radius;

};