#include <Game/Battle/EnemyInBattle.h>


EnemyInBattle::EnemyInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, 
    glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput) : ActorInBattle(name,submeshes,texturesFilePath,position,scale,color,mass,isStatic, hp, damageOutput)
{
}

EnemyInBattle::~EnemyInBattle()
{
}
