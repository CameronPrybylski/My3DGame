#pragma once

#include <Game/TexturedObject.h>

class PassageWay : public TexturedObject {

public:
    PassageWay(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, std::string nextScene);
    ~PassageWay();

    std::string GetNextScene(){return this->nextScene;}
protected:
    std::string nextScene;
};