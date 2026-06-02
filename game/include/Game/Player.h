#pragma once

#include <Engine/Scene/GameObject.h>

class Player : public GameObject
{
public:
    Player(std::string name);
    ~Player();


    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    bool mainCh = false;
    bool rotatingCounter = false;

    float direction = 0.0f;
};