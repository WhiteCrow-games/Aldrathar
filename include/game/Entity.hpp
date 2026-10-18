#pragma once

#include <raylib.h>

namespace Aldrathar {

class Entity {
public:
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const = 0;

    const Vector3& GetPosition() const noexcept {
        return position_;
    }

    Vector3& GetPosition() noexcept {
        return position_;
    }

    void SetPosition(Vector3 position) noexcept {
        position_ = position;
    }

protected:
    Vector3 position_{0.0F, 0.0F, 0.0F};
};

} // namespace Aldrathar
