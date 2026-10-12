#include <Game/Battle/PlayerInBattle.h>


PlayerInBattle::PlayerInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, 
    glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput) : ActorInBattle(name,submeshes,position,scale,color,mass,isStatic, hp, damageOutput)
{
}

PlayerInBattle::~PlayerInBattle()
{
}

