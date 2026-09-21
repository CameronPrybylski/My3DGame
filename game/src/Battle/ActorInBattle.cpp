#include <Game/Battle/ActorInBattle.h>

ActorInBattle::ActorInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, 
    glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput) : TexturedObject(name,submeshes,texturesFilePath,position,scale,color,mass,isStatic), hp(hp), damageOutput(damageOutput)
{
    attackToPosition = glm::vec3(0.0f);
    startPosition = position;
}

ActorInBattle::~ActorInBattle()
{
}

void ActorInBattle::Update(const Input &input, float dt)
{
    GameObject::Update(input, dt);
    if(!IsMoving() && attacking && attackToPosition != glm::vec3(0.0f))
    {
        glm::vec3 directionalVec = attackToPosition - transform.position;
        rigidBody.velocity.z = directionalVec.z * 1.0f;
        rigidBody.velocity.x = directionalVec.x * 1.0f;
    }
    else if(IsMoving() && !attacking && startPosition.x != transform.position.x && startPosition.z != transform.position.z)
    {
        ReturnToStart();
    }
}

bool ActorInBattle::IsMoving()
{
    return rigidBody.velocity.x != 0.0f || rigidBody.velocity.z != 0.0f;
}

void ActorInBattle::ReturnToStart()
{
    attacking = false;
    attackToPosition = glm::vec3(0.0f);
    glm::vec3 directionalVec = startPosition - transform.position;
    rigidBody.velocity.z = directionalVec.z * 1.0f;
    rigidBody.velocity.x = directionalVec.x * 1.0f;
}