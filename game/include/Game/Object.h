#pragma once

#include <Engine/Scene/GameObject.h>

class Object : public GameObject
{
public:
    Object(std::string name, std::vector<float> vert, std::vector<unsigned int> ind);
    ~Object();


    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    bool mainCh = false;
    bool rotatingCounter = false;

    float direction = 0.0f;

    void SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind);
};