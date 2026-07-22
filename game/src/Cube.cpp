#include <Game/Cube.h>

Cube::Cube(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic)
{
    mesh = AssetManager::GetMesh("cubeMesh");
    shaderName = "objectShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    rigidBody.mass = mass;
    hitBox = transform;
    this->color = color;
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
    GameObject::Update(input, dt);
}

void Cube::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
    GameObject::Render(renderer, camera);
}