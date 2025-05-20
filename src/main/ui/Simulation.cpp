// Simulation.cpp
#include "Simulation.hpp"

int numEntities;

Simulation::Simulation() : world(Config::windowWidth, Config::windowHeight, {}) {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> distX(Config::spawnMargin, Config::windowWidth  - Config::spawnMargin);
    std::uniform_real_distribution<float> distY(Config::spawnMargin, Config::windowHeight - Config::spawnMargin);
    std::uniform_real_distribution<float> distV(-150.0f, 150.0f);

    std::vector<Vec> placed;
    placed.reserve(Config::numBalls);

    for (int i = 0; i < Config::numBalls; ++i) {
        bool ok = false;
        for (int att = 0; att < Config::maxAttempts; ++att) {
            Vec p{ distX(rng), distY(rng) };
            bool clash = false;
            for (auto& q : placed) {
                if ((p - q).norm() < Config::radius * 2.0f) {
                    clash = true;
                    break;
                }
            }
            if (!clash) {
                placed.push_back(p);
                Vec v{ distV(rng), distV(rng) };
                world.addEntity(std::make_shared<Ball>(p, v, Vec(), 1.0f, Config::radius));
                ok = true;
                break;
            }
        }
        if (!ok) {
            break;
        }
        numEntities++;
    }

    renderer = Renderer(Config::windowWidth, Config::windowHeight);
}

void Simulation::run() {
    // temporary
    float total = 0.0f;
    //

    auto lastRenderTime = high_resolution_clock::now();
    auto lastTime = lastRenderTime;

    float accumulator = 0.0f;
    float acc = 0.0f;
    float num = 1.0f;

    bool running = true;
    while (running) {
        // temporary
            if (total >= Config::simulationRunTime) {
                running = false;
                break;
            }
        //
        
        auto currentTime = high_resolution_clock::now();
        float frameTime = duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        frameTime = std::min(frameTime, 0.25f);

        accumulator += frameTime;

        while (accumulator >= Config::fixedTimeStep) {
            world.update(Config::fixedTimeStep);
            accumulator -= Config::fixedTimeStep;
            total += Config::fixedTimeStep;
        }

        /*
        if (duration<double, std::milli>(currentTime - lastRenderTime).count() >= Config::frameDuration) {
            acc += 1/duration<float>(currentTime - lastRenderTime).count();
            num += 1;
            lastRenderTime = currentTime;
            renderer.render(world.getEntities());
        }
        */
       renderer.render(world.getEntities());

    }

    cout << "Average FPS: " << acc/num;
    cout << "\nNumber of Entities Spawned: " << numEntities;

}