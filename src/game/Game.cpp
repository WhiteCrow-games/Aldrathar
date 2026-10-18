#include "game/Game.hpp"
#include <algorithm>
#include <cmath>

namespace {
constexpr float JOYSTICK_RADIUS = 28.0F;
constexpr float KNOB_RADIUS = 11.0F;
constexpr float TRUNK_RADIUS = 0.28F; // Solo tronco bloquea, no follaje
constexpr float PLAYER_COLLISION_RADIUS = 0.25F;
constexpr float TREE_COLLISION_RADIUS =
    TRUNK_RADIUS + PLAYER_COLLISION_RADIUS;

bool pointInCircle(Vector2 point, Vector2 center, float radius)
{
    const float dx = point.x - center.x;
    const float dy = point.y - center.y;
    return dx * dx + dy * dy <= radius * radius;
}

bool blockedAt(float x, float z)
{
    if (x < -13.0F || x > 13.0F || z < -13.0F || z > 13.0F) return true;

    // Solo troncos bloquean, follaje no
    const Vector2 trunks[] = {
        {-5.0F, -3.0F}, {5.5F, -4.0F}, {-6.0F, 3.0F},
        {6.5F, 4.0F}, {-4.5F, 7.0F}, {4.5F, 9.0F}
    };
    for (const Vector2& t : trunks) {
        if (pointInCircle(Vector2{x, z}, t, TREE_COLLISION_RADIUS)) return true;
    }

    const bool insideHouseLength = z > -6.95F && z < -3.0F;
    if (insideHouseLength && (std::abs(x - 2.43F) < 0.40F || std::abs(x + 2.43F) < 0.40F)) return true;
    if (std::abs(z + 6.68F) < 0.40F && std::abs(x) < 2.85F) return true;
    if (std::abs(z + 3.25F) < 0.40F && std::abs(x) > 0.17F && std::abs(x) < 2.85F) return true;
    return false;
}

bool isPlayerInsideHouse(Vector3 p) {
    return p.x > -2.3F && p.x < 2.3F && p.z > -6.5F && p.z < -3.3F;
}

unsigned char getWallAlpha(bool inside) {
    return inside ? 85 : 255; // PZ fade
}

unsigned char getFoliageAlpha(Vector3 player, Vector3 tree) {
    float dx = player.x - tree.x;
    float dz = player.z - tree.z;
    float dist = std::sqrt(dx*dx + dz*dz);
    // Si estas a <1.8m detrás del árbol, se desvanece
    if (dist < 1.8F) return 90;
    if (dist < 2.8F) return 170;
    return 255;
}
}

