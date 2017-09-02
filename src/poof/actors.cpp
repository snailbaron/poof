#include "actors.hpp"
#include "resources.hpp"
#include "screen.hpp"

#include <algorithm>
#include <iostream>

namespace {

const float ShipMassKg = 1000.f;
const float ShipMaxSpeedMs = 40.f;
const auto ShipAccelerationForceNewton = 100000.f;
const auto ShipDecelerationForceNewton = 100000.f;

const auto ShipAccelerationMss = ShipAccelerationForceNewton / ShipMassKg;
const auto ShipDecelerationMss = ShipDecelerationForceNewton / ShipMassKg;
const auto ShipInputAccelerationMss = ShipAccelerationMss + ShipDecelerationMss;

ScreenPosition worldToScreen(const Vector<float>& worldPositionMeters)
{
    float ratio = screen::width() / 100.f;
    return {
        static_cast<int>(worldPositionMeters.x * ratio),
        static_cast<int>(worldPositionMeters.y * ratio)
    };
}

} // namespace


void Bullet::render() const
{
    const auto& texture = res::texture(res::TextureId::Bullet);
    screen::drawTexture(texture, worldToScreen(position));
}

void Bullet::update(float deltaSec)
{
    position += velocity * deltaSec;
}

void Ship::render() const
{
    const auto& texture = res::texture(textureId);
    screen::drawTexture(texture, worldToScreen(positionMeters));
}

void Ship::update(float deltaSec)
{
    Vector<float> cappedInput = input;
    if (cappedInput.norm() > 1) {
        cappedInput /= cappedInput.norm();
    }

    std::cerr << "input: " << cappedInput << std::endl;

    // If moving, apply deceleration
    auto speedMs = velocityMs.norm();
    if (speedMs > 0) {
        auto newSpeedMs =
            std::max(0.f, speedMs - ShipDecelerationMss * deltaSec);
        velocityMs *= newSpeedMs / speedMs;
    }

    // Apply input acceleration
    velocityMs += cappedInput * ShipInputAccelerationMss * deltaSec;

    // Cap speed
    if (velocityMs.norm() > ShipMaxSpeedMs) {
        velocityMs *= ShipMaxSpeedMs / velocityMs.norm();
    }

    std::cerr << "velocity: " << velocityMs << std::endl;

    // Update position using current velocity
    positionMeters += velocityMs * deltaSec;
}

void Ship::fire()
{

}