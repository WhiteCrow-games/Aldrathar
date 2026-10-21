#include "game/CollisionWorld.hpp"

#include <array>

namespace Aldrathar {
namespace {

struct CircleCollider {
    float x;
    float z;
    float radius;
};

struct AabbCollider {
    float minX;
    float maxX;
    float minZ;
    float maxZ;
};

constexpr std::array<CircleCollider, 6> TREE_TRUNKS{{
    {-5.0F, -3.0F, 0.53F},
    { 5.5F, -4.0F, 0.53F},
    {-6.0F,  3.0F, 0.53F},
    { 6.5F,  4.0F, 0.53F},
    {-4.5F,  7.0F, 0.53F},
    { 4.5F,  9.0F, 0.53F}
}};

// Límites de las paredes, incluyendo el espacio de colisión del jugador.
// La abertura central de la pared frontal conserva el paso de la puerta.
constexpr std::array<AabbCollider, 5> HOUSE_WALLS{{
    {-2.83F, -2.03F, -6.95F, -3.0F},
    { 2.03F,  2.83F, -6.95F, -3.0F},
    {-2.85F,  2.85F, -7.08F, -6.28F},
    {-2.85F, -0.17F, -3.65F, -2.85F},
    { 0.17F,  2.85F, -3.65F, -2.85F}
}};

bool InsideAabb(float x, float z, const AabbCollider& box) noexcept
{
    return x > box.minX && x < box.maxX &&
           z > box.minZ && z < box.maxZ;
}

} // namespace

bool CollisionWorld::IsBlocked(float x, float z) const noexcept
{
    if (x < -13.0F || x > 13.0F ||
        z < -13.0F || z > 13.0F) {
        return true;
    }

    for (const CircleCollider& tree : TREE_TRUNKS) {
        const float dx = x - tree.x;
        const float dz = z - tree.z;

        if (dx * dx + dz * dz <= tree.radius * tree.radius) {
            return true;
        }
    }

    for (const AabbCollider& wall : HOUSE_WALLS) {
        if (InsideAabb(x, z, wall)) {
            return true;
        }
    }

    return false;
}

} // namespace Aldrathar
