#include <Game/TexturedObject.h>

#include <cmath>
#include <algorithm>
#include <Engine/Renderer/Texture3D.h>

TexturedObject::TexturedObject(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic)
{
    mesh = std::make_shared<ObjectMesh>();
    //mesh->SetVertTextInd(vert, ind);
    this->submeshes = submeshes;
    shaderName = "textureShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    rigidBody.mass = mass;
    hitBox = transform;
    this->color = color;
    this->name = name;
    this->texturesFilePath = texturesFilePath;
}

TexturedObject::~TexturedObject()
{
}

void TexturedObject::OnEvent(const Input& input)
{
}

void TexturedObject::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
}

void TexturedObject::Update(const Input& input, float dt)
{    
    GameObject::Update(input, dt);
}

void TexturedObject::Render(Renderer& renderer, const Camera& camera)
{
    for(int i = 0; i < submeshes.size(); ++i)
    {
        std::shared_ptr<Mesh> submesh = submeshes[i];
        Texture t;
        if(submesh->material != nullptr && texturesMap.count(submesh->material->GetName()))
            renderer.DrawTextureCube(*submesh, transform, camera, AssetManager::GetShader(shaderName), texturesMap[submesh->material->GetName()], true, color, lightPos);
        else
            renderer.DrawTextureCube(*submesh, transform, camera, AssetManager::GetShader(shaderName), t, false, color, lightPos);
    }
    GameObject::Render(renderer, camera);
}

void TexturedObject::SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind)
{
    mesh->SetVertTextInd(vert, ind);
}

void TexturedObject::SetMaterialMap(std::map<std::string, std::shared_ptr<Material>> materialMap)
{
    this->materialMap = materialMap;
    std::map<std::string, std::shared_ptr<Material>>::iterator materialItr = materialMap.begin();
    for(; materialItr != materialMap.end(); ++materialItr)
    {
        if(!materialItr->second->GetMapKd().empty())
            texturesMap[materialItr->first].Create(texturesFilePath + materialItr->second->GetMapKd());
    }
}