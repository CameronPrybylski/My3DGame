#include <Game/PassageWay.h>

PassageWay::PassageWay(std::string name, std::vector<std::shared_ptr<Mesh>> submeshes, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, std::string nextScene) : TexturedObject(name, submeshes, position, scale, color, mass, isStatic), nextScene(nextScene)
{

}

PassageWay::~PassageWay()
{

}