#pragma once

#include <Engine/Scene/GameObject.h>
#include <Engine/Renderer/Material.h>

class Texture3D;

class Player : public GameObject
{
public:
    Player(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath);
    ~Player();


    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void Render(Renderer& renderer, const Camera& camera) override;

    void SetDirection(float direction){this->direction = direction;}

    void SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind);
    void SetMaterialMap(std::map<std::string, std::shared_ptr<Material>> materialMap);

    void SetSubMeshes(std::vector<std::shared_ptr<Mesh>> submeshes){this->submeshes = submeshes;}

private:
    bool rotatingCounter = false;
    bool roatatingClock = false;

    std::map<std::string, std::shared_ptr<Material>> materialMap;
    std::map<std::string, Texture> texturesMap;
    std::vector<std::shared_ptr<Mesh>> submeshes;
    std::string texturesFilePath;

    float direction = 0.0f;
    int jumps = 0;
};