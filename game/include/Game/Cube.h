#pragma once

#include <Engine/Scene/GameObject.h>

class Cube : public GameObject
{
public:
    Cube(std::string name);
    ~Cube();


    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    bool mainCh = false;
    bool rotatingCounter = false;

    float direction = 0.0f;
};