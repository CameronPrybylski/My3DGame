#pragma once

#include <Game/TexturedObject.h>

class Texture3D;

class Player : public TexturedObject
{
public:
    Player(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp);
    ~Player();


    void OnEvent(const Input& input) override;
    void Update(const Input& input, float dt) override;
    void OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt) override;

    void TakeDamage(int damage){this->hp -= damage;}
    bool IsAlive(){return hp > 0;}


private:
    int jumps = 0;
    int hp;
};