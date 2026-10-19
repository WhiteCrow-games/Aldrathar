#include "game/DragonEntity.hpp"

#include <cmath>
#include <raylib.h>
#include <rlgl.h>

namespace Aldrathar {

void DragonEntity::Update(float deltaTime)
{
    idleTime_ += 15.0F * DEG2RAD * deltaTime;

    headSwayDegrees_ = std::sin(idleTime_) * 7.5F;
    breathScale_ = std::sin(idleTime_ * 1.3F) * 0.08F;
}

void DragonEntity::Draw() const
{
    rlPushMatrix();
    rlTranslatef(position_.x, position_.y, position_.z);

    // Cuerpo con respiración.
    rlPushMatrix();
    rlScalef(
        1.0F + breathScale_,
        1.0F + breathScale_,
        1.0F + breathScale_
    );
    DrawCube(Vector3{0,1.0F,0}, 1.6F, 0.9F, 1.8F, Color{48,48,48,255});
    DrawCube(Vector3{0,0.95F,-0.6F}, 1.3F, 0.7F, 1.0F, Color{42,42,42,255});
    DrawCube(Vector3{0,1.25F,0.2F}, 1.0F, 0.35F, 1.2F, Color{60,60,60,255});
    rlPopMatrix();

    // Cuello.
    DrawCube(Vector3{0,1.15F,1.1F}, 0.6F, 0.6F, 0.6F, Color{45,45,45,255});
    DrawCube(Vector3{0,1.25F,1.6F}, 0.55F, 0.55F, 0.55F, Color{46,46,46,255});

    // Cabeza animada.
    rlPushMatrix();
    rlTranslatef(0, 1.35F, 2.05F);
    rlRotatef(headSwayDegrees_, 0, 1, 0);
    DrawCube(Vector3{0,0,0}, 0.5F, 0.5F, 0.5F, Color{50,50,50,255});
    DrawCube(Vector3{0,-0.1F,0.55F}, 0.45F, 0.3F, 0.6F, Color{58,58,58,255});
    DrawCube(Vector3{-0.18F,0.2F,-0.15F}, 0.08F, 0.08F, 0.5F, Color{30,30,30,255});
    DrawCube(Vector3{0.18F,0.2F,-0.15F}, 0.08F, 0.08F, 0.5F, Color{30,30,30,255});
    DrawSphere(Vector3{-0.22F,0.05F,0.15F}, 0.07F, Color{255,170,20,255});
    DrawSphere(Vector3{0.22F,0.05F,0.15F}, 0.07F, Color{255,170,20,255});
    rlPopMatrix();

    // Alas cerradas.
    DrawCube(Vector3{-0.9F,1.3F,0.1F}, 0.15F, 0.7F, 1.2F, Color{35,35,35,255});
    DrawCube(Vector3{0.9F,1.3F,0.1F}, 0.15F, 0.7F, 1.2F, Color{35,35,35,255});
    DrawCube(Vector3{-1.1F,1.25F,0.4F}, 0.05F, 0.6F, 1.2F, Color{110,25,25,200});
    DrawCube(Vector3{1.1F,1.25F,0.4F}, 0.05F, 0.6F, 1.2F, Color{110,25,25,200});

    // Patas.
    DrawCube(Vector3{-0.55F,0.45F,0.5F}, 0.28F, 0.7F, 0.28F, Color{44,44,44,255});
    DrawCube(Vector3{0.55F,0.45F,0.5F}, 0.28F, 0.7F, 0.28F, Color{44,44,44,255});
    DrawCube(Vector3{-0.5F,0.4F,-0.5F}, 0.32F, 0.65F, 0.32F, Color{46,46,46,255});
    DrawCube(Vector3{0.5F,0.4F,-0.5F}, 0.32F, 0.65F, 0.32F, Color{46,46,46,255});

    // Cola segmentada y púas.
    DrawCube(Vector3{0,0.85F,-1.3F}, 0.55F, 0.45F, 0.7F, Color{42,42,42,255});
    DrawCube(Vector3{0,0.8F,-1.95F}, 0.45F, 0.4F, 0.65F, Color{40,40,40,255});
    DrawCube(Vector3{0,0.75F,-2.55F}, 0.38F, 0.35F, 0.6F, Color{38,38,38,255});
    DrawCube(Vector3{0,0.7F,-3.1F}, 0.32F, 0.3F, 0.55F, Color{36,36,36,255});
    DrawCube(Vector3{0,0.65F,-3.6F}, 0.26F, 0.25F, 0.5F, Color{34,34,34,255});
    DrawCube(Vector3{0,0.6F,-4.05F}, 0.2F, 0.2F, 0.4F, Color{32,32,32,255});

    for (int i = 0; i < 5; ++i) {
        DrawCube(
            Vector3{0, 0.9F - i * 0.05F, -1.3F - i * 0.62F},
            0.07F, 0.16F, 0.07F,
            Color{28,28,28,255}
        );
    }

    rlPopMatrix();
}

} // namespace Aldrathar
