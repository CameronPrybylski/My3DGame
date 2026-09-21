#pragma once

#include <Game/TexturedObject.h>

class ActorInBattle : public TexturedObject {

public:
    ActorInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
    glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput);
    ~ActorInBattle();

    virtual void Update(const Input& input, float dt) override;

    virtual void TakeDamage(int damage){hp -= damage;}
    bool IsAlive(){return hp > 0;}
    int GetDamageOutput(){return damageOutput;}
    bool IsAttacking(){return attacking;}
    void SetAttacking(bool attacking){this->attacking = attacking;}
    bool IsAttackAnimating(){return attackAnimation;}
    bool IsMoving();
    glm::vec3 GetAttackPosition(){return attackToPosition;}
    void SetAttackPosition(glm::vec3 attackPosition){this->attackToPosition = attackPosition;}
    virtual void ReturnToStart();


protected:
    int hp;
    int damageOutput;
    bool attacking = false;
    bool attackAnimation = false;
    glm::vec3 attackToPosition;
    glm::vec3 startPosition;

};