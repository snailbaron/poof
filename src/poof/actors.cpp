#include "actors.hpp"
#include "resources.hpp"
#include "screen.hpp"

#include <algorithm>

void Ship::render() const
{
    const auto& texture = res::texture(textureId);
    screen::drawTexture(texture, position);
}

void Ship::update(float deltaSec)
{
    // TODO: Real movement code here
    dx += inputX * deltaSec * 1000.f;
    dy += inputY * deltaSec * 1000.f;

    dx = std::min(std::max(dx, -500.f), 500.f);


    position.x += dx * deltaSec;
    position.y += dy * deltaSec;
}