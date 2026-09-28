#pragma once

#include <Engine/Scene/GameObject.h>

class Cube : public GameObject
{
public:
    Cube(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic);
    ~Cube();


    void OnEvent(const Input& input) override;
    virtual void Update(const Input& input, float dt) override;
    virtual void Render(Renderer& renderer, const Camera& camera) override;
    void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

    bool mainCh = false;
    bool rotatingCounter = false;

    float direction = 0.0f;
};