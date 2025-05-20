// Collision.cpp
#include "Collision.hpp"

Collision::Collision() {}

void Collision::update(vector<shared_ptr<Entity>>& entities) {
    qt.clear();
    for (auto& entityPtr : entities) {
        if (entityPtr) {
            qt.insert(entityPtr);
        }
    }

    vector<shared_ptr<Entity>> nearbyBuffer;
    nearbyBuffer.reserve(64);

    for (auto& entityPtr : entities) {
        if (!entityPtr) {
            continue;
        }

        auto ballPtr = static_pointer_cast<Ball>(entityPtr);
        float radiusA = ballPtr->getRadius();
        Vec position = ballPtr->getPosition();

        float reach = radiusA + Config::radius;
        AABB range(
            Vec(position.x - reach, position.y - reach),
            Vec(position.x + reach, position.y + reach)
        );

        nearbyBuffer.clear();
        qt.query(range, nearbyBuffer);

        for (auto& otherPtr : nearbyBuffer) {
            if (!otherPtr || otherPtr == entityPtr) continue;
            if (entityPtr.get() >= otherPtr.get()) continue;

            checkAndResolveBetween(entityPtr, otherPtr);
        }

        if (entityPtr && checkCollisionBorder(entityPtr)) {
            resolveCollisionBorder(entityPtr);
        }

        applyContinuousFrictionIfOnBottom(entityPtr);
    }
}

void Collision::checkAndResolveBetween(shared_ptr<Entity> entityOne,
                                       shared_ptr<Entity> entityTwo) {
    if (checkCollisionBetween(entityOne, entityTwo)) {
        resolveCollisionBetween(entityOne, entityTwo);
    }
}

// for circles only currently
bool Collision::checkCollisionBetween(const shared_ptr<Entity>& entityOne,
                                      const shared_ptr<Entity>& entityTwo) {
    auto ballOne = static_pointer_cast<Ball>(entityOne);
    auto ballTwo = static_pointer_cast<Ball>(entityTwo);
    Vec delta = ballOne->getPosition() - ballTwo->getPosition();
    float distSq = delta.dot(delta);
    float radiusSum = ballOne->getRadius() + ballTwo->getRadius();
    return distSq <= radiusSum * radiusSum;
}

bool Collision::checkCollisionBorder(const shared_ptr<Entity>& entity) {
    auto ballPtr = static_pointer_cast<Ball>(entity);
    return ((ballPtr->getPosition().x + ballPtr->getRadius()) >= Config::windowWidth)
        || ((ballPtr->getPosition().y + ballPtr->getRadius()) >= Config::windowHeight)
        || ((ballPtr->getPosition().x - ballPtr->getRadius()) <= 0)
        || ((ballPtr->getPosition().y - ballPtr->getRadius()) <= 0);
}

float Collision::distance(const shared_ptr<Entity> entityOne,
                         const shared_ptr<Entity> entityTwo) {
    auto ballOne = static_pointer_cast<Ball>(entityOne);
    auto ballTwo = static_pointer_cast<Ball>(entityTwo);
    Vec distanceVector = ballOne->getPosition() - ballTwo->getPosition();

    return (distanceVector.norm()
            - ballOne->getRadius()
            - ballTwo->getRadius());
}

