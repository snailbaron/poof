#pragma once

#include "resources.hpp"
#include "vectors.hpp"

struct Movement {
    float dx;
    float dy;
};

struct Bullet {
    Bullet(Vector<float> position, Vector<float> velocity)
        : position(position)
        , velocity(velocity)
    { }

    void render() const;
    void update(float deltaSec);

    Vector<float> position;
    Vector<float> velocity;
};

struct Ship {
    void render() const;
    void update(float deltaSec);

    void fire();

    Vector<float> positionMeters;
    res::TextureId textureId = res::TextureId::Ship;
    Vector<float> velocityMs;
    Vector<float> input;
};