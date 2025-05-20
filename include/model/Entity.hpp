#pragma once

#include "Vec.hpp"
#include <chrono>

using namespace std;
using namespace chrono;

class Entity {
public:

    // constructors
    Entity(Vec position = Vec(), Vec velocity = Vec(), Vec acceleration = Vec(), float mass = 1.0f);

    // destructor
    virtual ~Entity() {};

    // functions
    Vec& getPosition();
    Vec& getVelocity();
    Vec& getAcceleration();
    float getMass();

private:

    // fields
    Vec position, velocity, acceleration;
    float mass;

};