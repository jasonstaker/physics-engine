#pragma once

#include "Entity.hpp"
#include "Quadtree.hpp"
#include "Ball.hpp"
#include "Config.hpp"
#include "Physics.hpp"
#include "AABB.hpp"
#include "Quadtree.hpp"
#include <vector>
#include <memory>
#include <cmath>
#include <thread>

using namespace std;

class Collision {

    // fields
    Quadtree qt = Quadtree(AABB(Vec(0, 0), Vec(Config::windowWidth, Config::windowHeight)), 6);
    vector<thread> threads;

public:

    // constructors
    Collision();

    // functions
    void update(vector<shared_ptr<Entity>>& entities);
    static bool checkCollisionBetween(const shared_ptr<Entity>& entityOne, const shared_ptr<Entity>& entityTwo);
    static bool checkCollisionBorder(const shared_ptr<Entity>& entity);
    static float distance(const shared_ptr<Entity> entityOne, const shared_ptr<Entity> entityTwo);
    static void resolveCollisionBetween(shared_ptr<Entity>& entityOne, shared_ptr<Entity>& entityTwo);
    static void resolveCollisionBorder(shared_ptr<Entity>& entity);
    static void checkAndResolveBetween(shared_ptr<Entity> entityOne, shared_ptr<Entity> entityTwo);
    void applyContinuousFrictionIfOnBottom(std::shared_ptr<Entity>& entity);
    
};