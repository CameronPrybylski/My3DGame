#include <Game/Cube.h>

Cube::Cube(std::string name)
{
    mesh = AssetManager::GetMesh("cubeMesh");
    shaderName = "objectShader";
    transform.position = glm::vec3(500.0f, 500.0f, 10.0f);
    transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    rigidBody.isStatic = false;
    rigidBody.mass = 1.0f;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->name = name;
}

Cube::~Cube()
{
}

void Cube::OnEvent(const Input& input)
{
}

void Cube::Update(const Input& input, float dt)
{
}

void Cube::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
}