void Game::drawDragon()
{
    rlPushMatrix();
    rlTranslatef(dragonPos_.x, dragonPos_.y, dragonPos_.z);
    // Ya no gira 360, solo idle natural +-7.5 grados
    float headSway = std::sin(dragonIdle_) * 7.5F;
    float breath = std::sin(dragonIdle_ * 1.3F) * 0.08F;

    // Cuerpo con respiración
    rlPushMatrix();
    rlScalef(1.0f + breath, 1.0f + breath, 1.0f + breath);
    DrawCube(Vector3{0,1.0f,0}, 1.6f, 0.9f, 1.8f, Color{48,48,48,255});
    DrawCube(Vector3{0,0.95f,-0.6f}, 1.3f, 0.7f, 1.0f, Color{42,42,42,255});
    DrawCube(Vector3{0,1.25f,0.2f}, 1.0f, 0.35f, 1.2f, Color{60,60,60,255});
    rlPopMatrix();

    // Cuello segmentado
    DrawCube(Vector3{0,1.15f,1.1f}, 0.6f, 0.6f, 0.6f, Color{45,45,45,255});
    DrawCube(Vector3{0,1.25f,1.6f}, 0.55f, 0.55f, 0.55f, Color{46,46,46,255});

    // Cabeza con sway de 15°/s
    rlPushMatrix();
    rlTranslatef(0, 1.35f, 2.05f);
    rlRotatef(headSway, 0,1,0);
    DrawCube(Vector3{0,0,0}, 0.5f, 0.5f, 0.5f, Color{50,50,50,255});
    DrawCube(Vector3{0,-0.1f,0.55f}, 0.45f, 0.3f, 0.6f, Color{58,58,58,255});
    DrawCube(Vector3{-0.18f,0.2f,-0.15f}, 0.08f, 0.08f, 0.5f, Color{30,30,30,255});
    DrawCube(Vector3{0.18f,0.2f,-0.15f}, 0.08f, 0.08f, 0.5f, Color{30,30,30,255});
    DrawSphere(Vector3{-0.22f,0.05f,0.15f}, 0.07f, Color{255,170,20,255});
    DrawSphere(Vector3{0.22f,0.05f,0.15f}, 0.07f, Color{255,170,20,255});
    rlPopMatrix();

    // Alas cerradas - estatico
    DrawCube(Vector3{-0.9f,1.3f,0.1f}, 0.15f, 0.7f, 1.2f, Color{35,35,35,255});
    DrawCube(Vector3{0.9f,1.3f,0.1f}, 0.15f, 0.7f, 1.2f, Color{35,35,35,255});
    DrawCube(Vector3{-1.1f,1.25f,0.4f}, 0.05f, 0.6f, 1.2f, Color{110,25,25,200});
    DrawCube(Vector3{1.1f,1.25f,0.4f}, 0.05f, 0.6f, 1.2f, Color{110,25,25,200});

    // Patas
    DrawCube(Vector3{-0.55f,0.45f,0.5f}, 0.28f, 0.7f, 0.28f, Color{44,44,44,255});
    DrawCube(Vector3{0.55f,0.45f,0.5f}, 0.28f, 0.7f, 0.28f, Color{44,44,44,255});
    DrawCube(Vector3{-0.5f,0.4f,-0.5f}, 0.32f, 0.65f, 0.32f, Color{46,46,46,255});
    DrawCube(Vector3{0.5f,0.4f,-0.5f}, 0.32f, 0.65f, 0.32f, Color{46,46,46,255});

    // Cola larga 6 segmentos
    DrawCube(Vector3{0,0.85f,-1.3f}, 0.55f, 0.45f, 0.7f, Color{42,42,42,255});
    DrawCube(Vector3{0,0.8f,-1.95f}, 0.45f, 0.4f, 0.65f, Color{40,40,40,255});
    DrawCube(Vector3{0,0.75f,-2.55f}, 0.38f, 0.35f, 0.6f, Color{38,38,38,255});
    DrawCube(Vector3{0,0.7f,-3.1f}, 0.32f, 0.3f, 0.55f, Color{36,36,36,255});
    DrawCube(Vector3{0,0.65f,-3.6f}, 0.26f, 0.25f, 0.5f, Color{34,34,34,255});
    DrawCube(Vector3{0,0.6f,-4.05f}, 0.2f, 0.2f, 0.4f, Color{32,32,32,255});
    // Púas cola
    for (int i=0;i<5;i++) DrawCube(Vector3{0,0.9f - i*0.05f,-1.3f - i*0.62f}, 0.07f, 0.16f, 0.07f, Color{28,28,28,255});

    rlPopMatrix();
}

void Game::initialize()
{
    elapsedTime_ = 0.0F;
    player_.GetPosition() = Vector3{0.0F, 0.0F, 3.0F};
    dragonPos_ = Vector3{0.0F, 0.0F, -8.5F};
    dragonIdle_ = 0.0F;
    isometric_ = false;
    joystickTouchId_ = -1;
    cameraTouchId_ = -1;
    cameraTouchWasDown_ = false;
    touchMove_ = Vector2{0.0F, 0.0F};
    camera_.up = Vector3{0.0F, 1.0F, 0.0F};
    isInsideHouse_ = false;
    updateCamera();
}

