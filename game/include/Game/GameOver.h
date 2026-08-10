#pragma once

#include <Engine/Scene/Scene.h>

class GameOver : public Scene
{
public:
    GameOver(float screenWidth, float screenHeight, std::string root, std::string loadFilePath, std::string nextScene);
    ~GameOver();

    void Init() override;
    void OnEvent(const Input& input) override;
    
private:
    std::string root;
    std::string loadFilePath;
};