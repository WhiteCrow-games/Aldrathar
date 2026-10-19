#pragma once

#include "game/Entity.hpp"

namespace Aldrathar {

class Player final : public Entity {
public:
    void Update(float deltaTime) override;
    void Draw() const override;

    void SetMoving(bool moving) noexcept {
        moving_ = moving;
    }

    void SetFacingDirection(float directionX, float directionZ) noexcept;

private:
    float animationTime_{0.0F};
    float facingAngleDegrees_{0.0F};
    bool moving_{false};
};

} // namespace Aldrathar
