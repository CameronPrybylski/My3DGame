#include <Game/Battle/PlayerInBattle.h>


PlayerInBattle::PlayerInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, 
    glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput) : ActorInBattle(name,submeshes,texturesFilePath,position,scale,color,mass,isStatic, hp, damageOutput)
{
}

PlayerInBattle::~PlayerInBattle()
{
}

void PlayerInBattle::OnEvent(const Input &input)
{
    if(input.IsKeyDown("SPACE") && !IsMoving())
    {
        this->attacking = true;
    }
}

