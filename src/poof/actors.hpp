#pragma once

#include "resources.hpp"

struct ActorPosition {
    float x;
    float y;
};

struct Movement {
    float dx;
    float dy;
};

struct Ship {
    ActorPosition position;
    Movement movement;
    res::TextureId textureId = res::TextureId::Ship;
};