#pragma once

#include <Engine/Scene/GameObject.h>
#include <Engine/Renderer/Material.h>

class Texture3D;

class TexturedObject : public GameObject
{
public:
    TexturedObject(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic);
    ~TexturedObject();


    virtual void OnEvent(const Input& input) override;
    virtual void Update(const Input& input, float dt) override;
    virtual void Render(Renderer& renderer, const Camera& camera) override;
    virtual void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

    void SetDirection(float direction){this->direction = direction;}
    void SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind);
    void SetMaterialMap(std::map<std::string, std::shared_ptr<Material>> materialMap);
    void SetSubMeshes(std::vector<std::shared_ptr<Mesh>> submeshes){this->submeshes = submeshes;}

    void SetTextures(std::vector<std::shared_ptr<Texture>> textures){this->textures = textures;}


protected:
    bool rotatingCounter = false;
    bool roatatingClock = false;

    std::map<std::string, std::shared_ptr<Material>> materialMap;
    std::map<std::string, Texture> texturesMap;
    std::vector<std::shared_ptr<Mesh>> submeshes;
    std::string texturesFilePath;
    std::vector<std::shared_ptr<Texture>> textures;

    float direction = 0.0f;
};