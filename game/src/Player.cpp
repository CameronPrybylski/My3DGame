#include <Game/Player.h>
#include <cmath>
#include <algorithm>
#include <Engine/Renderer/Texture3D.h>

Player::Player(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath)
{
    mesh = std::make_shared<ObjectMesh>();
    //mesh->SetVertTextInd(vert, ind);
    this->submeshes = submeshes;
    shaderName = "textureShader";
    transform.position = glm::vec3(500.0f, 500.0f, 10.0f);
    transform.scale = glm::vec3(10.0f, 10.0f, 10.0f);
    rigidBody.isStatic = false;
    rigidBody.mass = 1.0f;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->name = name;
    this->texturesFilePath = texturesFilePath;
}

Player::~Player()
{
}

void Player::OnEvent(const Input& input)
{
    
    if(input.IsKeyDown("D"))
    {
        transform.rotation.y = direction - 90.0f;
        rigidBody.velocity.z = sin(glm::radians(direction)) * 250.0f;
        rigidBody.velocity.x = cos(glm::radians(direction)) * -250.0f;
    }
    else if(input.IsKeyDown("A"))
    {
        transform.rotation.y = direction + 90.0f;
        rigidBody.velocity.z = sin(glm::radians(direction)) * -250.0f;
        rigidBody.velocity.x = cos(glm::radians(direction)) * 250.0f;
    }
    else if(input.IsKeyDown("W"))
    {
        transform.rotation.y = direction;
        rigidBody.velocity.z = cos(glm::radians(direction)) * 250.0f;
        rigidBody.velocity.x = sin(glm::radians(direction)) * 250.0f;
    }
    else if(input.IsKeyDown("S"))
    {
        transform.rotation.y = direction - 180.0f;
        rigidBody.velocity.z = cos(glm::radians(direction)) * -250.0f;
        rigidBody.velocity.x = sin(glm::radians(direction)) * -250.0f;
    }

    if(!(input.IsKeyDown("W") || input.IsKeyDown("S") || input.IsKeyDown("A") || input.IsKeyDown("D")))
    {
        rigidBody.velocity.z = 0.0f;
        rigidBody.velocity.x = 0.0f;
    }

    if(input.IsKeyDown("L"))
    {
        roatatingClock = true;
    }
    else
    {
        roatatingClock = false;
    }

    if(input.IsKeyDown("J"))
    {
        rotatingCounter = true;
    }
    else
    {
        rotatingCounter = false;
    }

    if(input.IsKeyDown("SPACE") and jumps < 2)
    {
        rigidBody.velocity.y = 400.0f;
        ++jumps;
    }
    
    
}

void Player::Update(const Input& input, float dt)
{
    if(rigidBody.velocity.y == 0.0f)
    {
        jumps = 0;
    }
    if(roatatingClock)
    {
        //transform.rotation.y -= 10.0f;
    }
    if(rotatingCounter)
    {
        //transform.rotation.y += 10.0f;
    }
}

void Player::Render(Renderer& renderer, const Camera& camera)
{
    glm::vec3 oldPos = transform.position;
    transform.position += posOffset;
    glm::vec3 oldScale = transform.scale;
    transform.scale /= scaleMulti;
    for(int i = 0; i < submeshes.size(); ++i)
    {
        std::shared_ptr<Mesh> submesh = submeshes[i];
        renderer.DrawTextureCube(*submesh, transform, camera, AssetManager::GetShader(shaderName), texturesMap[submesh->material->GetName()], color);
    }
    transform.position = oldPos;
    transform.scale = oldScale;
}

void Player::SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind)
{
    mesh->SetVertTextInd(vert, ind);
}

void Player::SetMaterialMap(std::map<std::string, std::shared_ptr<Material>> materialMap)
{
    this->materialMap = materialMap;
    std::map<std::string, std::shared_ptr<Material>>::iterator materialItr = materialMap.begin();
    for(; materialItr != materialMap.end(); ++materialItr)
    {
        texturesMap[materialItr->first].Create(texturesFilePath + materialItr->second->GetMapKd());
    }
    //this->textures = textrs;
}