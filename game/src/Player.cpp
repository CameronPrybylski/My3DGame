#include <Game/Player.h>
#include <cmath>
#include <algorithm>
#include <Engine/Renderer/Texture3D.h>

Player::Player(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp) : 
        TexturedObject(name,submeshes,texturesFilePath,position,scale,color,mass,isStatic), hp(hp)
{
}

Player::~Player()
{
}

void Player::OnEvent(const Input& input)
{
    if(rigidBody.isCollidingVec.x == 0.0f && rigidBody.isCollidingVec.z == 0.0f)
    {
        if(input.IsKeyDown("D"))
        {
            transform.rotation.y = (direction) - 90.0f;
            if(rigidBody.velocity.z < 250.0f)
                rigidBody.velocity.z = (sin(glm::radians(direction)) * 250.0f);
            if(rigidBody.velocity.x < 250.0f)
                rigidBody.velocity.x = (cos(glm::radians(direction)) * -250.0f);
        }
        else if(input.IsKeyDown("A"))
        {
            transform.rotation.y = (direction) + 90.0f;
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
            transform.rotation.y = (direction) - 180.0f;
            rigidBody.velocity.z = cos(glm::radians(direction)) * -250.0f;
            rigidBody.velocity.x = sin(glm::radians(direction)) * -250.0f;
        }
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

    if(input.IsKeyDown("SPACE") && jumps < 2)
    {
        rigidBody.velocity.y = 400.0f;
        ++jumps;
    }
}

void Player::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    if(collisionNormal.y == 1)
    {
        jumps = 0;
    }
}

void Player::Update(const Input& input, float dt)
{    
    GameObject::Update(input, dt);
}