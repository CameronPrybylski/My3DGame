#include <Game/NPC.h>

#include <cmath>
#include <algorithm>
#include <Engine/Renderer/Texture3D.h>

NPC::NPC(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, float maxDistance, glm::vec3 velocity, glm::vec3 direction) : 
        TexturedObject(name,submeshes,texturesFilePath,position,scale,color,mass,isStatic), 
        maxDistance(maxDistance), direction(direction)
{
    this->rigidBody.velocity = velocity;
}

NPC::~NPC()
{
}

void NPC::OnEvent(const Input& input)
{
}

void NPC::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
}

void NPC::Update(const Input& input, float dt)
{    
    if(rigidBody.isCollidingVec == glm::vec3(0.0f,0.0f,0.0f))
    {
        if(distanceTraveled >= maxDistance)
        {
            distanceTraveled = 0.0f;
            direction *= -1.0f;
            rigidBody.velocity = glm::vec3(0.0f,0.0f,0.0f);
        }
        
        if( (rigidBody.velocity.x == 0.0f || std::abs(rigidBody.velocity.x) < 250.0f) &&
            (rigidBody.velocity.z == 0.0f || std::abs(rigidBody.velocity.z) < 250.0f))
        {
            rigidBody.velocity += (direction * 25.0f);
        }

        distanceTraveled += std::abs(transform.position.x - rigidBody.previousPosition.x);
        distanceTraveled += std::abs(transform.position.z - rigidBody.previousPosition.z);
    }
    GameObject::Update(input, dt);
}

