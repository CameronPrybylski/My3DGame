#pragma once

#include <Game/NPC.h>

class Enemy : public NPC
{

public:
    Enemy(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, float maxDistance, glm::vec3 velocity, glm::vec3 direction, int hp);
    ~Enemy();

    //virtual void Update(const Input& input, float dt) override;
    virtual void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

    void TakeDamage(int damage){hp -= damage;}
    bool IsAlive(){return hp > 0;}

protected:
    int hp;
};