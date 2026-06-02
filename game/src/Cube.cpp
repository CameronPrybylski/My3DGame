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
    if(mainCh)
    {
        if(input.IsKeyDown("D"))
        {
            rigidBody.velocity.z = sin(glm::radians(direction)) * 250.0f;
            rigidBody.velocity.x = cos(glm::radians(direction)) * -250.0f;
        }
        else if(input.IsKeyDown("A"))
        {
            rigidBody.velocity.z = sin(glm::radians(direction)) * -250.0f;
            rigidBody.velocity.x = cos(glm::radians(direction)) * 250.0f;
        }
        else if(input.IsKeyDown("W"))
        {
            rigidBody.velocity.z = cos(glm::radians(direction)) * 250.0f;
            rigidBody.velocity.x = sin(glm::radians(direction)) * 250.0f;
        }
        else if(input.IsKeyDown("S"))
        {
            rigidBody.velocity.z = cos(glm::radians(direction)) * -250.0f;
            rigidBody.velocity.x = sin(glm::radians(direction)) * -250.0f;
        }

        if(!(input.IsKeyDown("W") || input.IsKeyDown("S") || input.IsKeyDown("A") || input.IsKeyDown("D")))
        {
            rigidBody.velocity.z = 0.0f;
            rigidBody.velocity.x = 0.0f;
        }
    
        if(input.IsKeyDown("SPACE"))
        {
            rigidBody.velocity.y = 350.0f;
        }
    }
    
}

void Cube::Update(const Input& input, float dt)
{
}

void Cube::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
}