void Game::updateCamera()
{
    camera_.target = Vector3{player_.GetPosition().x, player_.GetPosition().y + 0.8F, player_.GetPosition().z};
    if (isometric_) {
        camera_.position = Vector3{player_.GetPosition().x + 10.0F, player_.GetPosition().y + 12.0F, player_.GetPosition().z + 10.0F};
        camera_.projection = CAMERA_ORTHOGRAPHIC;
        camera_.fovy = 17.0F;
    } else {
        camera_.position = Vector3{player_.GetPosition().x, player_.GetPosition().y + 5.0F, player_.GetPosition().z + 8.5F};
        camera_.target.z -= 1.0F;
        camera_.projection = CAMERA_PERSPECTIVE;
        camera_.fovy = 48.0F;
    }
}

void Game::update(float fixedDeltaTime)
{
    elapsedTime_ += fixedDeltaTime;
    playerEntity_->Update(fixedDeltaTime);
    dragonIdle_ += DRAGON_IDLE_SPEED * 0.01745329252f * fixedDeltaTime; // 15°/s convertido a rad para sin()
    isInsideHouse_ = isPlayerInsideHouse(player_.GetPosition());

    if (IsKeyPressed(KEY_V)) isometric_ = !isometric_;
    float moveX = 0.0F, moveZ = 0.0F;
    if (IsKeyDown(KEY_A)) moveX -= 1.0F;
    if (IsKeyDown(KEY_D)) moveX += 1.0F;
    if (IsKeyDown(KEY_W)) moveZ -= 1.0F;
    if (IsKeyDown(KEY_S)) moveZ += 1.0F;

    const int touchCount = GetTouchPointCount();
    const bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const Vector2 mousePosition = GetMousePosition();
    bool joystickFound = false; bool cameraFound = false;

    if (touchCount > 0) {
        for (int i = 0; i < touchCount; ++i) {
            const int id = GetTouchPointId(i);
            const Vector2 screen = GetTouchPosition(i);
            const float sx = screen.x * 320.0F / static_cast<float>(GetScreenWidth());
            const float sy = screen.y * 240.0F / static_cast<float>(GetScreenHeight());
            const Vector2 p{sx, sy};
            if (id == joystickTouchId_) {
                joystickFound = true;
                const float dx = p.x - joystickCenter_.x; const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS ? JOYSTICK_RADIUS / distance : 1.0F;
                joystickKnob_ = Vector2{joystickCenter_.x + dx * scale, joystickCenter_.y + dy * scale};
                touchMove_.x = std::clamp(dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }
            if (id == cameraTouchId_) cameraFound = true;
            if (joystickTouchId_ == -1 && p.x < 100.0F && p.y > 125.0F) {
                joystickTouchId_ = id; joystickFound = true;
                const float dx = p.x - joystickCenter_.x; const float dy = p.y - joystickCenter_.y;
                const float distance = std::sqrt(dx * dx + dy * dy);
                const float scale = distance > JOYSTICK_RADIUS ? JOYSTICK_RADIUS / distance : 1.0F;
                joystickKnob_ = Vector2{joystickCenter_.x + dx * scale, joystickCenter_.y + dy * scale};
                touchMove_.x = std::clamp(dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
                touchMove_.y = std::clamp(dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            }
            if (cameraTouchId_ == -1 && p.x > 255.0F && p.y > 145.0F) { cameraTouchId_ = id; cameraFound = true; }
        }
    } else if (mouseDown) {
        const Vector2 p{mousePosition.x * 320.0F / static_cast<float>(GetScreenWidth()), mousePosition.y * 240.0F / static_cast<float>(GetScreenHeight())};
        if (p.x > 255.0F && p.y > 145.0F) { if (!cameraTouchWasDown_) isometric_ = !isometric_; cameraTouchWasDown_ = true; }
        else if (p.x < 100.0F && p.y > 125.0F) {
            const float dx = p.x - joystickCenter_.x; const float dy = p.y - joystickCenter_.y;
            const float distance = std::sqrt(dx * dx + dy * dy);
            const float scale = distance > JOYSTICK_RADIUS ? JOYSTICK_RADIUS / distance : 1.0F;
            joystickKnob_ = Vector2{joystickCenter_.x + dx * scale, joystickCenter_.y + dy * scale};
            touchMove_.x = std::clamp(dx / JOYSTICK_RADIUS, -1.0F, 1.0F);
            touchMove_.y = std::clamp(dy / JOYSTICK_RADIUS, -1.0F, 1.0F);
            joystickFound = true;
        }
    } else cameraTouchWasDown_ = false;

    if (touchCount > 0) {
        cameraTouchWasDown_ = cameraFound;
        if (cameraFound && cameraTouchId_ >= 0) { static int prev=-1; if (prev!=cameraTouchId_) isometric_=!isometric_; prev=cameraTouchId_; }
    }
    if (!joystickFound) { joystickTouchId_ = -1; joystickKnob_ = joystickCenter_; touchMove_ = Vector2{0.0F, 0.0F}; }
    if (!cameraFound) cameraTouchId_ = -1;

    moveX += touchMove_.x; moveZ += touchMove_.y;
    const float length = std::sqrt(moveX * moveX + moveZ * moveZ);
    player_.SetMoving(length > 0.0F);
    if (length > 0.0F) {
        constexpr float speed = 3.0F;
        const float stepX = (moveX / length) * speed * fixedDeltaTime;
        const float stepZ = (moveZ / length) * speed * fixedDeltaTime;
        const float nextX = player_.GetPosition().x + stepX;
        if (!blockedAt(nextX, player_.GetPosition().z)) player_.GetPosition().x = nextX;
        const float nextZ = player_.GetPosition().z + stepZ;
        if (!blockedAt(player_.GetPosition().x, nextZ)) player_.GetPosition().z = nextZ;
    }
    updateCamera();
}

void Game::render(float interpolation)
{
    (void)interpolation;
    BeginMode3D(camera_);
    drawOutdoor();
    drawHouse();
    drawTrees();
    drawBushes();
    drawDragon();
    drawCharacter();
    EndMode3D();
    DrawRectangle(5, 5, 205, 52, Color{0, 0, 0, 210});
    DrawText("ALDRATHAR // OUTDOOR", 10, 10, 10, RAYWHITE);
    if (isometric_) DrawText("CAMARA: ISOMETRICA", 10, 24, 8, SKYBLUE);
    else DrawText("CAMARA: TERCERA PERSONA", 10, 24, 8, SKYBLUE);
    DrawText(isInsideHouse_ ? "DENTRO: PAREDES FADE" : "FUERA", 10, 36, 8, isInsideHouse_? GREEN : LIGHTGRAY);
    DrawText("ARBOLES: TRONCO BLOQUEA / COPA FADE", 10, 46, 8, LIGHTGRAY);
    DrawText("PROTOTIPO 3D", 8, 226, 8, LIGHTGRAY);
    drawTouchControls();
}

void Game::drawTouchControls()
{
    DrawCircleV(joystickCenter_, JOYSTICK_RADIUS + 5.0F, Color{0, 0, 0, 100});
    DrawCircleV(joystickCenter_, JOYSTICK_RADIUS, Color{170, 180, 170, 100});
    DrawCircleLines(static_cast<int>(joystickCenter_.x), static_cast<int>(joystickCenter_.y), JOYSTICK_RADIUS, Color{220, 225, 210, 210});
    DrawCircleV(joystickKnob_, KNOB_RADIUS, Color{225, 225, 210, 220});
    const Vector2 buttonCenter{282.0F, 184.0F};
    DrawCircleV(buttonCenter, 24.0F, Color{0, 0, 0, 120});
    DrawCircleV(buttonCenter, 19.0F, Color{110, 130, 120, 210});
    DrawCircleLines(282, 184, 19.0F, RAYWHITE);
    DrawText("CAM", 269, 180, 9, RAYWHITE);
}
void Game::drawOutdoor()
{
    DrawPlane(Vector3{0.0F, -0.05F, 0.0F}, Vector2{32.0F, 32.0F}, Color{63, 78, 53, 255});
    DrawCube(Vector3{0.0F, 0.01F, 4.0F}, 2.2F, 0.04F, 18.0F, Color{116, 94, 67, 255});
}
void Game::drawHouse()
{
    unsigned char alpha = getWallAlpha(isInsideHouse_);
    const Color wall{113, 104, 85, alpha};
    const Color roof{67, 43, 39, alpha};
    const Color dark{36, 39, 38, alpha};

    DrawCube(Vector3{-2.43F, 1.35F, -5.0F}, 0.14F, 2.7F, 3.5F, wall);
    DrawCube(Vector3{2.43F, 1.35F, -5.0F}, 0.14F, 2.7F, 3.5F, wall);
    DrawCube(Vector3{0.0F, 1.35F, -6.68F}, 5.0F, 2.7F, 0.14F, wall);
    DrawCube(Vector3{-1.49F, 1.35F, -3.25F}, 2.02F, 2.7F, 0.14F, wall);
    DrawCube(Vector3{1.49F, 1.35F, -3.25F}, 2.02F, 2.7F, 0.14F, wall);
    DrawCube(Vector3{0.0F, 2.2F, -3.25F}, 0.96F, 1.0F, 0.14F, wall);
    DrawCube(Vector3{-1.25F, 3.0F, -5.0F}, 2.9F, 0.18F, 4.1F, roof);
    DrawCube(Vector3{1.25F, 3.0F, -5.0F}, 2.9F, 0.18F, 4.1F, roof);
    DrawCube(Vector3{-0.56F, 0.85F, -3.18F}, 0.12F, 1.7F, 0.08F, dark);
    DrawCube(Vector3{-1.65F, 1.55F, -3.16F}, 0.85F, 0.75F, 0.08F, Color{53, 83, 91, alpha});
    DrawCube(Vector3{1.65F, 1.55F, -3.16F}, 0.85F, 0.75F, 0.08F, Color{53, 83, 91, alpha});
    DrawCube(Vector3{0.0F, 0.05F, -3.1F}, 2.0F, 0.12F, 0.7F, Color{90, 83, 70, alpha});
}
void Game::drawTrees()
{
    const Vector3 positions[] = {{-5.0F, 0.0F, -3.0F},{5.5F, 0.0F, -4.0F},{-6.0F, 0.0F, 3.0F},{6.5F, 0.0F, 4.0F},{-4.5F, 0.0F, 7.0F},{4.5F, 0.0F, 9.0F}};
    for (const Vector3& p : positions) {
        // Tronco siempre solido y bloquea
        DrawCylinder(Vector3{p.x, 0.8F, p.z}, TRUNK_RADIUS, TRUNK_RADIUS*0.8F, 1.6F, 8, Color{91, 65, 43, 255});
        // Copa con fade si jugador detrás
        unsigned char alpha = getFoliageAlpha(player_.GetPosition(), p);
        Color leaf1{42, 76, 43, alpha};
        Color leaf2{52, 88, 47, alpha};
        DrawSphere(Vector3{p.x, 2.0F, p.z}, 1.0F, leaf1);
        DrawSphere(Vector3{p.x + 0.35F, 2.35F, p.z}, 0.65F, leaf2);
    }
}
void Game::drawBushes()
{
    // Arbustos no bloquean, pero tambien hacen fade
    const Vector3 bushes[] = {{2.0F,0,-1.0F},{-2.0F,0,1.0F},{3.5F,0,6.0F}};
    for (auto &b : bushes) {
        unsigned char alpha = getFoliageAlpha(player_.GetPosition(), b);
        DrawSphere(Vector3{b.x, 0.3F, b.z}, 0.45F, Color{55,85,45,alpha});
        DrawSphere(Vector3{b.x+0.2F,0.4F,b.z}, 0.35F, Color{65,95,50,alpha});
    }
}
void Game::drawCharacter()
{
    playerEntity_->Draw();
}

void Game::drawRoom() { DrawPlane(Vector3{0.0F, 0.0F, 0.0F}, Vector2{8.0F, 8.0F}, Color{43, 46, 48, 255}); }
void Game::drawFurniture() { DrawCube(Vector3{-1.7F, 0.85F, -1.8F}, 2.0F, 0.12F, 0.9F, Color{91, 97, 99, 255}); }
