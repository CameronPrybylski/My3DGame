#pragma once

#include <Game/TexturedObject.h>

class Texture3D;

class NPC : public TexturedObject
{
public:
    NPC(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, float maxDistance, glm::vec3 velocity, glm::vec3 direction);
    ~NPC();


    void OnEvent(const Input& input) override;
    virtual void Update(const Input& input, float dt) override;
    virtual void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

protected:
   float distanceTraveled = 0.0f;
   float maxDistance;
   glm::vec3 direction;
};