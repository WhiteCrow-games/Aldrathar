#include "aldrathar/objects/GameObject.hpp"

namespace Aldrathar {

const Vector3& GameObject::GetPosition() const noexcept {
    return position_;
}

void GameObject::SetPosition(const Vector3& position) noexcept {
    position_ = position;
}

} // namespace Aldrathar
