#pragma once

#include <Engine/Scene/Scene.h>

class Cube;
class Player;
class Enemy;

class Level : public Scene {

public:
    Level(float screenWidth, float screenHeight, std::string root, std::string loadFilePath);
    ~Level();

    void Init() override;

    void LoadLevel();
    void LoadPhysics(PhysicsSystem& physics) override;
    void OnEvent(const Input& input) override;
    void OnUpdate(const Input& input, PhysicsSystem& physics, float dt) override;
    void DrawObjects(Renderer& renderer) override;
    void OnCollision(std::vector<CollisionEvent> collisions, float dt);

    void UpdateCamera(const Input& input, float dt);
    

private:
    std::string root;
    std::string loadFilePath;
    std::shared_ptr<Player> player;
    std::shared_ptr<Cube> playerCube;
    std::map<std::string, std::shared_ptr<Enemy>> enemies;
    bool cameraRight = false;
    bool cameraLeft = false;
    bool cameraUp = false;
    bool cameraDown = false;
    bool cameraTowards = false;
    bool cameraAway = false;
    float angle = 0.0f;

    void EnemyPlayerCollision(std::string body1Name, std::string body2Name, glm::vec3 body1CollNorm, glm::vec3 body2CollNorm);

};