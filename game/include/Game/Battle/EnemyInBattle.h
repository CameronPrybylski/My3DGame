#pragma once

#include <Game/Battle/ActorInBattle.h>

class EnemyInBattle : public ActorInBattle {

public:
    EnemyInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
    glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput);
    ~EnemyInBattle();

    virtual void SetHighLightedColor(){this->color = highlightColor;}

protected:
    glm::vec4 highlightColor = glm::vec4{0.5f, 0.0f, 0.0f, 0.8f};

};