#pragma once

#include <Game/Battle/ActorInBattle.h>

class PlayerInBattle : public ActorInBattle {

public:
    PlayerInBattle(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, std::string texturesFilePath, glm::vec3 position, 
    glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, int hp, int damageOutput);
    ~PlayerInBattle();


};