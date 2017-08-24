#pragma once

#include "resources.hpp"

struct WorldPosition {
    float x;
    float y;
};

struct Movement {
    float dx;
    float dy;
};

struct Ship {
    void render() const;
    void update(float deltaSec);

    WorldPosition position;
    res::TextureId textureId = res::TextureId::Ship;
    float dx;
    float dy;
    float inputX;
    float inputY;
};