void Collision::resolveCollisionBetween(shared_ptr<Entity>& entityOne,
                                        shared_ptr<Entity>& entityTwo) {
    Vec velocityOne = entityOne->getVelocity();
    Vec velocityTwo = entityTwo->getVelocity();
    float massOne = entityOne->getMass();
    float massTwo = entityTwo->getMass();

    Vec positionDelta = entityTwo->getPosition() - entityOne->getPosition();
    float correctionLength = distance(entityTwo, entityOne) * -1;
    Vec normalVector = positionDelta.getUnit();

    float combinedMass = massOne + massTwo;
    float correctionHalf = correctionLength * 0.501f;
    entityOne->getPosition() = entityOne->getPosition() - normalVector * correctionHalf;
    entityTwo->getPosition() = entityTwo->getPosition() + normalVector * correctionHalf;

    float coefficientOne = massOne - Config::restitution * massTwo;
    float coefficientTwo = 1 + Config::restitution;
    float coefficientThree = massTwo - Config::restitution * massOne;

    float velocityOneNormal = velocityOne.dot(normalVector);
    float velocityTwoNormal = velocityTwo.dot(normalVector);
    float velocityOneNormalAfter = (velocityOneNormal * coefficientOne
                                    + velocityTwoNormal * coefficientTwo * massTwo)
                                   / combinedMass;
    float velocityTwoNormalAfter = (velocityTwoNormal * coefficientThree
                                    + velocityOneNormal * coefficientTwo * massOne)
                                   / combinedMass;

    Vec velocityOneNormalVector = normalVector * velocityOneNormal;
    Vec velocityTwoNormalVector = normalVector * velocityTwoNormal;

    Vec velocityOneTangent = velocityOne - velocityOneNormalVector;
    Vec velocityTwoTangent = velocityTwo - velocityTwoNormalVector;

    Vec velocityOneNormalAfterVector = normalVector * velocityOneNormalAfter;
    Vec velocityTwoNormalAfterVector = normalVector * velocityTwoNormalAfter;

    entityOne->getVelocity() = velocityOneTangent + velocityOneNormalAfterVector;
    entityTwo->getVelocity() = velocityTwoTangent + velocityTwoNormalAfterVector;
}

void Collision::resolveCollisionBorder(shared_ptr<Entity>& entity) {
    auto ballPtr = static_pointer_cast<Ball>(entity);
    float impulseMagnitude = ballPtr->getMass();

    // Right border
    if ((ballPtr->getPosition().x + ballPtr->getRadius()) >= Config::windowWidth) {
        ballPtr->getVelocity() = Vec(
            ballPtr->getVelocity().x * -1 * Config::restitution,
            ballPtr->getVelocity().y
        );
        ballPtr->getPosition() = Vec(
            Config::windowWidth - ballPtr->getRadius(),
            ballPtr->getPosition().y
        );
    }

    // Bottom border
    if ((ballPtr->getPosition().y + ballPtr->getRadius()) >= Config::windowHeight) {
        ballPtr->getPosition().y = Config::windowHeight - ballPtr->getRadius();
        ballPtr->getVelocity().y *= -Config::restitution;
    }

    // Left border
    if ((ballPtr->getPosition().x - ballPtr->getRadius()) <= 0) {
        ballPtr->getVelocity() = Vec(
            ballPtr->getVelocity().x * -1 * Config::restitution,
            ballPtr->getVelocity().y
        );
        ballPtr->getPosition() = Vec(
            ballPtr->getRadius(),
            ballPtr->getPosition().y
        );
    }

    // Top border
    if ((ballPtr->getPosition().y - ballPtr->getRadius()) <= 0) {
        ballPtr->getVelocity() = Vec(
            ballPtr->getVelocity().x,
            ballPtr->getVelocity().y * -1 * Config::restitution
        );
        ballPtr->getPosition() = Vec(
            ballPtr->getPosition().x,
            ballPtr->getRadius()
        );
    }
}

void Collision::applyContinuousFrictionIfOnBottom(shared_ptr<Entity>& entity) {
    auto ballPtr = static_pointer_cast<Ball>(entity);

    float bottomY = ballPtr->getPosition().y + ballPtr->getRadius();
    if (abs(bottomY - Config::windowHeight) < 0.5f) {
        if (abs(ballPtr->getVelocity().x) > 0.0f) {
            float frictionImpulse = Config::gravity.y * Config::frictionCoefficient * Config::fixedTimeStep * Config::timeScale;
            float direction = (ballPtr->getVelocity().x > 0) ? -1.0f : 1.0f;

            ballPtr->getVelocity().x += direction * frictionImpulse;

            if (ballPtr->getVelocity().x * direction > 0) {
                ballPtr->getVelocity().x = 0.0f;
            }
        }
    }
}
