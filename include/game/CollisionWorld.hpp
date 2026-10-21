#pragma once

namespace Aldrathar {

class CollisionWorld {
public:
    [[nodiscard]] bool IsBlocked(float x, float z) const noexcept;
};

} // namespace Aldrathar
