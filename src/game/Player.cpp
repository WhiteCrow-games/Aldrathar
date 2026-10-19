#include "game/Player.hpp"

#include <cmath>
#include <rlgl.h>

namespace Aldrathar {

void Player::Update(float deltaTime)
{
    animationTime_ += deltaTime;
}

void Player::SetFacingDirection(float directionX, float directionZ) noexcept
{
    if (directionX == 0.0F && directionZ == 0.0F) {
        return;
    }

    facingAngleDegrees_ = std::atan2(directionX, directionZ) * RAD2DEG;
}

void Player::Draw() const
{
    const float walk = moving_
        ? std::sin(animationTime_ * 8.0F) * 0.15F
        : 0.0F;

    const Vector3& p = position_;

    // Girar todo el modelo alrededor de los pies del jugador.
    rlPushMatrix();
    rlTranslatef(p.x, p.y, p.z);
    rlRotatef(facingAngleDegrees_, 0.0F, 1.0F, 0.0F);
    rlTranslatef(-p.x, -p.y, -p.z);

    // Sombra
    DrawCylinder(
        Vector3{p.x, 0.01F, p.z},
        0.4F, 0.4F, 0.02F, 8,
        Color{0, 0, 0, 60}
    );

    // Piernas
    DrawCube(
        Vector3{p.x - 0.14F,
                0.25F + (moving_ ? std::abs(walk * 0.3F) : 0.0F),
                p.z + walk},
        0.18F, 0.55F, 0.2F,
        Color{45, 55, 75, 255}
    );

    DrawCube(
        Vector3{p.x + 0.14F,
                0.25F + (moving_ ? std::abs(walk * 0.3F) : 0.0F),
                p.z - walk},
        0.18F, 0.55F, 0.2F,
        Color{45, 55, 75, 255}
    );

    // Torso y cinturón
    DrawCube(
        Vector3{p.x, 0.85F, p.z},
        0.5F, 0.65F, 0.32F,
        Color{65, 82, 104, 255}
    );

    DrawCube(
        Vector3{p.x, 0.6F, p.z},
        0.52F, 0.08F, 0.34F,
        Color{80, 60, 40, 255}
    );

    // Brazos
    DrawCube(
        Vector3{p.x - 0.32F, 0.85F, p.z - walk * 0.5F},
        0.15F, 0.55F, 0.15F,
        Color{184, 145, 112, 255}
    );

    DrawCube(
        Vector3{p.x + 0.32F, 0.85F, p.z + walk * 0.5F},
        0.15F, 0.55F, 0.15F,
        Color{184, 145, 112, 255}
    );

    // Cabeza, pelo y ojos
    DrawSphere(
        Vector3{p.x, 1.45F, p.z},
        0.24F,
        Color{184, 145, 112, 255}
    );

    DrawCube(
        Vector3{p.x, 1.62F, p.z},
        0.28F, 0.12F, 0.28F,
        Color{50, 40, 30, 255}
    );

    DrawCube(
        Vector3{p.x - 0.08F, 1.48F, p.z + 0.18F},
        0.04F, 0.04F, 0.02F, BLACK
    );

    DrawCube(
        Vector3{p.x + 0.08F, 1.48F, p.z + 0.18F},
        0.04F, 0.04F, 0.02F, BLACK
    );

    rlPopMatrix();
}

} // namespace Aldrathar
