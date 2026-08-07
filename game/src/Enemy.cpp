#include <Game/Enemy.h>

Enemy::Enemy(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, float maxDistance, glm::vec3 velocity, glm::vec3 direction, int hp)
        : NPC(name, submeshes, texturesFilePath, position, scale, color, mass, isStatic, maxDistance, velocity, direction), hp(hp)
{

}

Enemy::~Enemy()
{
}


void Enemy::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{

}