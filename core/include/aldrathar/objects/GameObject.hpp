#pragma once

#include "aldrathar/math/Vector3.hpp"

namespace Aldrathar {

class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    [[nodiscard]]
    const Vector3& GetPosition() const noexcept;

    void SetPosition(const Vector3& position) noexcept;

private:
    Vector3 position_{};
};

} // namespace Aldrathar
