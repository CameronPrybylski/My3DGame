#pragma once

#include <Engine/Scene/Scene.h>

class PlayerInBattle;
class EnemyInBattle;

class Battle : public Scene {

public:
    Battle(float screenWidth, float screenHeight, std::string root, std::string loadFilePath);
    ~Battle();

    void Init() override;

    void LoadBattle();
    void LoadPhysics(PhysicsSystem& physics) override;
    void OnEvent(const Input& input) override;
    void OnUpdate(const Input& input, PhysicsSystem& physics, float dt) override;

    virtual void HandleAttackTurn();
    virtual void AnimateIntro();

protected:
    std::string root;
    std::string loadFilePath;

    std::shared_ptr<PlayerInBattle> player;
    std::vector<std::shared_ptr<EnemyInBattle>> enemies;
    
    glm::vec3 cameraAnimationChange;
    int selectedEnemy = 0;
    bool playerTurn = true;
    bool introAnimation = true;


};