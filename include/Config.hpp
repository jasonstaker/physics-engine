#pragma once

#include "Vec.hpp"

namespace Config {

    // Window dimensions
    static constexpr unsigned int windowWidth = 1000;
    static constexpr unsigned int windowHeight = 800;

    // Physics parameters
    constexpr static float timeScale = 6.0f;
    static Vec gravity = Vec(0, 9.81f);
    constexpr static float dragCoefficient = 0.01f;
    constexpr static float restitution = .8f;
    constexpr static float frictionCoefficient = 1.0f;

    // Simulation variables
    static constexpr float simulationRunTime = 6.0f;
    static constexpr float renderFrequencyMultiplier = 3.0f;
    static constexpr float targetFPS = 60.0f;
    const double frameDuration = 1000.0 / targetFPS;
    const float fixedTimeStep = 1.0f / (targetFPS*renderFrequencyMultiplier);

    static const int numBalls = 1000;
    static const float radius = 10.0f;
    static const float spawnMargin = radius;
    static const int maxAttempts = 5000;
}