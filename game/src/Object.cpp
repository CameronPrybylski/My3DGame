#include <Game/Object.h>


Object::Object(std::string name, std::vector<float> vert, std::vector<unsigned int> ind, glm::vec3 position, 
        glm::vec3 scale, glm::vec4 color, float mass, bool isStatic)
{
    mesh = std::make_shared<ObjectMesh>();
    mesh->SetVertInd(vert, ind);
    shaderName = "objectShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    rigidBody.mass = mass;
    hitBox = transform;
    this->color = color;
    this->name = name;
}

Object::~Object()
{
}

void Object::OnEvent(const Input& input)
{
}

void Object::Update(const Input& input, float dt)
{
    GameObject::Update(input, dt);
}

void Object::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
    GameObject::Render(renderer, camera);
}

void Object::SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind)
{
    mesh->SetVertInd(vert, ind);
}