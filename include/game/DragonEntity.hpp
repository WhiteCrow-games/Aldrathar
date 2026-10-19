#pragma once

#include "game/Entity.hpp"

namespace Aldrathar {

class DragonEntity final : public Entity {
public:
    void Update(float deltaTime) override;
    void Draw() const override;

private:
    float idleTime_{0.0F};
    float headSwayDegrees_{0.0F};
    float breathScale_{0.0F};
};

} // namespace Aldrathar
