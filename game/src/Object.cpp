#include <Game/Object.h>


Object::Object(std::string name, std::vector<float> vert, std::vector<unsigned int> ind)
{
    mesh = std::make_shared<ObjectMesh>();
    mesh->SetVertInd(vert, ind);
    shaderName = "objectShader";
    transform.position = glm::vec3(1000.0f, 500.0f, 10.0f);
    transform.scale = glm::vec3(50.0f, 50.0f, 50.0f);
    rigidBody.isStatic = false;
    rigidBody.mass = 1.0f;
    this->color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
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
}

void Object::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
}

void Object::SetVertInd(std::vector<float> vert, std::vector<unsigned int> ind)
{
    mesh->SetVertInd(vert, ind);
}